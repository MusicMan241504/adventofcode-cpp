#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



void printArr(std::list<std::string>& arr) {
	for (const auto& e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}


std::string mult2024(std::string num) {
	unsigned long numInt {std::stoul(num)};
	num = std::to_string(numInt*2024);
	return num;
}


unsigned long long int countFunc(std::string num, int count, std::vector<std::vector<unsigned long long int>>& memo) {
	if (std::stoull(num) < memo.size() && memo[std::stoull(num)][count] != 0) {
		return memo[std::stoull(num)][count];
	}
	unsigned long long int val {0};
	if (count == 0) {
		return 1;
	}
	if (num == "0") {
		val += countFunc("1", count-1, memo);
	} else if (num.size()%2 == 0) {
		std::string tmp {num.substr(num.size()/2, num.size()/2)};
		// remove leading zeroes from tmp
		auto pos {tmp.find_first_of("123456789")};
		if (pos == tmp.npos) {
			tmp = "0";
		} else {
			tmp = tmp.substr(pos, tmp.size()-pos);
		}
		val += countFunc(tmp, count-1, memo);
		val += countFunc(num.substr(0,num.size()/2), count-1, memo);
	} else {
		val += countFunc(mult2024(num), count-1, memo);
	}
	if (std::stoull(num) < memo.size()) {
		memo[std::stoull(num)][count] = val;
	}
	return val;
}



int main() {
	std::ifstream f{"day11.txt"};
	std::list<std::string> nums;

	std::string line;
	std::getline(f,line);
	size_t preI {0};
	for (size_t i{0}; i < line.size(); i++) {
		if (line[i] == ' ') {
			nums.push_back(line.substr(preI,i-preI));
			preI = i+1;
		}
	}
	nums.push_back(line.substr(preI, line.size()-preI));

	// memoization
	std::vector<std::vector<unsigned long long int>> memo(1000, std::vector<unsigned long long int>(76,0));




	unsigned long long int score{0};
	for (const auto& e : nums) {
		unsigned long long int scoreTmp {countFunc(e, 75, memo)};
		score += scoreTmp;
		//std::cout << scoreTmp << '\n';
	}


	std::cout << score << '\n';



	return 0;

}

