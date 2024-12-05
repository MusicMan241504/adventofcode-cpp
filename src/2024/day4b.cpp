#include <fstream>
#include <iostream>
#include <vector>
#include <string>


void printArr(std::vector<bool>& charCheck) {
	for ( const auto& item : charCheck) {
		std::cout << item << ' ';
	}
	std::cout << '\n';
}




int main() {
	std::ifstream f{"day4.txt"};
	int count {0};
	std::vector<std::string> grid;
	std::string line;

	while (std::getline(f,line)) { // loop for each char
		grid.push_back(line);
	}


	for (size_t i {0}; i<grid.size(); i++) {
		for (size_t j{0}; j<grid[0].size(); j++) {
			// for ever char
			bool isXmas{1};
			if (i+1 >= grid.size() || j+1 >= grid.size() || i < 1 || j < 1) {
				continue;
			}

			if (grid[i][j] != 'A') {
				continue;
			}

			if ((grid[i-1][j-1] != 'M' || grid[i+1][j+1] != 'S')
					&&
				(grid[i-1][j-1] != 'S' || grid[i+1][j+1] != 'M')) {
				isXmas = 0;
			}

			if ((grid[i-1][j+1] != 'M' || grid[i+1][j-1] != 'S')
					&&
				(grid[i-1][j+1] != 'S' || grid[i+1][j-1] != 'M')) {
				isXmas = 0;
			}
				


			if (isXmas) {
				count++;
			}


		}
	}


	std::cout << count << '\n';

	return 0;
}

