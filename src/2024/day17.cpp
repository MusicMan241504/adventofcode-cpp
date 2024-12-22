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

int main() {

	size_t a{37293246};
	//size_t a{1461985568};
	//size_t a{47906343213345};
	//size_t a{5988759999866};
	//size_t a{47910079998940};
	//size_t a{47910079998866};
	size_t b{0};
	size_t c{0};

	std::vector<size_t> instructions{2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0};

	size_t instPointer{0};

	while (instPointer < instructions.size()) {
		size_t instruction{instructions[instPointer]};
		size_t operand{instructions[instPointer+1]};
		//std::cout << a << ' ' << b << ' ' << c << '\n';
		
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
					std::cout << (combo(operand,a,b,c) & 7) << ',';
					instPointer+=2;
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
	std::cout << '\n';

	return 0;
}
