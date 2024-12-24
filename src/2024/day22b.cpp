#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void mix(long long int& secretNumber, long long int num) {
	secretNumber = secretNumber ^ num;
}

void prune(long long int& secretNumber) {
	secretNumber = secretNumber%16777216;
}

long long int nextSecretNumber(long long int secretNumber) {
	mix(secretNumber, secretNumber*64);
	prune(secretNumber);
	mix(secretNumber, secretNumber/32);
	prune(secretNumber);
	mix(secretNumber, secretNumber*2048);
	prune(secretNumber);
	return secretNumber;
}


int main() {
	std::ifstream f{"day22.txt"};


	std::vector<std::vector<int>> allPrices;
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}

		std::vector<int> prices;

		long long int secretNumber{stoi(line)};
		int price{0};
		for (size_t i{0}; i < 2000; i++) {
			secretNumber = nextSecretNumber(secretNumber);
			price = secretNumber % 10;
			prices.push_back(price);
		}

		allPrices.push_back(prices);
	}

	long long int total{0};
	for (int c1{-3}; c1 < 10; c1++) {
		for (int c2{-3}; c2 < 10; c2++) {
			for (int c3{-3}; c3 < 10; c3++) {
				for (int c4{-3}; c4 < 10; c4++) {
					long long int tmpTotal{0};
					for (auto& prices : allPrices) {
						if (c1+c2+c3+c4 < 0) {
							break;
						}
						for (size_t i{4}; i < prices.size(); i++) {
							if (prices[i-3] - prices[i-4] == c1 &&
									prices[i-2] - prices[i-3] == c2 &&
									prices[i-1] - prices[i-2] == c3 &&
									prices[i] - prices[i-1] == c4) {
								tmpTotal += prices[i];
								break;
							}
						}
					}
					if (tmpTotal > total) {
						total = tmpTotal;
					}
				}
			}
		}
		std::cout << c1 << '\n';
	}
	std::cout << total << '\n';

	return 0;
}

