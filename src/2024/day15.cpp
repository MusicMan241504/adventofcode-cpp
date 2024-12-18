#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void printArr(T& arr) {
	for (const auto& e : arr) {
		std::cout << e << '\n';
	}
	std::cout << '\n';
}

bool moveRobot(std::vector<std::string>& grid, size_t x, size_t y, int xDir, int yDir) {
	if (x+xDir < 0 || x+xDir >= grid[0].size() || y+yDir < 0 || y+yDir >= grid.size()) {
		return 0;
	}

	size_t newX{x+xDir};
	size_t newY{y+yDir};
	if (grid[newY][newX] == '#') {
		return 0;
	}

	if (grid[newY][newX] == '.') {
		grid[newY][newX] = grid[y][x];
		grid[y][x] = '.';
		return 1;
	}
	
	if (grid[newY][newX] == 'O') {
		if (moveRobot(grid, newX, newY, xDir, yDir)) {
			grid[newY][newX] = grid[y][x];
			grid[y][x] = '.';
			return 1;
		}
	}
	return 0;
}




int main() {
	std::ifstream f{"day15.txt"};


	std::vector<std::string> grid;
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		grid.push_back(line);
	}

	// find robot
	size_t x{0};
	size_t y{0};
	for (; y < grid.size(); y++) {
		x = 0;
		for (; x < grid[0].size(); x++) {
			if (grid[y][x] == '@') {
				goto endloop;
			}
		}
	}
endloop:

	char c;
	while (f >> c) {
		if (c == '\n') {
			continue;
		}

		//std::cout << c << '\n';

		// get direction
		int xDir{0};
		int yDir{0};
		switch (c) {
			case '^':
				yDir = -1;
				break;
			case '>':
				xDir = 1;
				break;
			case '<':
				xDir = -1;
				break;
			case 'v':
				yDir = 1;
				break;
		}
		if (moveRobot(grid,x,y,xDir,yDir)) {
			x+=xDir;
			y+=yDir;
		}
		//printArr(grid);
	}

	// calulate GPS
	int totalGPS{0};
	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j] == 'O') {
				totalGPS += 100*i+j;
			}
		}
	}

	std::cout << totalGPS << '\n';
		





	return 0;

}

