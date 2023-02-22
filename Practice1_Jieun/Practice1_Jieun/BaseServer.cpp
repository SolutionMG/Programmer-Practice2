

#include "pch.h"
#include "BaseServer.h"
#include "ChattingRoom.h"
#include "PlayerInfo.h"

#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>


BaseServer::BaseServer() : m_iocpHandle( NULL ), m_listenSocket( INVALID_SOCKET )
{   
}

BaseServer::~BaseServer() noexcept = default;

bool BaseServer::Initialize()
{
    ///Initialize
    m_players.reserve( 100 );

    for (int i = 0; i < 1000; ++i) 
        m_charRoomNumber.push(i);

    InitializeCommandFunction();

    ///오류 메시지 한국어 출력
    std::wcout.imbue( std::locale( "korean" ) );

    WSADATA wsaData;
    int returnValue = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( returnValue != 0 )
    {
        DisplayError( "WSAStartup Initialize()" );
        return false;
    }

    m_listenSocket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );

    if ( m_listenSocket == INVALID_SOCKET )
    {
        DisplayError( "WSASocket Initialize()" );
        return false;
    }

    ///Nagle Off Option
    int socketOption = 1;
    returnValue = setsockopt( m_listenSocket, SOL_SOCKET, TCP_NODELAY, reinterpret_cast< const char* >( &socketOption ), sizeof( socketOption ) );
    if ( returnValue != 0 )
    {
        DisplayError( "setsockopt Initialize()" );
        return false;
    }

    std::cout << "Server Initialize Sueccess..." << std::endl;
    return true;
}

bool BaseServer::OpenServer()
{
    /// IOCP 객체 생성
    m_iocpHandle = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, NULL, 0 );
    CreateIoCompletionPort( reinterpret_cast< HANDLE >( m_listenSocket ), m_iocpHandle, 0, 0 );

    WSAOVERLAPPED_EXTEND over;
    Accept( &over );

    ///WorkerThread 생성 - Accept, Send, Recv 기능 수행 IOCP 쓰레드 풀을 통해 TOTALCORE/2 개수의 스레드로 동작
    std::vector< std::thread > workerThreads;
    for (int i = 0; i < ( InitializeServer::TOTALCORE / 2 ); ++i)
    {
        workerThreads.emplace_back( [ & ]() { MainWorkProcess(); } );
    }

    ///Other Thread...

    ///LogOnThread - 로그인 관리 Thread
    std::thread logonThread{ [ & ]() { LogOnCommandProcess(); } };
    logonThread.join();

    for ( auto& wthread : workerThreads )
    {
        wthread.join();
    }

    closesocket( m_listenSocket );
    WSACleanup();

    return false;
}

void BaseServer::AddCommand( const std::string& command, std::function<bool( const SOCKET& socket ) > commandFunction )
{
    m_commandFunctions.emplace( std::make_pair( command , commandFunction ) );
}

bool BaseServer::InitializeCommandFunction()
{
    m_commandFunctions.reserve( 10 );

    AddCommand( CommandMessage::COMMANDLIST, std::function( [ & ]( const SOCKET& socket ) -> bool { return ReqeustCommandList( socket ); } ) );
    AddCommand( CommandMessage::USERLIST, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestUserList( socket ); } ) );
    AddCommand( CommandMessage::EXIT, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestExit( socket ); } ) );
    AddCommand( CommandMessage::ROOMCREATE, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestRoomCreate( socket ); } ) );
    AddCommand( CommandMessage::ROOMLIST, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestRoomList( socket ); } ) );
    AddCommand( CommandMessage::ROOMENTER, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestRoomEnter( socket ); } ) );
    AddCommand( CommandMessage::PLAYERINFO , std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestUserInfo( socket ); } ) );
    AddCommand( CommandMessage::ROOMINFO, std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestRoomInfo( socket ); } ) );
    AddCommand( CommandMessage::SECRETMESSAGE , std::function( [ & ]( const SOCKET& socket ) -> bool { return RequestNote( socket ); } ) );

    return true;
}

