

#include "pch.h"
#include "PlayerInfo.h"


PlayerInfo::PlayerInfo() : m_name{ " " }, m_roomNumber{ -1 }, m_roomInTime{ "" }
{
	m_chattingBuffer.reserve( InitailizeServer::MAX_BUFFERSIZE );
}

PlayerInfo::~PlayerInfo() noexcept = default;

const char* PlayerInfo::GetName() const
{
	return m_name;
}

void PlayerInfo::SetName( const char* name )
{
	strcpy_s( m_name, name );
}

void PlayerInfo::SetRoomNumber( const int& num )
{
	m_roomNumber = num;
}

void PlayerInfo::SetRoomInTime( const std::string time )
{
	m_roomInTime = time;
}

void PlayerInfo::PushChattingBuffer( char word )
{
	m_chattingBuffer.emplace_back( word );
}

void PlayerInfo::ClearChattingBuffer()
{
	m_chattingBuffer.clear();
}

const std::string_view PlayerInfo::GetChattingLog()
{
	std::string_view str{ m_chattingBuffer.begin(), m_chattingBuffer.begin() + m_chattingBuffer.size() };
	return str;
}

const int& PlayerInfo::GetRoomNumber()
{
	return m_roomNumber;
}

const std::string& PlayerInfo::GetRoomInTime() const
{
	return m_roomInTime;
}
