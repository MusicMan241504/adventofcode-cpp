#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Node{
	char letter{};
	bool visited{0};
	bool xPos{0};
	bool xNeg{0};
	bool yPos{0};
	bool yNeg{0};
	bool counted{0};
	int id{0};
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


void calcRegions(std::vector<std::vector<Node*>>& grid, size_t x, size_t y, char c, size_t& area, int xDir, int yDir, int id) {
	if (grid[x][y]->letter != c) {
		if (xDir == 1) {
			grid[x-1][y]->xPos = 1;
		} else if (xDir == -1) {
			grid[x+1][y]->xNeg = 1;
		} else if (yDir == 1) {
			grid[x][y-1]->yPos = 1;
		} else if (yDir == -1) {
			grid[x][y+1]->yNeg = 1;
		}
		return;
	}
	if (grid[x][y]->visited) {
		return;
	}
	//std::cout << x << ' ' << y << '\n';
	grid[x][y]->visited = 1;
	grid[x][y]->id = id;
	area++;

	if (x+1 < grid.size()) {
		calcRegions(grid, x+1, y, c, area, 1, 0, id);
	} else {
		grid[x][y]->xPos = 1;
	}
	if (y+1 < grid[0].size()) {
		calcRegions(grid, x, y+1, c, area, 0, 1, id);
	} else {
		grid[x][y]->yPos = 1;
	}
	if (x > 0) {
		calcRegions(grid, x-1, y, c, area, -1, 0, id);
	} else {
		grid[x][y]->xNeg = 1;
	}
	if (y > 0) {
		calcRegions(grid, x, y-1, c, area, 0, -1, id);
	} else {
		grid[x][y]->yNeg = 1;
	}


	//std::cout << grid[x][y]->area << '\n';

}

void deleteArr(std::vector<std::vector<Node*>>& arr) {
	for (auto& row : arr) {
		for (auto & e : row) {
			delete e;
		}
	}
}

void printSides(std::vector<int>& arr) {
	for (auto& e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}


int main() {
	std::ifstream f{"day12.txt"};
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

	std::vector<int> areas;
	int id{0};
	for (size_t i{0}; i< grid.size(); i++) {
		for (size_t j{0}; j< grid[0].size(); j++) {
			size_t area{0};
			calcRegions(grid, i, j, grid[i][j]->letter, area, 0, 0, id);
			if (area != 0) {
				areas.push_back(area);
				id++;
			}
		}
	}

	std::vector<int> sides(areas.size(),0);

	// x pos so increment y values
	char c{'0'};
	bool fence{0};
	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j]->xPos) {
				if (grid[i][j]->letter != c || !fence) {
					sides[grid[i][j]->id] ++;
				}
				fence = 1;
			} else {
				fence = 0;
			}
			c = grid[i][j]->letter;
		}
		fence = 0;
		c = '0';
	}
	//printSides(sides);
	// x neg so increment y values
	c = '0';
	fence = 0;
	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j]->xNeg) {
				if (grid[i][j]->letter != c || !fence) {
					sides[grid[i][j]->id] ++;
				}
				fence = 1;
			} else {
				fence = 0;
			}
			c = grid[i][j]->letter;
		}
		fence = 0;
		c = '0';
	}
	//printSides(sides);
	// y pos so increment x values
	c = '0';
	fence = 0;
	for (size_t j{0}; j < grid[0].size(); j++) {
		for (size_t i{0}; i < grid.size(); i++) {
			if (grid[i][j]->yPos) {
				if (grid[i][j]->letter != c || !fence) {
					sides[grid[i][j]->id] ++;
				}
				fence = 1;
			} else {
				fence = 0;
			}
			c = grid[i][j]->letter;
		}
		fence = 0;
		c = '0';
	}
	//printSides(sides);
	// y neg so increment x values
	c = '0';
	fence = 0;
	for (size_t j{0}; j < grid[0].size(); j++) {
		for (size_t i{0}; i < grid.size(); i++) {
			if (grid[i][j]->yNeg) {
				if (grid[i][j]->letter != c || !fence) {
					sides[grid[i][j]->id] ++;
				}
				fence = 1;
			} else {
				fence = 0;
			}
			c = grid[i][j]->letter;
		}
		fence = 0;
		c = '0';
	}
	//printSides(sides);


	// calculate total
	int total{0};
	for (size_t i {0}; i < areas.size(); i++) {
		total += areas[i]*sides[i];
	}


	//printSides(sides);
	//printArr(grid);

	std::cout << total << '\n';


	deleteArr(grid);

	return 0;

}

