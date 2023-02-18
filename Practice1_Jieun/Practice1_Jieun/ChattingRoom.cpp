

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
	auto iter = find( m_accessorIndex.begin(), m_accessorIndex.end(), socket );
	if (iter != m_accessorIndex.end())
		m_accessorIndex.erase( iter );
}

const std::vector< SOCKET >& ChattingRoom::GetAccessorIndex() const
{
	return m_accessorIndex;
}
