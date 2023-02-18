

#ifndef ROOM_H
#define ROOM_H


class Room
{
private:
	std::mutex m_roomLock;

	/// �� ��ȣ
	int m_index;
	/// �� �̸�
	char m_name[InitializeRoom::MAX_ROOMNAME];
	/// �ִ� �ο�
	int m_maxUser;
	/// ä�ù� ���ο� �� 
	int m_totalPlayers;
	/// �� ���� �ð�
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
