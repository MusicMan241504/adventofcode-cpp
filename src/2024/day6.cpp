#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>


void printArr(std::vector<std::string>& arr) {
	for ( const auto& item : arr) {
		std::cout << item << '\n';
	}
	std::cout << '\n';
}




int main() {
	std::ifstream f{"day6.txt"};
	int count {1};
	std::vector<std::string> grid;
	std::string line;
	
	while (std::getline(f,line)) { // loop for each char
		if (line != "") {
			grid.push_back(line);
		}
	}

	// find guard
	std::array<int,2> pos{0,0}; // x,y
	std::array<int,2> dir{0,-1}; // 
	for (size_t i{0}; i < grid.size(); i++) {
		for (size_t j{0}; j < grid[0].size(); j++) {
			if (grid[i][j] == '^') {
				grid[i][j] = 'X';
				pos[0] = j;
				pos[1] = i;
				break;
			}
		}
	}

	//printArr(grid);

	while (pos[0]+dir[0] >= 0 && pos[1]+dir[1] >= 0 && pos[0]+dir[0] < grid[0].size() && pos[1]+dir[1] < grid.size()) {
		if (grid[pos[1]+dir[1]][pos[0]+dir[0]] != '#') {
			pos[0] += dir[0];
			pos[1] += dir[1];
			if (grid[pos[1]][pos[0]] == '.') {
				count++;
				grid[pos[1]][pos[0]] = 'X';
			}
		} else {
			// rotate
			int tmp = dir[0];
			dir[0] = -dir[1];
			dir[1] = tmp;
		}
		//printArr(grid);
	}



	std::cout << count << '\n';

	return 0;
}

