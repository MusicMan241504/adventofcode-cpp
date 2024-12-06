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
	int count {0};
	std::vector<std::string> gridConst;
	std::string line;

	while (std::getline(f,line)) { // loop for each char
		if (line != "") {
			gridConst.push_back(line);
		}
	}

	// find guard
	std::array<int,2> posConst{0,0}; // x,y
	std::array<int,2> dirConst{0,-1}; // 
	for (size_t i{0}; i < gridConst.size(); i++) {
		for (size_t j{0}; j < gridConst[0].size(); j++) {
			if (gridConst[i][j] == '^') {
				gridConst[i][j] = 'X';
				posConst[0] = j;
				posConst[1] = i;
				break;
			}
		}
	}

	//printArr(gridConst);

	for (size_t i{0}; i < gridConst.size(); i++) {
		for (size_t j{0}; j < gridConst[0].size(); j++) {
			std::vector<std::string> grid {gridConst};
			if (grid[i][j] == '.') {

				grid[i][j] = 'O';
			} else {
				continue;
			}

			std::array<int,2> pos {posConst};
			std::array<int,2> dir {dirConst};

			int looping {0};
			while (pos[0]+dir[0] >= 0 && pos[1]+dir[1] >= 0 && pos[0]+dir[0] < grid[0].size() && pos[1]+dir[1] < grid.size()) {
				if (grid[pos[1]+dir[1]][pos[0]+dir[0]] != '#' && grid[pos[1]+dir[1]][pos[0]+dir[0]] != 'O') {
					pos[0] += dir[0];
					pos[1] += dir[1];
					if (grid[pos[1]][pos[0]] == '.') {
						grid[pos[1]][pos[0]] = 'X';
					}
				} else {
					// rotate
					int tmp = dir[0];
					dir[0] = -dir[1];
					dir[1] = tmp;
					if (grid[pos[1]][pos[0]] == '+') {
						// loop
						looping++;
					} else {
						grid[pos[1]][pos[0]] = '+';
					}
				}
				//printArr(grid);
				if (looping >= 4) {
					count++;
					//printArr(grid);
					break;
				}
			}
		}
	}


	std::cout << count << '\n';

	return 0;
}

