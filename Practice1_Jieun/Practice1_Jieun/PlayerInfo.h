

#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include "ClientInfo.h"


class PlayerInfo final : public ClientInfo
{
private:
	///�÷��̾� ���� �̸�
	char m_name[InitailizePlayer::MAX_NAME];

	///�÷��̾ �۽� �� �Է����� ���ڿ�
	std::vector< char > m_chattingBuffer;
	int m_roomNumber;

	///�� ���� �ð�
	std::string m_roomInTime;

public:
	explicit PlayerInfo();
	virtual ~PlayerInfo() noexcept;

	///Set
	void SetName( const char* name );
	void SetRoomNumber( const int& num );
	void SetRoomInTime( const std::string time );

	///Get
	const char* GetName() const;
	const std::string_view GetChattingLog();
	const int& GetRoomNumber();
	const std::string& GetRoomInTime() const;

	///ä�ù��� 
	void PushChattingBuffer( char word );
	void ClearChattingBuffer();
	 
};
#endif // !PLAYERINFO_H

