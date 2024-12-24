#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
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
	std::set<int> maxPCset;


	for (size_t i{0}; i < 26*26; i++) {
		int tmpCount{1};

		std::set<int> PCset;
		PCset.insert(i);


		// for every node
		for (size_t j{0}; j < 26*26; j++) {
			bool isConnected {1};
			// if connected to every node in PCset
			for (auto node : PCset) {
				if (!adjacencyMatrix[node][j]) {
					isConnected = 0;
					break;
				}
			}
			if (isConnected) {
				PCset.insert(j);
				tmpCount++;
			}
		}
		if (tmpCount > count) {
			count = tmpCount;
			maxPCset = PCset;
		}
	}

	// get password
	std::string password;
	for (auto pc : maxPCset) {
		password += pc/26+'a';
		password += pc%26 + 'a';
		password += ',';
	}

	std::cout << password << '\n';

	//std::cout << count << '\n';


	return 0;
}

