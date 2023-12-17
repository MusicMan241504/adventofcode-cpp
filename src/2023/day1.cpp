#include <fstream>
#include <iostream>
#include <string>
int main() {
	std::ifstream f{"day1.txt"};
	long total {0};
	while (f) {
		std::string s;
		std::getline(f,s);
		auto i1 {s.find_first_of("0123456789")};
		auto i2 {s.find_last_of("0123456789")};
		if (i1 != std::string::npos) {
			total += (s[i1]-'0')*10 + (s[i2]-'0');
		}
	}
	std::cout << total << '\n';
	return 0;
}
