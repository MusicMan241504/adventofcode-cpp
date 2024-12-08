#include <forward_list>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>


void printArr(std::vector<std::string>& arr) {
	for ( const auto& item : arr) {
		std::cout << item << '\n';
	}
	std::cout << '\n';
}


struct Antenna {
	long int x {};
	long int y {};
	char freq {};
};

int main() {
	std::ifstream f{"day8.txt"};
	std::vector<std::string> grid;
	std::string line;
	int sum{0};


	// get rules
	while (std::getline(f,line)) { // loop for each char
		if (line == "") {
			break;
		}
		grid.push_back(line);
	}
	//printArr(grid);

	// get antennas
	std::forward_list<Antenna*> antennas;
	for (long int i{0}; i < (long int)grid.size(); i++) {
		for (long int j{0}; j < (long int)grid[0].size(); j++) {
			if (std::isalnum(grid[i][j])) {
				antennas.emplace_front(new Antenna{j,i,grid[i][j]});
			}
		}
	}

	while (!antennas.empty()) {
		Antenna* antenna {*antennas.begin()};
		antennas.pop_front();
		for (auto a : antennas) {
			if (a->freq == antenna->freq) {
				// for coords (x,y) (w,z)
				// 2 antinodes at (2w-x,2z-y) (2x-w,2y-z)
				long int x1{2*a->x-antenna->x};
				long int y1{2*a->y-antenna->y};
				long int x2{2*antenna->x-a->x};
				long int y2{2*antenna->y-a->y};

				if (x1>=0 && y1>=0 && x1<(long int)grid[0].size() && y1<(long int)grid.size()) {
					if (grid[y1][x1] != '#') {
						grid[y1][x1] = '#';
						sum++;
					}
				}

				if (x2>=0 && y2>=0 && x2<(long int)grid[0].size() && y2<(long int)grid.size()) {
					if (grid[y2][x2] != '#') {
						grid[y2][x2] = '#';
						sum++;
					}
				}
			}
		}
		delete antenna;
	}

	//printArr(grid);


	std::cout << sum << '\n';


	return 0;
}

