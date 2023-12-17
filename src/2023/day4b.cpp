#include <fstream>
#include <set>
#include <string>
#include <iostream>
#include <array>

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
	std::array<int,211> counts{};
	counts.fill(1);
	
	long total {0};
	int cardNum {1};
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
			
			int bonusCardNum = cardNum+1;
			for (const auto& e : wins) {
				if (nums.find(e) != nums.end()) { // match found
					counts[bonusCardNum-1] += counts[cardNum-1];
					++bonusCardNum;
				}
			}
			total += counts[cardNum-1];




		}
		++cardNum;
	}
	std::cout << total << '\n';
//	print(counts);


	return 0;
}

