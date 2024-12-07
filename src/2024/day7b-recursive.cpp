#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int addOne(std::vector<unsigned char>& arr) { // base 3 array
	for (size_t i{0}; i < arr.size(); i++) {
		if (arr[i] != 2) {
			arr[i]++;
			return 0;
		} else {
			arr[i] = 0;
		}
	}
	return 1;
}

unsigned long long int concat(unsigned long long int ans, unsigned int num) {
	auto numTmp {num};
	while (numTmp!=0) {
		numTmp = numTmp/10;
		ans = ans*10;
	}
	return ans + num;
}

bool calculate(std::vector<unsigned int>& nums, unsigned long long int ans, unsigned long long int runningTotal, size_t numIndex) {
	if (runningTotal > ans) {
		return 0;
	}
	if (numIndex >= nums.size()) {
		if (ans == runningTotal) {
			return 1; // found operators
		} else {
			return 0; // not found operators
		}
	}
	bool r1 {calculate(nums, ans, runningTotal+nums[numIndex], numIndex+1)};
	bool r2 {calculate(nums, ans, runningTotal*nums[numIndex], numIndex+1)};
	bool r3 {calculate(nums, ans, concat(runningTotal,nums[numIndex]), numIndex+1)};
	if (r1 || r2 || r3) {
		return 1;
	} else {
		return 0;
	}
}


int main() {
	std::ifstream f{"day7.txt"};
	std::string line;
	unsigned long long int sum {0};


	// get rules
	while (std::getline(f,line)) { // loop for each char
		if (line == "") {
			break;
		}
		std::vector<unsigned int> nums;
		unsigned long long int ans {0};
		size_t pos {line.find(':')};
		ans = std::stoull(line.substr(0,pos));

		pos+=2;
		size_t pos2 {line.find(' ',pos)};
		while (pos2 != line.npos) {
			//std::cout << line.substr(pos, pos2-pos) << '\n';
			nums.push_back(std::stoi(line.substr(pos, pos2-pos)));
			pos = pos2+1;
			pos2 = line.find(' ',pos);
		}
		//std::cout << line.substr(pos, line.size()-pos) << '\n';
		nums.push_back(std::stoi(line.substr(pos, line.size()-pos)));

		
		if (calculate(nums, ans, 0, 0)) {
			//std::cout << ans << '\n';
			sum+=ans;
		}

	}

	std::cout << sum << '\n';




	return 0;
}

