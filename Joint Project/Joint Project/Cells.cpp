#include "Cells.h"


Cell::Cell(int t_cellID)
{
	m_id = t_cellID;
}

void Cell::addNeighbour(int t_cellId)
{
	m_neighbours.push_back(t_cellId);
}

std::vector<int>& Cell::neighbours()
{
	return m_neighbours;
}

bool Cell::isMarked() const
{
	return m_marked;
}

void Cell::setMarked(bool t_val)
{
	m_marked = t_val;
}

void Cell::setOrigin(int t_origin)
{
	m_origin = t_origin;
}

int Cell::getOrigin()
{
	return m_origin;
}

void Cell::setPrevious(int t_cellID)
{
	m_previous = t_cellID;
}

int Cell::previous() const
{
	return m_previous;
}