bool BaseServer::MainWorkProcess()
{
    while ( true )
    {
        DWORD bytes;
        ULONG_PTR completionKey;
        WSAOVERLAPPED* over;

        bool returnValue = GetQueuedCompletionStatus( m_iocpHandle, &bytes, &completionKey, &over, INFINITE );
        
        SOCKET userKey = static_cast< SOCKET > ( completionKey );
        WSAOVERLAPPED_EXTEND* overExtend = reinterpret_cast< WSAOVERLAPPED_EXTEND* >( over );

        switch ( overExtend->opType )
        {
        case EOperationType::RECV:
        {
            if ( bytes == 0 || returnValue == false )
            {
                Disconnect( userKey );
                break;
            }
            ReassemblePacket( overExtend->networkBuffer, bytes, userKey );
        }
        break;

        case EOperationType::SEND:
        {
            if ( bytes == 0 || returnValue == false ) 
            {
                Disconnect( userKey );
                break;
            }
            delete over;
            over = nullptr;
        }
        break;

        case EOperationType::ACCEPT:
        {
            if ( returnValue == false )
            {
                Disconnect( userKey );
                break;
            }

            userKey = overExtend->socket;
            std::cout << "ACCEPT Player [" << userKey << "]" << std::endl;
            AddNewClient( userKey );
            m_playersLock.lock();
            m_players[userKey].ReceivePacket();
            m_playersLock.unlock();

            Accept( overExtend );
        }
        break;
        }
    }
    return false;
}

bool BaseServer::Listen()
{
    SOCKADDR_IN serverAddr;
    ZeroMemory( &serverAddr, sizeof( serverAddr ) );
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( InitializeServer::SERVERPORT );
    serverAddr.sin_addr.S_un.S_addr = htonl( INADDR_ANY );

    int returnValue = -1;
    returnValue = bind( m_listenSocket, reinterpret_cast< sockaddr* >( &serverAddr ), sizeof( serverAddr ) );

    if ( returnValue != 0 )
    {
        DisplayError( "bind Listen()" );
        return false;
    }

    returnValue = listen( m_listenSocket, SOMAXCONN );
    if ( returnValue != 0 )
    {
        DisplayError( "listen Listen()" );
        return false;
    }

    std::cout << "Waiting For Player..." << std::endl;
    return true;
}

bool BaseServer::Accept( WSAOVERLAPPED_EXTEND* over )
{
    SOCKET socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
    if ( socket == INVALID_SOCKET )
    {
        DisplayError( "WSAStartup Accept()" );
        return false;
    }

    ///Nagle Off Option
    int socketOption = 1;
    int returnValue = setsockopt( socket, SOL_SOCKET, TCP_NODELAY, reinterpret_cast< const char* >( &socketOption ), sizeof( socketOption ));
    if ( returnValue != 0 )
    {
        DisplayError( "setsockopt Accept()" );
        return false;
    }

    ZeroMemory( &over->over, sizeof( over->over ) );

    DWORD bytes;
    over->opType = EOperationType::ACCEPT;
    over->socket = socket;

    bool returnValue2 = AcceptEx( m_listenSocket, socket, over->networkBuffer, 0, sizeof( SOCKADDR_IN ) + 16, sizeof( SOCKADDR_IN ) + 16, &bytes, &over->over );
    if ( returnValue2 == false )
    {
        ///작업이 성공적으로 시작, 아직 진행 중
        if ( WSAGetLastError() == ERROR_IO_PENDING )
            return true;

        DisplayError( "AcceptEx Accept()" );
        return false;
    }

    return true;
}

bool BaseServer::AddNewClient( const SOCKET& socket )
{
    m_playersLock.lock();
    m_players[socket].StartLock();
    m_players[socket].SetSocket( socket );
    m_players[socket].SetOverlappedOperation( EOperationType::RECV );
    m_players[socket].SetState( EClientState::ACCESS );
    m_players[socket].EndLock();
    m_playersLock.unlock();

    HANDLE returnValue2 = CreateIoCompletionPort( reinterpret_cast< HANDLE >( socket ), m_iocpHandle, socket, 0 );
    if ( returnValue2 == NULL ) 
    {
        DisplayError( "CreateIoCompletionPort AddNewClient()" );
        return false;
    }

    /// 로그인 요청 메시지 전송
    m_playersLock.lock();
    m_players[socket].SendPacket( RenderMessageMacro::ACCESS_MESSAGE );
    m_players[socket].SendPacket( RenderMessageMacro::LOGON_REQUEST );
    m_players[socket].SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
    m_playersLock.unlock();

    return true;
}

