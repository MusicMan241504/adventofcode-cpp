#include <fstream>
#include <iostream>
#include <vector>
#include <string>


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

		// add in binary 0 represents add, 1 represents multiply
		// add ranges from 0 to 2^(nums.size()-1)-1
		// can do using binary shift
		for (size_t add{0}; add < (1u << (nums.size()-1u)); add++) {
			unsigned long long int ansTmp {nums[0]};
			for (size_t j{0}; j < nums.size()-1; j++) {
				if ((add & (1 << j)) == 0) { // add
					ansTmp += nums[j+1];
				} else {
					ansTmp *= nums[j+1];
				}
			}
			if (ans == ansTmp) {
				//std::cout << ans << '\n';
				sum += ans;
				break;
			}
		}
	}

	std::cout << sum << '\n';




	return 0;
}

