#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void printArr(std::vector<int>& arr) {
	for (const auto e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}

int main() {
	std::ifstream f{"day9.txt"};
	std::string input;

	std::getline(f,input);

	std::vector<int> disk;

	int id{0};
	for (size_t i{0}; i < input.size(); i++) {
		int val {-1};
		if (i%2==0){
			val = id;
			id++;
		}
		for (int j{0}; j < input[i] - '0'; j++) {
			disk.push_back(val);
		}
	}

	//printArr(disk);


	size_t preEmpty {0};
	for (size_t i{disk.size()-1}; preEmpty < i; i--) {
		if (disk[i] != -1) {
			for (; preEmpty < i; preEmpty++) {
				if (disk[preEmpty] == -1) {
					disk[preEmpty] = disk[i];
					disk[i] = -1;
					break;
				}
			}
		}
	}


	long int total {0};
	for (size_t i{0}; i< disk.size(); i++) {
		if (disk[i] != -1) {
			total += (i*disk[i]);
		}
	}

	//printArr(disk);
	std::cout << total << '\n';

	return 0;
}

