#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main() {
	std::ifstream f{"day23.txt"};

	std::vector<std::vector<bool>> adjacencyMatrix(26*26, std::vector<bool>(26*26,0));
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		size_t num1{(size_t)(line[0]-'a')*26+(line[1]-'a')};
		size_t num2{(size_t)(line[3]-'a')*26+(line[4]-'a')};
		adjacencyMatrix[num1][num2] = 1;
		adjacencyMatrix[num2][num1] = 1;
	}

	int count{0};
	for (size_t pc1{0}; pc1 < 26*26; pc1++) {
		for (size_t pc2{pc1+1}; pc2 < 26*26; pc2++) {
			for (size_t pc3{pc2+1}; pc3 < 26*26; pc3++) {
				if (adjacencyMatrix[pc1][pc2] &&
				adjacencyMatrix[pc1][pc3] &&
				adjacencyMatrix[pc2][pc3]) {
					if (pc1/26 == 't'-'a' ||
					pc2/26 == 't'-'a' ||
					pc3/26 == 't'-'a') {
						count++;
						//std::cout << pc1 << ',' << pc2 << ',' << pc3 << '\n';
					}
				}
			}
		}
	}
	std::cout << count << '\n';


	return 0;
}

