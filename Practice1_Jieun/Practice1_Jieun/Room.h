

#ifndef ROOM_H
#define ROOM_H


class Room
{
private:
	std::mutex m_roomLock;

	/// 방 번호
	int m_index;
	/// 방 이름
	char m_name[InitializeRoom::MAX_ROOMNAME];
	/// 최대 인원
	int m_maxUser;
	/// 채팅방 총인원 수 
	int m_totalPlayers;
	/// 방 개설 시간
	std::string m_inTime;

public:
	explicit Room();
	virtual ~Room() noexcept;

	///Set
	void SetName( const char* name );
	void SetIndex( const int& index );
	void SetMaxUser( const int& num );
	void SetTotalPlayers( const int& totalPlayer );
	void SetRoomInTime( const std::string& inTime );

	///Get
	const char* GetName() const;
	const int& GetIndex();
	const int& GetMaxUser() const;
	const int& GetTotalPlayer() const;
	const std::string& GetRoomInTime() const;

	///Lock
	void StartLock();
	void EndLock();
};
#endif // !ROOM_H
