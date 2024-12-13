#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Node{
	char letter{};
	bool visited{0};

	// 0 = no fence
	// 1 = down (x+1)
	// 2 = right (y+1)
	// 3 = up (x-1)
	// 4 = left (y-1)
	//int fenceDirection{0};
	bool fenceXPos{0};
	bool fenceYPos{0};
	bool fenceXNeg{0};
	bool fenceYNeg{0};

};


void printArr(std::vector<std::vector<Node*>>& arr) {
	for (const auto& row : arr) {
		for (const auto& e : row) {
			std::cout << e->letter;
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}


// Accepts coords of a node and detects if new fence side must be created
// coords are of the node just before the fence with fence between this node and the one specified by adding direction vector to this node
bool checkFence(std::vector<std::vector<Node*>>& grid, size_t x, size_t y, char c, int xDir, int yDir) {
	if (yDir == 1) {
		if (x>0 && grid[x-1][y]->letter == c && grid[x-1][y]->fenceYPos == 1) {
			return 0;
		}
		if (x+1 < grid.size() && grid[x+1][y]->letter == c && grid[x+1][y]->fenceYPos == 1) {
			return 0;
		}
	}
	if (yDir == -1) {
		if (x>0 && grid[x-1][y]->letter == c && grid[x-1][y]->fenceYNeg == 1) {
			return 0;
		}
		if (x+1 < grid.size() && grid[x+1][y]->letter == c && grid[x+1][y]->fenceYNeg == 1) {
			return 0;
		}
	}
	if (xDir == 1) {
		if (y>0 && grid[x][y-1]->letter == c && grid[x][y-1]->fenceXPos == 1) {
			return 0;
		}
		if (y+1 < grid[0].size() && grid[x][y+1]->letter == c && grid[x][y+1]->fenceXPos == 1) {
			return 0;
		}
	}
	if (xDir == -1) {
		if (y>0 && grid[x][y-1]->letter == c && grid[x][y-1]->fenceXNeg == 1) {
			return 0;
		}
		if (y+1 < grid[0].size() && grid[x][y+1]->letter == c && grid[x][y+1]->fenceXNeg == 1) {
			return 0;
		}
	}


	return 1;
}


void calcRegions(std::vector<std::vector<Node*>>& grid, size_t x, size_t y, char c, size_t& area, size_t& perimeter, int xDir, int yDir) {
	if (grid[x][y]->letter != c) {
		if (checkFence(grid, x-xDir, y-yDir, c, xDir, yDir)) {
			perimeter++;
		}
		if (xDir == 1) {
			grid[x-xDir][y-yDir]->fenceXPos = 1;
		} else if (xDir == -1) {
			grid[x-xDir][y-yDir]->fenceXNeg = 1;
		} else if (yDir == 1) {
			grid[x-xDir][y-yDir]->fenceYPos = 1;
		} else if (yDir == -1) {
			grid[x-xDir][y-yDir]->fenceYNeg = 1;
		}
		return;
	}
	if (grid[x][y]->visited) {
		return;
	}
	//std::cout << x << ' ' << y << '\n';
	grid[x][y]->visited = 1;
	area++;

	if (x+1 < grid.size()) {
		calcRegions(grid, x+1, y, c, area, perimeter, 1, 0);
	} else {
		if (checkFence(grid, x, y, c, 1, 0)) {
			perimeter++;
		}
		grid[x][y]->fenceXPos = 1;
	}
	if (y+1 < grid[0].size()) {
		calcRegions(grid, x, y+1, c, area, perimeter, 0, 1);
	} else {
		if (checkFence(grid, x, y, c, 0, 1)) {
			perimeter++;
		}
		grid[x][y]->fenceYPos = 1;
	}
	if (x > 0) {
		calcRegions(grid, x-1, y, c, area, perimeter, -1, 0);
	} else {
		if (checkFence(grid, x, y, c, -1, 0)) {
			perimeter++;
		}
		grid[x][y]->fenceXNeg = 1;
	}
	if (y > 0) {
		calcRegions(grid, x, y-1, c, area, perimeter, 0, -1);
	} else {
		if (checkFence(grid, x, y, c, 0, -1)) {
			perimeter++;
		}
		grid[x][y]->fenceYNeg = 1;
	}


	//std::cout << grid[x][y]->area << '\n';

}



int main() {
	std::ifstream f{"test.txt"};
	std::vector<std::vector<Node*>> grid;

	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		std::vector<Node*> row(line.size());
		for (size_t i {0}; i < line.size(); i++) {
			row[i] = new Node{line[i]};
		}
		grid.push_back(row);
	}

	size_t total {0};
	for (size_t i{0}; i< grid.size(); i++) {
		for (size_t j{0}; j< grid[0].size(); j++) {
			size_t area{0};
			size_t perimeter{0};
			calcRegions(grid, i, j, grid[i][j]->letter, area, perimeter, 0, 0);
			if (area != 0) {
				std::cout << area << ' ' << perimeter << '\n' << '\n';
				total += area*perimeter;
			}
		}
	}


	//printArr(grid);

	std::cout << total << '\n';




	return 0;

}

