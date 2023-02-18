

#include "pch.h"
#include "Room.h"


Room::Room( ) : m_index( -1 ), m_name( "" ), m_maxUser( 0 ), m_totalPlayers( 0 )
{
}

Room::~Room() noexcept = default;

void Room::StartLock()
{
	m_roomLock.lock();
}

void Room::EndLock()
{
	m_roomLock.unlock();
}

void Room::SetName( const char* name )
{
	strcpy_s(m_name, name);
}

void Room::SetIndex( const int& index )
{
	m_index = index;
}

void Room::SetMaxUser( const int& num )
{
	m_maxUser = num;
}

void Room::SetTotalPlayers( const int& totalPlayer )
{
	m_totalPlayers = totalPlayer;
}

void Room::SetRoomInTime( const std::string& inTime )
{
	m_inTime = inTime;
}

const char* Room::GetName() const
{
	return m_name;
}

const int& Room::GetIndex()
{
	return m_index;
}

const int& Room::GetMaxUser() const
{
	return m_maxUser;
}

const int& Room::GetTotalPlayer() const
{
	return m_totalPlayers;
}

const std::string& Room::GetRoomInTime() const
{
	return m_inTime;
}
