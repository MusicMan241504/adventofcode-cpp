#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>


class Robot{
	public:
		std::vector<int> p{};
		std::vector<int> v{};

		void move() {
			p[0] += v[0];
			p[1] += v[1];
			if (p[0] < 0) {
				p[0] += 101; // 101
			}
			if (p[0] > 100) {
				p[0] -= 101; // 101
			}
			if (p[1] < 0) {
				p[1] += 103; // 103
			}
			if (p[1] > 102) {
				p[1] -= 103; // 103
			}
		}
};

void deleteList(std::list<Robot*> lst) {
	for (auto e : lst) {
		delete e;
	}
}

void printCoords(std::list<Robot*> lst) {
	for (auto e : lst) {
		std::cout << e->p[0] << ' ' << e->p[1] << '\n';
	}
}

bool isChristmasTree(std::list<Robot*> lst) {
	// (40,40) - (60,60) all squares contain robot
	for (int x{50}; x<52; x++) {
		for (int y{60}; y<62; y++) {
			// find robot
			bool found{0};
			for (auto e : lst) {
				if (e->p[0] == x && e-> p[1] == y) {
					found = 1;
					break;
				}
			}
			if (!found) {
				return 0;
			}
		}
	}
	return 1;
}

int main() {
	std::ifstream f{"day14.txt"};


	std::list<Robot*> robots;
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		std::vector<int> p(2);

		
		p[0] = std::stoi(line.substr(2, line.find(',')-2));
		p[1] = std::stoi(line.substr(line.find(',')+1, line.find('v')-line.find(',')-1));

		std::vector<int> v(2);
		v[0] = std::stoi(line.substr(line.find('v')+2, line.find(',', line.find('v'))-line.find('v')));
		v[1] = std::stoi(line.substr(line.find(',', line.find('v'))+1, line.size()-line.find(',', line.find('v'))));

		robots.push_back(new Robot{p,v});

	}
	size_t i{0};
	for (; !isChristmasTree(robots); i++) {
		for (auto robot : robots) {
			robot->move();
		}
		//std::cout << i << '\n';
	}
	std::cout << i << '\n';



	//printCoords(robots);

	deleteList(robots);


	return 0;

}