bool BaseServer::StateWorkBranch( const SOCKET& socket, const std::string& command )
{
    m_playersLock.lock();
    auto& player = m_players[ socket ];
    m_playersLock.unlock();
    player.StartLock();
    switch (player.GetState())
    {
    case EClientState::ACCESS:
    {
        player.EndLock();

        if (command.length() < sizeof(CommandMessage::LOGON) + 1)
        {
            player.StartLock();
            player.ClearChattingBuffer();
            player.EndLock();
            player.SendPacket( RenderMessageMacro::LOGON_REQUEST );
            player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
            break;
        }

        std::string_view checkCommand = { command.cbegin(), command.cbegin() + sizeof(CommandMessage::LOGON) - 1 };
        if (checkCommand == CommandMessage::LOGON && command[5] == ' ')
        {
            m_logOn.push(socket);
        }
        else
        {
            player.StartLock();
            player.ClearChattingBuffer();
            player.EndLock();
            player.SendPacket( RenderMessageMacro::LOGON_REQUEST );
            player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        }
    }
    break;
    case EClientState::LOGON:
    {
        player.EndLock();
        CommandWorkBranch( socket, command );
    }
    break;
    case EClientState::ROOM:
    {
        player.EndLock();

        std::string_view message = { command.cbegin(), command.end() };
        if ( message == CommandMessage::ROOMEXIT )
        {
            RequestRoomExit( socket );
            return true;
        }

        Chatting( socket );
        player.StartLock();
        player.ClearChattingBuffer();
        player.EndLock();
        
        player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
    }
    break;
    case EClientState::END:
    {
        player.ClearChattingBuffer();
        player.EndLock();
    }
    break;
    default:
    {
        player.ClearChattingBuffer();
        player.EndLock();
    }
    break;
    }

    return true;
}

bool BaseServer::CommandWorkBranch( const SOCKET& socket, const std::string& command )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();


    if (command.empty() )
    {
        player.StartLock();
        player.ClearChattingBuffer();
        player.EndLock();

        player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }

    bool flag = true;
    if (command.length() == 1 )
    {       
        auto iterator = m_commandFunctions.find( command );
        if ( iterator == m_commandFunctions.end() )
        {
            player.StartLock();
            player.ClearChattingBuffer();
            player.EndLock();
            player.SendPacket( RenderMessageMacro::NOCOMMAND_MESSAGE );
            player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
            flag = false;
        }
        else
        {
            if ( flag == true )
            {
                m_commandFunctions[ command ]( socket );
                
                if (command == CommandMessage::EXIT)
                    return true;

                player.StartLock();
                player.ClearChattingBuffer();
                player.EndLock();
            }
            return true;
        }
    }
    else if (command.length() >= 2 )
    {
        std::string checkCommand2Word = "";
        if (command[1] == ' ' )
        {
            checkCommand2Word = { command.cbegin(), command.cbegin() + 1 };
        }
        else
        {
            checkCommand2Word = { command.cbegin(), command.cbegin() + 2 };
        }
        auto iterator = m_commandFunctions.find( checkCommand2Word );
        if ( iterator == m_commandFunctions.end() )
        {
            player.StartLock();
            player.ClearChattingBuffer();
            player.EndLock();
            player.SendPacket( RenderMessageMacro::NOCOMMAND_MESSAGE );
            player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
            flag = false;
        }
        if ( flag == true )
        {
            m_commandFunctions[checkCommand2Word]( socket );
            player.StartLock();
            player.ClearChattingBuffer();
            player.EndLock();
        }
        return true;
    }
    return false;
}

bool BaseServer::ReqeustCommandList( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    player.SendPacket( RenderMessageMacro::DIVIDE_LINE_MESSAGE );
    player.SendPacket( RenderMessageMacro::GUIDE_MESSAGE );
    player.SendPacket( RenderMessageMacro::DIVIDE_LINE_MESSAGE );
    player.SendPacket( RenderMessageMacro::SELECT_COMMAND_MESSAGE );
    player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );

    return true;
}

bool BaseServer::RequestExit( const SOCKET& socket )
{
    return Disconnect(socket);
}

