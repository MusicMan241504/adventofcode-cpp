#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main() {
	std::ifstream f{"day2.txt"};
	std::string line;
	int count {0};

	while (std::getline(f,line)) { // loop for each line
		std::vector<int> nums;
		size_t prePos {0};
		size_t pos {0};
		do {
			pos = line.find(' ', prePos+1);
			int num {std::stoi(line.substr(prePos,pos-prePos))};
			prePos = pos;


			nums.push_back(num);


		} while (pos != line.npos);


		bool safe {0};
		for (size_t i{0}; i<nums.size(); i++) {
			bool increasing {0};
			bool firstNum {1};
			bool secondNum {1};
			bool safeIter {1};
			int preNum {0};
			for (size_t j{0}; j<nums.size(); j++) {
				int num {nums[j]};
				if (j==i) {
					continue;
				}
				if (firstNum) {
					firstNum = 0;
					preNum = num;
					continue;
				}
				if (secondNum) {
					if (num > preNum) {
						increasing = 1;
					} else {
						increasing = 0;
					}
					secondNum = 0;
				}
				if (increasing) {
					if (not (num-preNum >=1 && num-preNum <=3)) {
						// not safe
						safeIter = 0;
						break;
					}
				} else {
					if (not (preNum-num >=1 && preNum-num <=3)) {
						// not safe
						safeIter = 0;
						break;
					}
				}

				preNum = num;


			}
			if (safeIter) {
				safe = 1;
			}


		}





		if (safe) {
			count++;
			//std::cout << line << '\n';
		}
	}

	std::cout << count << '\n';

	return 0;
}

