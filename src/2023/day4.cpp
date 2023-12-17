#include <fstream>
#include <set>
#include <string>
#include <iostream>

void parseNums(const std::string& s, size_t start, size_t end, std::set<int>& set) { // end should be index one after last number
	size_t index {start};
	size_t preIndex {start};
	size_t endIndex {start};
	while (preIndex < end) {
		index = s.find_first_of("0123456789",preIndex);
		endIndex = s.find_first_not_of("0123456789",index);
		set.insert(std::stoi(s.substr(index, endIndex-index)));
		preIndex = endIndex;
	}
}

template <typename T>
void print(const T& cont) {
	for (const auto& e : cont){
		std::cout << e << ' ';
	}
	std::cout << '\n';
}

int main() {
	std::ifstream f{"day4.txt"};
	
	long total {0};
	while (f) {
		std::string s;
		std::getline(f,s);
		if (s != "") {
			std::set<int> wins;
			std::set<int> nums;
			const auto pipeIndex {s.find("|")};
			parseNums(s, s.find(":")+2,pipeIndex-1,wins);
			parseNums(s, pipeIndex+2,s.length(),nums);
//			print(wins);
			
			long score {0};
			for (const auto& e : wins) {
				if (nums.find(e) != nums.end()) {
					if (score == 0) {
						++score;
					} else {
						score *=2;
					}
				}
			}
			total+=score;




		}
	}
	std::cout << total << '\n';


	return 0;
}

