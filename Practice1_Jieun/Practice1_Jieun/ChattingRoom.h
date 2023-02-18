

#ifndef CHATTINGROOM_H
#define CHATTINGROOM_H
#include "Room.h"


class ChattingRoom: public Room
{
private:
	/// 해당 채팅방 접속자들의 소켓들
	std::vector< SOCKET > m_accessorIndex;

public:
	explicit ChattingRoom();
	virtual ~ChattingRoom() noexcept;

	///Set
	///...

	///Get
	const std::vector< SOCKET >& GetAccessorIndex() const;

	///접속사 추가 및 삭제 
	void PushAccessor(const SOCKET& socket);
	void PopAccessor(const SOCKET& socket);
};
#endif // !CHATTINGROOM_H
