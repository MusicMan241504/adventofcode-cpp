#include <forward_list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


struct Node {
	int height{};
	int score{};
	bool visited{};
};

void printArr(std::vector<std::vector<Node*>>& arr) {
	for (const auto& r : arr) {
		for (const auto e : r) {

			std::cout << e->score << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int pathFind(std::vector<std::vector<Node*>>& grid, size_t i, size_t j, int height) {	
	if (grid[i][j]->height != height) {
		return 0;
	}
	if (grid[i][j]->visited) {
		return grid[i][j]->score;
	}
	if (height == 9) {
		grid[i][j]->score = 1;
		return 1;
	}
	if (grid[i][j]->height == height) {
		if (i+1 < grid.size()) {
			grid[i][j]->score += pathFind(grid, i+1, j, height+1);
		}
		if (j+1 < grid.size()) {
			grid[i][j]->score += pathFind(grid, i, j+1, height+1);
		}
		if (i > 0) {
			grid[i][j]->score += pathFind(grid, i-1, j, height+1);
		}
		if (j > 0) {
			grid[i][j]->score += pathFind(grid, i, j-1, height+1);
		}
		grid[i][j]->visited = 1;
		return grid[i][j]->score;
	}

	return 0;
}


int main() {
	std::ifstream f{"test.txt"};
	std::string line;
	std::vector<std::vector<Node*>> grid;

	for (size_t i{0}; std::getline(f,line); i++) {
		if (line == "") {
			break;
		}
		std::vector<Node*> row(line.size());
		for (size_t j{0}; j < line.size(); j++) {
			row[j] = new Node{(line[j]-'0'),0,0};
		}
		grid.emplace_back(row);
	}

	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j]->height == 0) {
				grid[i][j]->score = pathFind(grid, i, j, 0);
				//std::cout << grid[i][j]->score << '\n';
				grid[i][j]->visited = 1;
			}
		}
	}

	// count score
	long int count{0};
	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j]->height == 0) {
				count += grid[i][j]->score;
			}
		}
	}
	printArr(grid);

	std::cout << count << '\n';
	
	return 0;

}

