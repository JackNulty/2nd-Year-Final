#pragma once
#include "Globals.h"
#include "Cells.h"

class Grid {
public:
	Grid();
	void neighbours(std::vector<Cell>& t_grid);
	void checkCell(Cell& t_cell);
	std::vector<int> bfs(int t_startCellID, int t_destinationCellID);
	bool foundTarget = false;
	std::queue<Cell> cellQueue;
	void clearGrid();
private:
	std::vector<Cell> cellMap;

};
