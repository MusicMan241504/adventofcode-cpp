#include <bits/stdc++.h>
using namespace std;

template <typename T>
void print(const T& v) {
	for (const auto& e : v) {
		cout << e << ' ';
	}
	cout << '\n';
}

template <typename T>
void printMap(const T& m, const int i) {
	for (const auto& e : m) {
		cout << e[i] << ' ';
	}
	cout << '\n';
}

template <typename T>
long long mapFunc(const T& maps, long long num) {
//	cout << num << '\n';
	for (const auto& m : maps) { // for each map in maps
		for (const auto& line : m) { // for each line in map
			if (num >= line[1] && num < line[1]+line[2]) { // if in range
				num = line[0]+(num-line[1]);
//				cout << num << "num" << '\n';
				break;
			}
		}
	}
//	cout << num << '\n';
	return num;
}

int main() {
	ifstream f{"day5.txt"};
	string s;
	getline(f,s);
	list<long long> seeds;
	auto p{s.find_first_of("0123456789")};
	while (p != 0) {
		seeds.push_back(stoll(s.substr(p,s.find_first_not_of("0123456789",p)-p)));
		p = s.find_first_not_of("0123456789",p)+1;
	}

	// create array(7) of lists(x) of arrays(3)
	
	vector<list<vector<long long>>> maps(7);
	int map_index{-1};
	// iterate through every line in file
	while (f) {
		getline(f,s);
		if (s != "") {
			if (s.find("map") != s.npos) { // if contains word map
				++ map_index;
			} else {
				auto space1{s.find(" ")};
				auto space2{s.find(" ",space1+1)};
				maps[map_index].push_back({
						stoll(s.substr(0,space1)),
						stoll(s.substr(space1+1,space2-space1-1)),
						stoll(s.substr(space2+1)),
						});
			}
		}
//		cout << map_index << '\n';
	}


//	print(seeds);
//	printMap(maps[1],0);
	
	for (auto& seed : seeds) {
		seed = mapFunc(maps,seed);
	}

	cout << *min_element(seeds.begin(),seeds.end()) << '\n';

//	print(seeds);



	return 0;
}

	