bool BaseServer::RequestUserInfo( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    player.StartLock();
    std::string_view message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };
    player.EndLock();

    std::string parse = "";

    if (message.length() < 4)
    {
        parse += RenderMessageMacro::FAILED_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    if (message[2] != ' ')
    {
        player.SendPacket(RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }

    std::string_view userName = { message.cbegin() + 3, message.cend() };
    bool flag = false;
    SOCKET userSocket;

    m_playersLock.lock();
    for ( const auto& user : m_players )
    {
        if ( user.second.GetState() > EClientState::ACCESS && user.second.GetState() < EClientState::EXIT )
        {
            if ( userName == user.second.GetName() )
            {
                userSocket = user.first;
                flag = true;
                break;
            }
        }
    }
    m_playersLock.unlock();


    if ( flag == true )
    {
        parse += "<유저 정보>\n\r";

        m_playersLock.lock();
        auto& target = m_players[userSocket];
        m_playersLock.unlock();

        parse += { userName.cbegin(), userName.cend()};

        switch ( target.GetState() )
        {
        case EClientState::ACCESS:
        {
        }
        break;
        case EClientState::LOGON:
        {
            parse += "님은 로비에 있습니다.\n\r";
            parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
            parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
            player.SendPacket( parse.c_str());
        }
        break;
        case EClientState::ROOM:
        {
            parse += "님은";

            target.StartLock();
            int roomNumber = target.GetRoomNumber();
            target.EndLock();

            char roomIndex[8]; 
            _itoa_s( roomNumber, roomIndex, 10 );
            parse += roomIndex;
            parse += "번 방에 있습니다.\n\r";
            parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
            player.SendPacket( parse.c_str() );
        }
        break;
        case EClientState::EXIT:
        {
        }
        break;
        case EClientState::END:
        {
        }
        break;
        default:
            break;
        }
    }
    else
    {
        parse += RenderMessageMacro::USERINFO_MESSAGE_FAILED;
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
    }

    return true;
}

bool BaseServer::RequestUserList( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    std::string_view message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };

    if ( message.length() > 2 )
    {
        player.SendPacket(RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }
    

    std::string userNameList = "--------------------------------유저 목록--------------------------------\n\r";
    m_playersLock.lock();
    for ( const auto& p : m_players )
    {
        if ( p.second.GetState() > EClientState::ACCESS && p.second.GetState() < EClientState::EXIT )
        {
            userNameList += p.second.GetName();
            userNameList += "\n\r";
        }
    }
    m_playersLock.unlock();

    std::string parse = userNameList;
    parse += RenderMessageMacro::DIVIDE_LINE_MESSAGE;
    parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
    parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;

    player.SendPacket( parse);

    return true;
}

bool BaseServer::RequestRoomInfo( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    std::string_view message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };
    std::string parse = "";
    if (message.length() < 4)
    {
        parse += RenderMessageMacro::NOCOMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    if ( message[2] != ' ' )
    {
        parse += RenderMessageMacro::NOCOMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    std::string roomIndex = { message.cbegin() + 3, message.cend() };
    int isNumber = message[ 3 ] - '0';

    if (isNumber < 0 || isNumber > 9)
    {
        parse += "<방 정보 불러오기 실패> \n\r";
        parse += RenderMessageMacro::FAILED_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    int index = atoi( roomIndex.c_str() );
    std::string sendMessage = "[";
    parse += "<방 정보>\n\r";

    ///현재 시간
    ///입장 시간 기입
    std::string roomInTime = "";
    char timebuffer[64];
    time_t currentTime = time( NULL );
    tm currentTm;
    localtime_s( &currentTm, &currentTime );

    strftime( timebuffer, sizeof( timebuffer ), "%m-%d-%Y %X", &currentTm );
    roomInTime = timebuffer;

    bool flag = false;
    m_chattRoomLock.lock();
    for ( const auto& room : m_chattingRooms )
    {
        if ( index == room.first )
        {
            flag = true;
            ///방 정보 메시지 보내기
            char roomTotal[8];
            char roomMax[8];
            _itoa_s(room.second.GetTotalPlayer(), roomTotal, 10);
            _itoa_s(room.second.GetMaxUser(), roomMax, 10);

            sendMessage += roomIndex;
            sendMessage += "] (";
            sendMessage += roomTotal;
            sendMessage += "/";
            sendMessage += roomMax;
            sendMessage += ") ";
            sendMessage += room.second.GetName();
            sendMessage += "\n\r";
            sendMessage += "개설시간:   ";
            sendMessage += room.second.GetRoomInTime();

            for (const auto& id : room.second.GetAccessorIndex())
            {
                m_playersLock.lock();
                sendMessage += "\n\r참여자:";
                sendMessage += m_players[id].GetName();
                sendMessage += "    참여시간:   ";
                sendMessage += m_players[id].GetRoomInTime();
                sendMessage += "\n\r";
                m_playersLock.unlock();
            }

            parse += RenderMessageMacro::ROOMINFO_LINE_MESSAGE;
            parse += sendMessage;
            parse += RenderMessageMacro::DIVIDE_LINE_MESSAGE;

            player.SendPacket( parse );
            
            break;
        }
    }
    m_chattRoomLock.unlock();

    if (flag == false)
    {
        player.SendPacket("<방 정보 불러오기 실패> 존재하지 않는 방입니다.\n\r");
    }

    player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
    return true;
}

bool BaseServer::RequestNote( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    std::string_view message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };

    if (message.length() <= 2)
    {
        player.SendPacket( RenderMessageMacro::FAILED_COMMAND_MESSAGE );
        player.SendPacket( RenderMessageMacro::SELECT_COMMAND_MESSAGE );
        player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }

    std::string name;
    std::string note;
    bool flag = true;
    for ( int i = 3; i < message.length(); ++i )
    {
        if ( message[i] == ' ' )
        {
            flag = false;
        }

        if (flag == true)
        {
            name += message[i];

        }
        else
        {
            note += message[i];
        }
    }

    bool isExistPlayer = false;
    PlayerInfo* targetPlayerInfo = nullptr;

    {
        m_playersLock.lock();
        
        for ( auto& p : m_players )
        {
            if ( name == p.second.GetName() )
            {
                targetPlayerInfo = &( p.second );
                isExistPlayer = true;
            }
        }

        m_playersLock.unlock();
    }
    
    std::string parse = "";
    if ( isExistPlayer == false )
    {
        parse += "<귓속말> 존재하지 않는 유저입니다.\n\r";
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;

        player.SendPacket( parse );

    }
    else
    {
        if ( name == player.GetName() )
        {
            parse += "<귓속말> 본인에게는 귓속말을 할 수 없습니다.\n\r";
            parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
            parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;

            player.SendPacket( parse );
        }
        else
        {
            std::string fromName;
            {
                std::lock_guard<std::mutex> guard( player.GetLock() );
                fromName = player.GetName();
            }

            parse += "<귓속말> ";
            parse += "[ ";
            parse += fromName;
            parse += " ==> ";
            parse += name;
            parse += " ] ";
            parse += note;
            parse += "\n\r";
            parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
            targetPlayerInfo->SendPacket( parse.c_str() );
        }

    }

    return false;
}

bool BaseServer::RequestRoomExit( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[ socket ];
    m_playersLock.unlock();
    std::string name;
    int beforeRoomIndex = -1;
    {
        std::lock_guard<std::mutex> guard( player.GetLock() );
        name = player.GetName();
        beforeRoomIndex = player.GetRoomNumber();
        player.SetRoomNumber( -1 );
        player.SetState( EClientState::LOGON );
        player.SendPacket( "방에서 퇴장하셨습니다.\n\r");
        player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        player.ClearChattingBuffer();
    }

    {
        m_chattRoomLock.lock();
        auto& room = m_chattingRooms[ beforeRoomIndex ];
        m_chattRoomLock.unlock();

        room.StartLock();
        int total = room.GetTotalPlayer();
        room.EndLock();

        if ( total == 1 )
        {
            ///사용하지 않게된 인덱스 회수
            m_chattRoomNumLock.lock();
            m_charRoomNumber.push( room.GetIndex() );
            m_chattRoomNumLock.unlock();

            ///방폭파
            m_chattRoomLock.lock();
            m_chattingRooms.erase( room.GetIndex() );
            m_chattRoomLock.unlock();
        }
        else
        {
            room.StartLock();
            room.SetTotalPlayers( --total );
            room.PopAccessor( socket );
            const std::vector< SOCKET > remainUser = room.GetAccessorIndex();
            room.EndLock();

            room.StartLock();
            int max = room.GetMaxUser();
            room.EndLock();

            char totalUserString[ 8 ];
            char maxUserString[ 8 ];

            _itoa_s( max, maxUserString, 10 );
            _itoa_s( total, totalUserString, 10 );

            /// 퇴장 메시지 출력
            std::string message = "** [";
            message += name;
            message += "] 님이 나가셨습니다. (현재인원: ";
            message += totalUserString;
            message += "/";
            message += maxUserString;
            message += ")\n\r";

            m_playersLock.lock();
            for ( const auto& user : remainUser )
            {
                m_players[ user ].SendPacket( message );
            }
            m_playersLock.unlock();
        }
    }
    return true;
}

bool BaseServer::RequestRoomCreate( const SOCKET& socket )
{
    ///o 최대인원 방이름
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();
    std::string_view message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };

    ///[예외처리] 양식에 맞지 않음
    if ( message.length() <= 4 )
    {
        player.SendPacket( RenderMessageMacro::FAILED_COMMAND_MESSAGE );
        player.SendPacket( RenderMessageMacro::SELECT_COMMAND_MESSAGE );
        player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }

    std::string max = "";
    std::string roomName = "";
    bool flag = false;
    for ( int i = 2; i < message.length(); ++i )
    {
        if ( message[i] == ' ' )
        {
            flag = true;
        }

        if ( flag == false )
        {
            max += message[i];
        }
        else
        {
            if ( message[i] != ' ' )
                roomName += message[i];
        }
    }

    /// 방이름이 없음
    if ( roomName.empty() == true )
    {
        player.SendPacket(RenderMessageMacro::CREATE_ROOM_FAILED_OVERUSERS);
        player.SendPacket(RenderMessageMacro::ROOM_ENTER_NONAME_MESSAGE);
        player.SendPacket(RenderMessageMacro::SELECT_COMMAND_MESSAGE);
        player.SendPacket(RenderMessageMacro::COMMAND_WAIT_MESSAGE );
    }

    int maxUser = atoi(max.c_str());

    
    /// 인원 초과 혹은 양식에 맞지 않음.
    if (  maxUser < InitializeRoom::MIN_ROOMPLAYER || maxUser > InitializeRoom::MAX_ROOMPLAYER )
    {
        player.SendPacket(RenderMessageMacro::CREATE_ROOM_FAILED_OVERUSERS );
        player.SendPacket(RenderMessageMacro::FAILED_COMMAND_MESSAGE);
        player.SendPacket(RenderMessageMacro::SELECT_COMMAND_MESSAGE );
        player.SendPacket(RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        return false;
    }

    m_chattRoomNumLock.lock();
    int number = m_charRoomNumber.top();
    m_charRoomNumber.pop();
    m_chattRoomNumLock.unlock();

    m_chattRoomLock.lock();
    auto& room = m_chattingRooms[number];
    m_chattRoomLock.unlock();

    ///입장 시간 기입
    std::string roomInTime = "";
    ///현재 시간
    char timebuffer[64];
    time_t currentTime = time(NULL);
    tm currentTm;
    localtime_s( &currentTm, &currentTime );

    strftime( timebuffer, sizeof( timebuffer ), "%m-%d-%Y %X", &currentTm );
    roomInTime = timebuffer;

    room.StartLock();
    room.SetIndex( number );
    room.SetMaxUser( maxUser );
    room.SetName( roomName.c_str() );
    room.SetTotalPlayers( 1 );
    room.PushAccessor( socket );
    room.EndLock();
    room.SetRoomInTime( roomInTime );
    
    std::cout <<"["<< number <<"] [" << roomName << "] 생성" << std::endl;

    player.StartLock();
    player.SetState( EClientState::ROOM );
    player.SetRoomNumber( number );
    player.SetRoomInTime( roomInTime );
    player.EndLock();

    std::string enterMessage = "** ";
    enterMessage += m_players[socket].GetName();
    enterMessage += "님이 들어오셨습니다. (현재인원: 1/";
    enterMessage += max;
    enterMessage += ")\n\r";

    
    player.SendPacket( RenderMessageMacro::CREATE_ROOM_SUCCESS_MESSAGE );
    player.SendPacket( enterMessage.c_str() );
    player.SendPacket( "** 방에서 나가기 : /X\n\r");
    player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );

    return true;
}

bool BaseServer::RequestRoomEnter( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];;
    m_playersLock.unlock();

    std::string message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };
    std::string userName = player.GetName();

    std::string parse = "";

    if (message[1] != ' ')
    {
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    std::string roomNumberMessage = { message.cbegin() + 2, message.cend() };

    int roomNumber =  atoi( roomNumberMessage.c_str() );
    m_chattRoomLock.lock();
    auto iter = m_chattingRooms.find( roomNumber );
    auto enditer = m_chattingRooms.end();
    m_chattRoomLock.unlock();

    if (iter == enditer)
    {
        parse += RenderMessageMacro::ROOM_ENTER_FAILED_MESSAGE;
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    m_chattRoomLock.lock();
    auto& room = m_chattingRooms[roomNumber];
    m_chattRoomLock.unlock();


    room.StartLock();
    int total = room.GetTotalPlayer();
    int max = room.GetMaxUser();
    room.EndLock();

    ///최대 인원 제한
    if (total == max)
    {
        parse += RenderMessageMacro::ROOM_ENTER_FULLMESSAGE;
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return false;
    }

    room.StartLock();
    room.PushAccessor( socket );
    std::vector< SOCKET > roomUserIndex = room.GetAccessorIndex();
    room.SetTotalPlayers( ++total );
    room.EndLock();

    ///입장 시간 기입
    std::string roomInTime = "";
    ///현재 시간
    char timebuffer[64];
    time_t currentTime = time( NULL );
    tm currentTm;
    localtime_s( &currentTm, &currentTime );

    strftime( timebuffer, sizeof( timebuffer ), "%m-%d-%Y %X", &currentTm );
    roomInTime = timebuffer;

    player.StartLock();
    player.SetState( EClientState::ROOM );
    player.SetRoomNumber( roomNumber );
    player.SetRoomInTime( roomInTime );
    player.EndLock();
    
    char totalcount[8];
    char maxcount[8];
    _itoa_s( total, totalcount, 10 );
    _itoa_s( max, maxcount, 10 );

    std::string enterMessage = "\n\r** ";
    enterMessage +=  userName;
    enterMessage += "님이 입장하셨습니다. (현재인원: ";
    enterMessage += totalcount;
    enterMessage += "/ ";
    enterMessage += maxcount;
    enterMessage += ")\n\r";    

    player.SendPacket( "** 방에서 나가기 : /X\n\r" );

    parse += "<입장>";
    parse += enterMessage;
    parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;

    m_playersLock.lock();
    for ( const auto& user : roomUserIndex )
    {
        m_players[user].SendPacket( parse.c_str() );
    }
    m_playersLock.unlock();


    return true;
}

bool BaseServer::RequestRoomList( const SOCKET& socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();
    std::string message = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };

    m_chattRoomLock.lock();
    size_t roomSize = m_chattingRooms.size();
    m_chattRoomLock.unlock();

    std::string parse;
    parse = "--------------------------------방 목록--------------------------------\n\r";



    if ( roomSize == 0 )
    {
        /// 방이 없음.
        parse += "방이 존재하지 않습니다.\n\r";
        parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
        parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
        player.SendPacket( parse );
        return true;
    }

    std::string roomsInfo = "";
    char roomNumber[8];
    char totalPlayer[8];
    char maxPlayer[8];
    m_chattRoomLock.lock();
    for ( auto& room : m_chattingRooms )
    {
        _itoa_s( room.first, roomNumber, 10 );
        room.second.StartLock();
        _itoa_s( room.second.GetTotalPlayer(), totalPlayer, 10 );
        _itoa_s( room.second.GetMaxUser(), maxPlayer, 10 );
        const char* name = room.second.GetName();
        room.second.EndLock();

        roomsInfo += '[';
        roomsInfo += roomNumber;
        roomsInfo += "] ";
        roomsInfo += name;
        roomsInfo += "(현재인원: ";
        roomsInfo += totalPlayer;
        roomsInfo += ",";
        roomsInfo += maxPlayer;
        roomsInfo += ")";
        roomsInfo += "\n\r";
    }
    m_chattRoomLock.unlock();

    parse += roomsInfo;
    parse += RenderMessageMacro::DIVIDE_LINE_MESSAGE;
    parse += RenderMessageMacro::SELECT_COMMAND_MESSAGE;
    parse += RenderMessageMacro::COMMAND_WAIT_MESSAGE;
    player.SendPacket( parse );

    return true;
}

