#include <fstream>
#include <iostream>
#include <vector>


void printArr(std::vector<bool>& charCheck) {
	for ( const auto& item : charCheck) {
		std::cout << item << ' ';
	}
	std::cout << '\n';
}




int main() {
	std::ifstream f{"day3.txt"};
	char ch;
	long int total {0};
	int num1 {0};
	int num2 {0};
	std::vector<bool> charCheck{0,0,0,0,0,0,0,0,0,0,0, 0};
	//			    0 1 2 3 4 5 6 7 8 9 10 11
	//			    m u l ( 9 9 9 , 9 9 9  )
	
	while (f >> ch) { // loop for each char
		if (ch == 'm') {
			charCheck[0] = 1;
		} else if (charCheck[0]) {
			charCheck[0] = 0;
			if (ch == 'u') {
				charCheck[1] = 1;
			}
		} else if (charCheck[1]) {
			charCheck[1] = 0;
			if (ch == 'l') {
				charCheck[2] = 1;
			}
		} else if (charCheck[2]) {
			charCheck[2] = 0;
			if (ch == '(') {
				charCheck[3] = 1;
			}
		} else if (charCheck[3]) {
			charCheck[3] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[4] = 1;
				num1 = ch-'0';
			}
		} else if (charCheck[4]) {
			charCheck[4] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[5] = 1;
				num1 = num1*10+ch-'0';
			} else if (ch == ',') {
				charCheck[7] = 1;
			}
		} else if (charCheck[5]) {
			charCheck[5] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[6] = 1;
				num1 = num1*10+ch-'0';
			} else if (ch == ',') {
				charCheck[7] = 1;
			}
		} else if (charCheck[6]) {
			charCheck[6] = 0;
			if (ch == ',') {
				charCheck[7] = 1;
			}
		} else if (charCheck[7]) {
			charCheck[7] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[8] = 1;
				num2 = ch-'0';
			}
		} else if (charCheck[8]) {
			charCheck[8] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[9] = 1;
				num2 = num2*10+ch-'0';
			} else if (ch == ')') {
				charCheck[11] = 1;
			}
		} else if (charCheck[9]) {
			charCheck[9] = 0;
			if (ch >= '0' && ch <= '9') {
				charCheck[10] = 1;
				num2 = num2*10+ch-'0';
			} else if (ch == ')') {
				charCheck[11] = 1;
			}
		} else if (charCheck[10]) {
			charCheck[10] = 0;
			if (ch == ')') {
				charCheck[11] = 1;
			} 
		}


		//printArr(charCheck);


		if (charCheck[11]) {
			// found mul command
			charCheck[11] = 0;
			total += num1*num2;
			//std::cout << num1 << ' ' << num2 << '\n';
		}
			




	}

	std::cout << total << '\n';

	return 0;
}

