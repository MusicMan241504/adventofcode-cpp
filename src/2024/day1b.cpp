#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
int main() {
	std::ifstream f{"day1.txt"};
	std::vector<int> left;
	std::vector<int> right;
	int intL;
	int intR;
	while (f >> intL and f >> intR) {
		left.push_back(intL);
		right.push_back(intR);
	}

	long total {0};
	for (size_t i{0}; i< left.size(); i++) {
		long int counter {std::count(right.begin(),right.end(), left[i])};
		total += left[i]*counter;
	}

	std::cout << total << '\n';

	return 0;
}

