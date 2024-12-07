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

void concat(unsigned long long int& ans, int num) {
	auto numTmp {num};
	while (numTmp!=0) {
		numTmp = numTmp/10;
		ans = ans*10;
	}
	ans += num;
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

		// add in binary 0 represents add, 1 represents multiply, 2 represents concatenation
		// add ranges from 0 to 3^(nums.size()-1)-1
		std::vector<unsigned char> addArr(nums.size()-1);
		while (true) {
			unsigned long long int ansTmp {nums[0]};
			for (size_t j{0}; ansTmp <= ans && j < nums.size()-1; j++) {
				if (addArr[j] == 0) { // add
					ansTmp += nums[j+1];
				} else if (addArr[j] == 1) {
					ansTmp *= nums[j+1];
				} else {
					concat(ansTmp, nums[j+1]);
				}
			}
			if (ans == ansTmp) {
				//std::cout << ans << '\n';
				sum += ans;
				break;
			}
			if (addOne(addArr) == 1) {
				break; // overflow
			}
		}
	}

	std::cout << sum << '\n';




	return 0;
}

