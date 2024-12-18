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
			} else if (p[0] > 100) {
				p[0] -= 101; // 101
			}
			if (p[1] < 0) {
				p[1] += 103; // 103
			} else if (p[1] > 102) {
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

bool isChristmasTree(std::list<Robot*>& lst) {
	// find row containing > 50 robots
	std::vector<int> count(103); // last 20 rows
	for (const auto& e : lst) {
		count[e->p[1]]++;
	}

	for (const auto& e : count) {
		if (e >= 32) {
			return 1;
		}
	}
	return 0;
}

void printRobots(std::list<Robot*> lst) {
	std::vector<std::vector<bool>> robots(103,std::vector<bool>(101,0));
	for (const auto& e : lst) {
		robots[e->p[1]][e->p[0]] = 1;
	}

	for (const auto& row : robots) {
		for (auto e : row) {
			if (e) {
				std::cout << '#';
			} else {
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
	std::cout << '\n';
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
	size_t i{1};
	for (; 1; i++) {
		for (auto& robot : robots) {
			robot->move();
		}
		if (i % 100000 == 0) {
			std::cout << i << '\n';
		}
		
		if (isChristmasTree(robots)) {
			printRobots(robots);
			std::string s;
			std::cout << i << '\n';
			std::cin >> s;
			std::cout << "\n\n\n\n\n";
		}


	}
	//std::cout << i << '\n';
	//printRobots(robots);



	//printCoords(robots);

	deleteList(robots);


	return 0;

}

