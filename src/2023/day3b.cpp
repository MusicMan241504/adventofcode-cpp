#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
#include <string>

template <typename T>
void printLoop(const T& vec) {
	for (const auto& e : vec) {
		std::cout << e << '\n';
	}
	std::cout << '\n';
}
int main() {
	std::ifstream f{"day3.txt"};
	std::vector<std::string> vec{};

	while (f) {
		std::string s;
		std::getline(f,s);
		// doesn't add blank line at end of file
		if (s != "") {
			vec.push_back(s);
		}
	}

	//printLoop(vec);
	
	long total {0};
	for (auto row{vec.begin()}; row!=vec.cend(); ++row) {
		size_t index {0};
		size_t preIndex {0};
		while (index != std::string::npos) {
			index = (*row).find_first_of("*",preIndex); // get index of first digit



			// checks symbol
			std::set<int> knownNums{};
			// uses an interator as a pointer to go through the 3 surrounding rows a symbol could be in
			// loop stops when iterator is 2 beyond current so runs for it-1,it,it+1
			// uses max and min to prevent out of bounds
			for (auto rowCheck{std::max(std::prev(row),vec.begin())}; rowCheck != std::min(std::next(row,2),vec.end()); ++rowCheck){
				// uses index to iterate from char before start of num and char after end of num
				// min and max needed to prevent index being out of bounds of string
				for (size_t indexCheck {std::max(index,(size_t)1)-1}; indexCheck<=std::min(index+1,(*row).length()-1); ++indexCheck){
					// is digit
					if (std::isdigit((*rowCheck).at(indexCheck))) {
						// find rest of num
						// find start by searching backwards from known value to find first non num then add 1
						const auto numStart {(*rowCheck).find_last_not_of("0123456789",indexCheck)+1};
						const auto numEnd {(*rowCheck).find_first_not_of("0123456789",indexCheck)};
						const int num {std::stoi((*rowCheck).substr(numStart, numEnd-numStart))};
						knownNums.insert(num);
					}
				}
			}

			// increment counter
			if (knownNums.size() >= 2) {
				long ratio {1};
				for (const auto& num : knownNums) {
					ratio *= num;
				}
				total += ratio;
			}

			// set iterators
			preIndex = index+1;

		}
	}

	std::cout << total << '\n';


	return 0;
}


