#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>




template <typename T>
void printArr(T& arr) {
	for (const auto& e : arr) {
		std::cout << e << '\n';
	}
	std::cout << '\n';
}

long long int isPossible(std::string pattern, std::vector<std::string>& towels, std::unordered_map<std::string, long long int>& memo) {
	//std::cout << pattern << '\n';

	if (memo.contains(pattern)) {
		return memo[pattern];
	}

	if (pattern == "") {
		//std::cout << "FOUND" << '\n';
		return 1;
	}
	if (!memo.contains(pattern)) {
		memo[pattern] = 0;
	}
	for (auto towel : towels) {
		if (pattern.starts_with(towel)) {
			memo[pattern] += isPossible(pattern.substr(towel.size(),pattern.size()-towel.size()), towels, memo);
		}
	}
	return memo[pattern];
}



int main() {
	std::ifstream f{"day19.txt"};

	std::vector<std::string> towels;


	std::string line;

	// get available towels
	std::getline(f,line);
	size_t prePos{0};
	size_t afterPos{line.find(',')};
	while (afterPos != line.npos) {
		towels.push_back(line.substr(prePos, afterPos-prePos));
		prePos = afterPos+2;
		afterPos = line.find(',',prePos);
	}
	towels.push_back(line.substr(prePos, line.size()-prePos));

	//printArr(towels);


	// blank line
	std::getline(f,line);

	long long int count{0};

	// each pattern
	std::unordered_map<std::string, long long int> memo;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}

		count += isPossible(line, towels, memo);
	}
	std::cout << count << '\n';

	return 0;
}
