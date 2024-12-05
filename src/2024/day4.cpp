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
	std::string xmas {"XMAS"};
	
	while (std::getline(f,line)) { // loop for each char
		grid.push_back(line);
	}


	for (size_t i {0}; i<grid.size(); i++) {
		for (size_t j{0}; j<grid[0].size(); j++) {
			// for ever char
			for (int k{-1}; k <= 1; k++) {
				for (int m{-1}; m<= 1; m++) {
					// for every direction
					bool isXmas{1};
					if (k==0 && m==0) {
						continue;
					}
					if (i+k*3 >= grid.size() || j+m*3 >= grid.size() || i+k*3 < 0 || j+m*3 < 0) {
						continue;
					}
					for (size_t n{0}; n<4;n++) {
						// for every char in each directin
						if (grid[i+k*n][j+m*n] != xmas[n]) {
							isXmas = 0;
						}
					}
					if (isXmas) {
						count++;
					}
				}
			}


		}
	}


	std::cout << count << '\n';

	return 0;
}

