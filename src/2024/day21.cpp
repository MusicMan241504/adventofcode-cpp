#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// Find shortest path from start char to end char
void getMoves(char start, char end, std::vector<std::vector<char>>& grid, std::list<std::string>& movesList) {
	// get coords of start and end
	size_t startX{0};
	size_t startY{0};
	size_t endX{0};
	size_t endY{0};
	for (size_t y{0}; y < grid.size(); y++) {
		for (size_t x{0}; x < grid[0].size(); x++) {
			if (grid[y][x] == start) {
				startX = x;
				startY = y;
			}
			if (grid[y][x] == end) {
				endX = x;
				endY = y;
			}
		}
	}


	std::string moves1;

	if (grid[startY][endX] != ' ') {
		// if x must increase
		if (endX > startX) {
			for (size_t i{startX}; i < endX; i++) {
				moves1 += '>';
			}
		}
		// if x must decrease
		if (endX < startX) {
			for (size_t i{endX}; i < startX; i++) {
				moves1 += '<';
			}
		}
		// if y must increase
		if (endY > startY) {
			for (size_t i{startY}; i < endY; i++) {
				moves1 += 'v';
			}
		}
		// if y must decrease
		if (endY < startY) {
			for (size_t i{endY}; i < startY; i++) {
				moves1 += '^';
			}
		}
		movesList.push_back(moves1);
	}

	std::string moves2;

	if (grid[endY][startX] != ' ' && startX != endX && startY != endY) {
		// if y must increase
		if (endY > startY) {
			for (size_t i{startY}; i < endY; i++) {
				moves2 += 'v';
			}
		}
		// if y must decrease
		if (endY < startY) {
			for (size_t i{endY}; i < startY; i++) {
				moves2 += '^';
			}
		}
		// if x must increase
		if (endX > startX) {
			for (size_t i{startX}; i < endX; i++) {
				moves2 += '>';
			}
		}
		// if x must decrease
		if (endX < startX) {
			for (size_t i{endX}; i < startX; i++) {
				moves2 += '<';
			}
		}
		movesList.push_back(moves2);
	}
}



int main() {
	std::ifstream f{"day21.txt"};

	std::vector<std::vector<char>> numberPad{
		{'7','8','9'},
			{'4','5','6'},
			{'1','2','3'},
			{' ','0','A'}};

	std::vector<std::vector<char>> arrowPad{
		{' ','^','A'},
			{'<','v','>'}};

	int total {0};

	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}


		std::list<std::string> movesList{line};
		for (size_t i{0}; i < 3; i++) {
			std::list<std::string> newMovesList;
			for (auto moves : movesList) {
				std::vector<std::list<std::string>> movesNew;
				char preChar{'A'};
				for (char c : moves) {
					std::list<std::string> movesListTmp;
					if (i == 0) {
						getMoves(preChar, c, numberPad, movesListTmp);
					} else {
						getMoves(preChar, c, arrowPad, movesListTmp);
					}
					movesNew.push_back(movesListTmp);
						
					preChar = c;
				}

				// get all combinations of moves and store into newMovesList
				// find number of combinations needed
				size_t pairCount{0};
				for (auto movesNewPair : movesNew) {
					if (movesNewPair.size() == 2) {
						pairCount++;
					}
				}
				size_t combinations{(size_t)1 << pairCount};
				for (size_t j{0}; j < combinations; j++) {
					std::string moveTmp;
					size_t k{0};
					for (auto movesNewPair : movesNew) {
						if (movesNewPair.size() != 2) {
							moveTmp += movesNewPair.front();
							moveTmp += 'A';
							// do not increment k
							continue;
						}
						if (j & (1 << k)) { // if kth bit of j = 1
							moveTmp += movesNewPair.front();
						} else {
							moveTmp += movesNewPair.back();
						}
						moveTmp += 'A';
						k++;
					}
					//std::cout << moveTmp << '\n';
					newMovesList.push_back(moveTmp);
				}

					

			}
			movesList = newMovesList;
		}
		// get lowest length
		size_t len{999999999};
		for (auto moves : movesList) {
			if (moves.size() < len) {
				len = moves.size();
			}
		}
		total += len*std::stoi(line.substr(0,3));
		//std::cout << len << '\n';
	}

	std::cout << total << '\n';

	return 0;
}