void BaseServer::LogOnCommandProcess()
{
    using namespace std::chrono_literals;

    while ( true )
    {
        m_logOnLock.lock();
        if ( m_logOn.empty() == true )
        {
            m_logOnLock.unlock();
            /// 로그인 하려는 유저가 있을 때 마다만 동작.
            std::this_thread::sleep_for( 100ms );
        }

        else
        {
            bool check = false;

            SOCKET socket = m_logOn.front();
            m_logOn.pop();
            m_logOnLock.unlock();

            m_playersLock.lock();
            auto& player = m_players[socket];
            m_playersLock.unlock();

            /// 이름 추출
            player.StartLock();
            const std::string name{ player.GetChattingLog().cbegin() + sizeof(CommandMessage::LOGON),player.GetChattingLog().cend() };
            player.EndLock();
            /// 동일이름 유저 존재유무 확인

            m_playersLock.lock();
            for (const auto& p : m_players)
            {
                if (name == p.second.GetName())
                {
                    check = true;
                    break;
                }
            }
            m_playersLock.unlock();

           
            if (check == false)
            {
                player.StartLock();
                player.ClearChattingBuffer();
                player.SetName( name.c_str() );
                player.SetState( EClientState::LOGON );
                player.EndLock();
                std::cout << name.c_str() << "[" << socket << "] LogOn" << std::endl;

                ///클라이언트에 로그인 성공 문구 출력
                player.SendPacket( RenderMessageMacro::DIVIDE_LINE_MESSAGE );
                player.SendPacket( RenderMessageMacro::SUCCESS_LOGON_MESSAGE );
                player.SendPacket( RenderMessageMacro::DIVIDE_LINE_MESSAGE );
                player.SendPacket( RenderMessageMacro::SELECT_COMMAND_MESSAGE );
                player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
            }

            else
            {
                player.StartLock();
                player.ClearChattingBuffer();
                player.EndLock();

                ///클라이언트에 로그인 실패 문구 출력
                player.SendPacket( RenderMessageMacro::LOGON_FAILED );
                player.SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
            }
            player.ReceivePacket();
        }
    }
}

