#pragma once
#include <iostream>
#include <vector>
#include "Globals.h"

class Cell {
private:
	bool m_marked{ false }; // this is used by the algorithm
	std::vector<int> m_neighbours; // a one dimensional array containing all the neighbours
	int m_origin = 0;
	int m_previous{ -1 };
public:
	int m_id; //id for this cell
	Cell(int t_cellID = -1); // constructor function to accept and store the cell id

	void addNeighbour(int t_cellId); // To add a neighbour

	std::vector<int>& neighbours(); // To return the list of neighbours

	bool isMarked() const; // returns the member variable m_marked;

	void setMarked(bool t_val); // setter method to set the value of member m_marked
	void setOrigin(int t_origin);
	int getOrigin();
	void setPrevious(int t_cellID);
	int previous() const;
};
