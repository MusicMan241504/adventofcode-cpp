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

bool isOrdered(std::vector<int>& nums, std::vector<std::vector<int>>& rules) {
	bool ordered {1};
	for (auto rule : rules) {
		bool isNum2 {0};
		for (size_t i{0}; i< nums.size(); i++) {
			if (nums[i] == rule[1]) {
				isNum2 = 1;
			}
			if (isNum2 && nums[i] == rule[0]) {
				ordered = 0;
			}
		}
	}
	return ordered;
}



int main() {
	std::ifstream f{"day5.txt"};
	std::vector<std::vector<int>> rules;
	std::string line;


	// get rules
	while (std::getline(f,line)) { // loop for each char
		if (line == "") {
			break;
		}
		size_t pos {line.find('|')};
		std::string num1 {line.substr(0,pos)};
		std::string num2 {line.substr(pos+1,line.size()-pos)};
		std::vector<int> rule {std::stoi(num1),std::stoi(num2)};
		rules.push_back(rule);
	}

	// get arrays
	std::vector<std::vector<int>> numArr;
	while (std::getline(f,line)) {
		std::vector<int> nums;
		size_t pos {0};
		size_t pos2 {line.find(',',pos+1)};
		while (pos2 != line.npos) {

			nums.push_back(std::stoi(line.substr(pos,pos2-pos)));
			pos = pos2+1;
			pos2 = line.find(',',pos);
		}
		nums.push_back(std::stoi(line.substr(pos,line.size()-pos)));
		numArr.push_back(nums);
	}

	// check rules
	int sum {0};
	for (auto nums : numArr) {
		bool ordered {isOrdered(nums,rules)};


		if (ordered) { // sort order
			sum+= nums[nums.size()/2];
		}
	}
	std::cout << sum << '\n';




	return 0;
}

