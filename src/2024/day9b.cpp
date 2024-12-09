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

	int id2{999999999};
	for (int i{(int)disk.size()-1}; i > 0; i--) {
		if (disk[i] == -1 || disk[i]>id2) {
			continue;
		}
		int id{disk[i]};
		//std::cout << id << '\n';
		int endIndex{(int)i};
		for (; i >= 0 && disk[i] == id; i--) ;
		int len {endIndex-i};
		//std::cout << disk[endIndex] << ' ' << disk[i] << '\n';
		//std::cout << len << '\n';
		
		// find space starting from beginning
		int emptyCount {0};
		for (int j{0}; j < i+1; j++) {
			if (disk[j] == -1) {
				emptyCount++;
			} else {
				emptyCount = 0;
			}
			if (emptyCount == len) {
				for (int k{0}; k < len; k++) {
					disk[j+k-len+1] = disk[i+k+1];
					disk[i+k+1] = -1;
				}
				break;
			}
		}
		i++;
		id2 = id-1;
		//printArr(disk);


	}


	long long int total {0};
	for (size_t i{0}; i< disk.size(); i++) {
		if (disk[i] != -1) {
			total += (i*disk[i]);
		}
	}

	//printArr(disk);
	std::cout << total << '\n';

	return 0;
}

