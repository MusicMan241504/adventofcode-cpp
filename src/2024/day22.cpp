#include <fstream>
#include <iostream>
#include <list>
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

	
	long long int total{0};
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		
		long long int secretNumber{stoi(line)};
		for (size_t i{0}; i < 2000; i++) {
			secretNumber = nextSecretNumber(secretNumber);
		}
		total += secretNumber;
		//std::cout << secretNumber << '\n';
	}

	std::cout << total << '\n';


	return 0;
}

