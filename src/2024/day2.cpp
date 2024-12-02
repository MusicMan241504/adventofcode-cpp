#include <fstream>
#include <iostream>
#include <string>
int main() {
	std::ifstream f{"day2.txt"};
	std::string line;
	int count {0};
	
	while (std::getline(f,line)) { // loop for each line
		size_t prePos {0};
		size_t pos {0};
		bool increasing {1};
		bool firstNum {1};
		bool secondNum {1};
		bool safe {1};
		int preNum {0};
		do {
			pos = line.find(' ', prePos+1);
			int num {std::stoi(line.substr(prePos,pos-prePos))};
			prePos = pos;

			// do stuff with numbers here

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
					safe = 0;
					break;
				}
			} else {
				if (not (preNum-num >=1 && preNum-num <=3)) {
					// not safe
					safe = 0;
					break;
				}
			}

			preNum = num;

		} while (pos != line.npos);

		if (safe) {
			count++;
			//std::cout << line << '\n';
		}
	}

	std::cout << count << '\n';

	return 0;
}

