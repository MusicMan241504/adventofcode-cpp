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
	std::ifstream f{"day2.txt"};
	
	int total {0};
	while(f){
		std::string s;
		std::getline(f,s);
		if (s!= ""){
			// set min values to 0
			int red {0};
			int green {0};
			int blue {0};
			// remove first part
			s = s.substr(s.find(":")+2);
			//std::cout << s << '\n';

			// split string on semicolons
			size_t preIndex {0};
			size_t index {0};
			while (index != std::string::npos) {

					index = s.find(";",preIndex);
					std::string subStr{s.substr(preIndex,index-preIndex)};
					preIndex = index+2;
					//std::cout << preIndex << index << '\n';
					

					red = std::max(getNum(subStr,"red"),red);
					green = std::max(getNum(subStr,"green"),green);
					blue = std::max(getNum(subStr,"blue"),blue);
			}
			total+=(red*blue*green);
		}
	}
	std::cout << total << '\n';
	return 0;
}
	
