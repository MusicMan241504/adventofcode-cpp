#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

// Find shortest path from start char to end char
std::list<std::string> getMoves(char start, char end, std::vector<std::vector<char>>& grid) {
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

	std::list<std::string> output;

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
		output.push_back(moves1);
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
		output.push_back(moves2);
	}
	return output;
}

unsigned long long int getLength(std::string input, size_t i, std::vector<std::vector<char>>& numberPad, std::vector<std::vector<char>>& arrowPad, std::vector<std::unordered_map<std::string, unsigned long long int>>& memo) {
	if (i == 26) {
		return input.size();
	}
	
	if (memo[i].contains(input)) {
		return memo[i][input];
	}


	unsigned long long int len{0};
	char preChar{'A'};
	for (auto c : input) {
		std::list<std::string> movesList;
		if (i == 0) {
			movesList = getMoves(preChar, c, numberPad);
		} else {
			movesList = getMoves(preChar, c, arrowPad);
		}
		unsigned long long int individualLen{999999999999999999};
		for (auto moves : movesList) {
			//std::cout << i << ' ' << preChar << ": " << moves << "A\n";
			unsigned long long int tmpLen{getLength(moves+'A', i+1, numberPad, arrowPad, memo)};
			if (tmpLen < individualLen) {
				individualLen = tmpLen;
			}
		}
		//std::cout << i << ' ' << individualLen << '\n';
		len += individualLen;
		
		preChar = c;
	}
	//std::cout << '\n';
	memo[i][input] = len;
	return len;
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

	
	std::vector<std::unordered_map<std::string, unsigned long long int>> memo(26,std::unordered_map<std::string, unsigned long long int>());


	unsigned long long int total {0};

	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}

		total += getLength(line, 0, numberPad, arrowPad, memo)*stoi(line.substr(0,3));
		//std::cout << total << '\n';


	}

	std::cout << total << '\n';

	return 0;
}

