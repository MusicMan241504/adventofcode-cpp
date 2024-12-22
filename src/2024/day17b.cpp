#include <iostream>
#include <vector>


void printArr(std::vector<size_t>& arr) {
	for (const auto& e : arr) {
		std::cout << e << ' ';
	}
	std::cout << '\n';
}

size_t combo(size_t operand, size_t a, size_t b, size_t c) {
	switch (operand) {
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return a;
		case 5:
			return b;
		case 6:
			return c;
	}
	return 0;
}

bool isArrEquals(std::vector<size_t>& a, std::vector<size_t>& b) {
	if (a.size() != b.size()) {
		return 0;
	}
	for (size_t i{0}; i < a.size(); i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

int main() {

	size_t b{0};
	size_t c{0};

	std::vector<size_t> instructions{2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0};

	size_t instPointer{0};

	// 52500000000000
	for (size_t startA{0}; ; startA++) {
		if (startA % 1000000 == 0) {
			std::cout << startA << '\n';
		}

		size_t a{startA};
		b = 0;
		c = 0;
		instPointer = 0;

		std::vector<size_t> output;

		while (instPointer < instructions.size()) {
			size_t instruction{instructions[instPointer]};
			size_t operand{instructions[instPointer+1]};

			switch (instruction) {
				case 0:
					a = a >> combo(operand,a,b,c);
					instPointer+=2;
					break;
				case 1:
					b = b ^ operand;
					instPointer+=2;
					break;
				case 2:
					b = combo(operand,a,b,c) & 7;
					instPointer+=2;
					break;
				case 3:
					if (a != 0) {
						instPointer = operand;
					} else {
						instPointer+=2;
					}
					break;
				case 4:
					b = b ^ c;
					instPointer+=2;
					break;
				case 5:
					output.push_back(combo(operand,a,b,c) & 7);
					std::cout << startA << ' ' << (combo(operand,a,b,c) & 7) << '\n';
					instPointer+=2;
					instPointer = 999;
					break;
				case 6:
					b = a >> combo(operand,a,b,c);
					instPointer+=2;
					break;
				case 7:
					c = a >> combo(operand,a,b,c);
					instPointer+=2;
					break;
			}
		}
		//printArr(output);



		if (isArrEquals(output, instructions)) {
			std::cout << startA << '\n';
			return 0;
		}
	}

	return 0;
}