bool BaseServer::Chatting( const SOCKET& socket )
{
    std::string userMessage = "[";
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    int roomIndex = player.GetRoomNumber();
    userMessage += player.GetName();
    std::string message = { player.GetChattingLog().cbegin(),player.GetChattingLog().cend() };

    userMessage += "]";
    userMessage += " ";
    userMessage += message;
    userMessage += "\n\r";

    m_chattRoomLock.lock();
    auto& room = m_chattingRooms[roomIndex];
    m_chattRoomLock.unlock();

    room.StartLock();
    const std::vector< SOCKET > playersIndex = room.GetAccessorIndex();
    room.EndLock();

    for ( int i = 0; i < playersIndex.size(); ++i )
    {
        if ( playersIndex[i] == socket )
        {
            continue;
        }
        m_playersLock.lock();
        m_players[playersIndex[i]].SendPacket( userMessage.c_str() );
        m_players[playersIndex[i]].SendPacket( RenderMessageMacro::COMMAND_WAIT_MESSAGE );
        m_playersLock.unlock();
    }


    return false;
}

bool BaseServer::ReassemblePacket( char* packet, const DWORD& bytes, const SOCKET& socket )
{
    if ( packet == nullptr || bytes == 0 )
        return false;

    m_playersLock.lock( );
    auto& player = m_players[ socket ];
    m_playersLock.unlock( );

    bool flag = false;
    std::string command;
    for (DWORD i = 0; i < bytes; ++i)
    {
        if ( packet[ i ] == '\r\n' || packet[ i ] == '\n' || packet[ i ] == '\r' )
        {
            command = { player.GetChattingLog().cbegin(), player.GetChattingLog().cend() };
            for ( auto& ele : command )
            {
                if ( ele == ' ' )
                    break;

                if ( ele >= 'a' && ele <= 'z' )
                    ele -= 'a' - 'A';
            }

            std::cout << command << std::endl;
            StateWorkBranch( socket, command );
            flag = true;
            break;
        }
        else
        {
            player.StartLock();
            player.PushChattingBuffer( packet[ i ] );
            player.EndLock();
        }
    }
    if ( command != CommandMessage::EXIT )
        player.ReceivePacket();
    
    return true;
}

