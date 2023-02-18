

#include "pch.h"
#include "ChattingRoom.h"
#include <algorithm>


ChattingRoom::ChattingRoom()
{
	m_accessorIndex.reserve( 20 );
}
ChattingRoom::~ChattingRoom() noexcept = default;

void ChattingRoom::PushAccessor( const SOCKET& socket )
{
	m_accessorIndex.push_back( socket );
	std::cout << socket << "Ãß°¡" << std::endl;
}

void ChattingRoom::PopAccessor( const SOCKET& socket )
{
	std::erase_if( m_accessorIndex,
	[ & ]( const SOCKET& socket2 )
	{
		return socket == socket2;
	} );
}

const std::vector< SOCKET >& ChattingRoom::GetAccessorIndex() const
{
	return m_accessorIndex;
}
