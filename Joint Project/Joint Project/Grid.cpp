#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		cellMap.emplace_back(i);
	}
	std::cout << cellMap.size();
	neighbours(cellMap);
}

void Grid::neighbours(std::vector<Cell>& t_grid)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		checkCell(t_grid[i]);
	}
}

void Grid::checkCell(Cell& t_cell)
{
	int row = t_cell.m_id / ROWS;
	int col = t_cell.m_id % COLS;

	// List all neighbors:
	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
		{
			int index = n_row * COLS + n_col;
			t_cell.addNeighbour(index);
		}
	}
}

std::vector<int> Grid::bfs(int t_startCellID, int t_destCellID)
{
	bool goalReached = false;
	std::queue<Cell> queue;

	Cell& start = cellMap.at(t_startCellID);
	queue.emplace(start);
	start.setMarked(true);
	while (queue.empty() == false && goalReached == false)
	{
		std::vector<int>& neighbours = queue.front().neighbours();
		for (int cellIndex = 0; cellIndex < neighbours.size() && !goalReached; cellIndex++)
		{
			Cell& childCell = cellMap.at(neighbours.at(cellIndex));
			if (childCell.m_id == t_destCellID)
			{
				goalReached = true;
				childCell.setPrevious(queue.front().m_id);
			}
			else if (childCell.isMarked() == false)
			{
				childCell.setPrevious(queue.front().m_id);
				childCell.setMarked(true);
				queue.emplace(childCell);
			}
		}
		queue.pop();
	}

	std::vector<int> path;
	if (goalReached == true)
	{
		Cell& currentID = cellMap.at(t_destCellID);
		while (currentID.m_id != t_startCellID)
		{
			path.push_back(currentID.m_id);
			//currentID = currentID.previous(); // No, this creates a Cell with the proper ID, but a previous of -1
			currentID = cellMap.at(currentID.previous()); // Do it this way instead, i.e. retrieve the cell from the cellMap
		}
		path.push_back(t_startCellID);
		std::reverse(path.begin(), path.end());
	}

	std::cout << "Shortest path from " << t_startCellID << " to " << t_destCellID << ": ";
	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] << " ";
	}

	return path;
}

void Grid::clearGrid()
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		cellMap[i].setPrevious(-1);
		cellMap[i].setMarked(false);
	}
}
