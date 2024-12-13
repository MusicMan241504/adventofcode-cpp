#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Node{
	char letter{};
	bool visited{0};
	int area{0};
	int perimeter{0};
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

void deleteArr(std::vector<std::vector<Node*>>& arr) {
	for (auto& row : arr) {
		for (auto & e : row) {
			delete e;
		}
	}
}


void calcRegions(std::vector<std::vector<Node*>>& grid, size_t x, size_t y, char c, size_t& area, size_t& perimeter) {
	if (grid[x][y]->letter != c) {
		perimeter++;
		return;
	}
	if (grid[x][y]->visited) {
		return;
	}
	//std::cout << x << ' ' << y << '\n';
	grid[x][y]->visited = 1;
	area++;

	if (x+1 < grid.size()) {
		calcRegions(grid, x+1, y, c, area, perimeter);
	} else {
		perimeter++;
	}
	if (y+1 < grid[0].size()) {
		calcRegions(grid, x, y+1, c, area, perimeter);
	} else {
		perimeter++;
	}
	if (x > 0) {
		calcRegions(grid, x-1, y, c, area, perimeter);
	} else {
		perimeter++;
	}
	if (y > 0) {
		calcRegions(grid, x, y-1, c, area, perimeter);
	} else {
		perimeter++;
	}


	//std::cout << grid[x][y]->area << '\n';

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

	size_t total {0};
	for (size_t i{0}; i< grid.size(); i++) {
		for (size_t j{0}; j< grid[0].size(); j++) {
			size_t area{0};
			size_t perimeter{0};
			calcRegions(grid, i, j, grid[i][j]->letter, area, perimeter);
			if (area != 0) {
				//std::cout << area << ' ' << perimeter << '\n' << '\n';
				total += area*perimeter;
			}
		}
	}


	//printArr(grid);
	
	std::cout << total << '\n';

	deleteArr(grid);


	return 0;

}

