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

			std::cout << (e->height == 0 && e->visited) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void pathFind(std::vector<std::vector<Node*>>& grid, size_t i, size_t j, int height, int score) {	
	if (grid[i][j]->height != height) {
		return;
	}
	if (grid[i][j]->visited) {
		return;
	}
	if (height == 0) {
		grid[i][j]->visited = 1;
		return;
	}
	if (grid[i][j]->height == height) {
		if (i+1 < grid.size()) {
			pathFind(grid, i+1, j, height-1, score);
		}
		if (j+1 < grid.size()) {
			pathFind(grid, i, j+1, height-1, score);
		}
		if (i > 0) {
			pathFind(grid, i-1, j, height-1, score);
		}
		if (j > 0) {
			pathFind(grid, i, j-1, height-1, score);
		}
		//grid[i][j]->score = score;
		grid[i][j]->visited = 1;
	}
}


int main() {
	std::ifstream f{"day10.txt"};
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
			if (grid[i][j]->height == 9) {
				//grid[i][j]->score = 1;
				pathFind(grid, i, j, 9, 1);
				//std::cout << grid[i][j]->score << '\n';
				grid[i][j]->visited = 1;
				//printArr(grid);

				// reset values for 0s
				for (size_t x{0}; x < grid.size(); x++) {
					for (size_t y{0}; y < grid[0].size(); y++) {
						if (grid[x][y]->height == 0 && grid[x][y]->visited == 1) {
							grid[x][y]->score++;
						}
						grid[x][y]->visited = 0;
					}
				}
							
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
//	printArr(grid);

	std::cout << count << '\n';
	
	return 0;

}

