#include <list>
#include <fstream>
#include <iostream>
#include <string>



void printArr(std::list<std::string>& arr) {
	for (const auto& e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}


void mult2024(std::string& num) {
	unsigned long numInt {std::stoul(num)};
	num = std::to_string(numInt*2024);
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

	//printArr(nums);

	for (size_t i{0}; i < 25; i++) {
		for (auto it{nums.begin()}; it != nums.end(); it++) {
			//std::cout << *it << '\n';
			if (*it == "0") {
				*it = "1";
			} else if ((*it).size() %2 == 0) {
				std::string tmp {(*it).substr((*it).size()/2,(*it).size()/2)};
				// remove leading zeroes from tmp
				auto pos {tmp.find_first_of("123456789")};
				if (pos == tmp.npos) {
					tmp = "0";
				} else {
					tmp = tmp.substr(pos, tmp.size()-pos);
				}


				*it = (*it).substr(0,(*it).size()/2);
				it++;
				nums.insert(it, tmp);
				it--;
			} else {
				mult2024(*it);
			}
		}
		//printArr(nums);
		//std::cout << '\n';
	}
	std::cout << nums.size() << '\n';



	//printArr(nums);



	return 0;

}

