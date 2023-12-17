#include <fstream>
#include <iostream>

int getNum(std::string s, std::string col) {
	size_t numIndex {s.find(col)};
	if (numIndex != std::string::npos) {
		// get index of space before
		size_t spaceIndex {s.rfind(" ",numIndex-2)};
		int num {std::stoi(s.substr(spaceIndex+1,numIndex-spaceIndex-2))};
		return num;
	} else {
		return 0;
	}
}


int main() {
	constexpr int red {12};
	constexpr int green {13};
	constexpr int blue {14};
	std::ifstream f{"day2.txt"};
	
	int total {0};
	int id {1};
	while(f){
		std::string s;
		std::getline(f,s);
		if (s!= ""){
			// remove first part
			s = s.substr(s.find(":")+2);
			//std::cout << s << '\n';

			// split string on semicolons
			size_t preIndex {0};
			size_t index {0};
			bool isPos {true};
			while (isPos && index != std::string::npos) {

					index = s.find(";",preIndex);
					std::string subStr{s.substr(preIndex,index-preIndex)};
					preIndex = index+2;
					//std::cout << preIndex << index << '\n';

					if (getNum(subStr,"red") >red) {
						isPos = false;
					}
					if (getNum(subStr,"green") > green) {
						isPos = false;
					}
					if (getNum(subStr,"blue") > blue) {
						isPos = false;
					}

			}
			if (isPos) {
			//	std::cout << id << ' ';
				total+=id;
			}
			++id;
		}
	}
	std::cout << total << '\n';
	return 0;
}
	
