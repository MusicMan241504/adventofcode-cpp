#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <map>

int main() {
	std::ifstream f{"day1.txt"};
	std::map<std::string,std::string> replaceMap {
		{"one", "one1one"},
		{"two", "two2two"},
		{"three", "three3three"},
		{"four", "four4four"},
		{"five", "five5five"},
		{"six", "six6six"},
		{"seven", "seven7seven"},
		{"eight", "eight8eight"},
		{"nine", "nine9nine"}};
	long total {0};
	while (f) {
		std::string s;
		std::getline(f,s);
		
		for (const auto& replaceStr : replaceMap) {
			s = std::regex_replace(s,std::regex(replaceStr.first),replaceStr.second);
		}
		std::cout << s << '\n';
		
		auto i1 {s.find_first_of("0123456789")};
		auto i2 {s.find_last_of("0123456789")};
		if (i1 != std::string::npos) {
			total += (s[i1]-'0')*10 + (s[i2]-'0');
		}
		std::cout << total << '\n';
	}
	std::cout << total << '\n';
	return 0;
}