bool BaseServer::Disconnect( SOCKET socket )
{
    m_playersLock.lock();
    auto& player = m_players[socket];
    m_playersLock.unlock();

    player.StartLock();
    const std::string name = player.GetName();
    player.EndLock();

    if (player.GetState() == EClientState::ROOM)
    {
        m_chattRoomLock.lock();
        auto& room = m_chattingRooms[player.GetRoomNumber()];
        m_chattRoomLock.unlock();

        room.StartLock();
        int total = room.GetTotalPlayer();
        room.EndLock();

        if (total == 1)
        {
            ///사용하지 않게된 인덱스 회수
            m_chattRoomNumLock.lock();
            m_charRoomNumber.push( room.GetIndex() );
            m_chattRoomNumLock.unlock();

            ///방폭파
            m_chattRoomLock.lock();
            m_chattingRooms.erase( room.GetIndex() );
            m_chattRoomLock.unlock();
        }
        else
        {
            room.StartLock();
            room.SetTotalPlayers( --total );
            room.PopAccessor( socket );
            const std::vector< SOCKET > remainUser = room.GetAccessorIndex();
            room.EndLock();

            room.StartLock();
            int max = room.GetMaxUser();
            room.EndLock();

            char totalUserString[8];
            char maxUserString[8];

            _itoa_s( max, maxUserString, 10 );
            _itoa_s( total, totalUserString, 10 );

            /// 퇴장 메시지 출력
            std::string message = "** [";
            message += name;
            message += "] 님이 나가셨습니다. (현재인원: ";
            message += totalUserString;
            message += "/";
            message += maxUserString;
            message += ")\n\r";

            m_playersLock.lock();
            for ( const auto& user : remainUser )
            {
                m_players[user].SendPacket( message );
            }
            m_playersLock.unlock();
        }
    }

    m_playersLock.lock();
    m_players.erase(socket);
    m_playersLock.unlock();

    closesocket(socket);

    std::cout << "[" << socket << "] " << name << " 유저 접속 종료" << std::endl;
    return true;
}

void BaseServer::DisplayError( const char* msg )
{
    void* messageBuffer;
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&messageBuffer, 0, NULL );
    std::cout << msg;
    std::wcout << L" 에러 " << messageBuffer << std::endl;
    LocalFree( messageBuffer );
}
