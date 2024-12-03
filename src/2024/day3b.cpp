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
	bool doMul {1};
	std::vector<bool> doCharCheck{0,0,0,0};
	//			      0 1 2 3
	//			      d o ( )
	std::vector<bool> dontCharCheck{0,0,0,0,0,0,0};
	//				0 1 2 3 4 5 6
	//				d o n ' t ( )
	std::vector<bool> charCheck{0,0,0,0,0,0,0,0,0,0,0, 0};
	//			    0 1 2 3 4 5 6 7 8 9 10 11
	//			    m u l ( 9 9 9 , 9 9 9  )

	while (f >> ch) { // loop for each char
		if (doMul) {
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

		// check for do()
		if (ch == 'd') {
			doCharCheck[0] = 1;
		} else if (doCharCheck[0]) {
			doCharCheck[0] = 0;
			if (ch == 'o') {
				doCharCheck[1] = 1;
			}
		} else if (doCharCheck[1]) {
			doCharCheck[1] = 0;
			if (ch == '(') {
				doCharCheck[2] = 1;
			}
		} else if (doCharCheck[2]) {
			doCharCheck[2] = 0;
			if (ch == ')') {
				doCharCheck[3] = 1;
				doMul = 1;
			}
		}

		// check for don't()
		if (ch == 'd') {
			dontCharCheck[0] = 1;
		} else if (dontCharCheck[0]) {
			dontCharCheck[0] = 0;
			if (ch == 'o') {
				dontCharCheck[1] = 1;
			}
		} else if (dontCharCheck[1]) {
			dontCharCheck[1] = 0;
			if (ch == 'n') {
				dontCharCheck[2] = 1;
			}
		} else if (dontCharCheck[2]) {
			dontCharCheck[2] = 0;
			if (ch == '\'') {
				dontCharCheck[3] = 1;
			}
		} else if (dontCharCheck[3]) {
			dontCharCheck[3] = 0;
			if (ch == 't') {
				dontCharCheck[4] = 1;
			}
		} else if (dontCharCheck[4]) {
			dontCharCheck[4] = 0;
			if (ch == '(') {
				dontCharCheck[5] = 1;
			}
		} else if (dontCharCheck[5]) {
			dontCharCheck[5] = 0;
			if (ch == ')') {
				dontCharCheck[6] = 1;
				doMul = 0;
			}
		} 
	}
	std::cout << total << '\n';
	return 0;
}
