#include <iostream>
#include <vector>


void printArr(std::vector<size_t>& arr) {
	for (const auto& e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}

unsigned long long int getNext3bits(unsigned long long int currentBits, std::vector<size_t>& instructions, size_t i) {
	size_t a{0};
	size_t b{0};
	size_t c{0};
	unsigned long long int ans{0};
	for (size_t startA{(currentBits << 3)}; startA < (currentBits << 3)+8 ; startA++) {
		a = startA;


		b = a&7;
		b = b^6;
		c = a>>b;
		b = b^c;
		b = b^7;
		a = a>>3;
		if ((b&7) == instructions[i]) {
			//std::cout << "Possible " << instructions[i] << ": " << startA << '\n';
			if (i != 0) {
				unsigned long long int tmp {getNext3bits(startA, instructions, i-1)};
				if (tmp > 0) {
					ans = tmp;
				}
			} else {
				//std::cout << "ANSWER FOUND: " << startA << '\n';
				return startA;
			}
		}
	}
	return ans;
}

int main() {


	std::vector<size_t> instructions{2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0};


	// it is possible to separate the problem as each number in output depends on only 3 bits so find the correct 3 bits for each number and combine them together
	
	unsigned long long int ans{0};
	ans = getNext3bits(0, instructions, instructions.size()-1);
	std::cout << ans << '\n';

	return 0;
}
