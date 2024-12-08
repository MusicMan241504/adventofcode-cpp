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
				// antinodes occur at n*(w-x,z-y) distance from (x,y)
				long int xDiff{a->x-antenna->x};
				long int yDiff{a->y-antenna->y};

				// forward iteration
				long int x{a->x};
				long int y{a->y};
				for (; x>=0 && y>=0 && x<(long int)grid[0].size() && y<(long int)grid.size(); x+=xDiff, y+=yDiff) {
					if (grid[y][x] != '#') {
						grid[y][x] = '#';
						sum++;
					}
				}

				// backward iteration
				x = a->x;
				y = a->y;
				for (; x>=0 && y>=0 && x<(long int)grid[0].size() && y<(long int)grid.size(); x-=xDiff, y-=yDiff) {
					if (grid[y][x] != '#') {
						grid[y][x] = '#';
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

