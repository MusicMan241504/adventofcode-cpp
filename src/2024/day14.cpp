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
	for (size_t i{0}; i < 100; i++) {
		for (auto robot : robots) {
			robot->move();
		}
	}


	// count quadrants
	
	int leftTop{0};
	int leftBottom{0};
	int rightTop{0};
	int rightBottom{0};
	for (auto robot : robots) {
		if (robot->p[0] < 50) { // left < 50
			if (robot->p[1] < 51) { // top < 51
				leftTop++;
			} else if (robot->p[1] > 51) { // bottom > 51
					leftBottom++;
			}
		} else if (robot->p[0] > 50) { // right > 50
			if (robot->p[1] < 51) { // top < 51
				rightTop++;
			} else if (robot->p[1] > 51) { // bottom > 51
				rightBottom++;
			}
		}
	}

	int total {leftTop*leftBottom*rightTop*rightBottom};

	//printCoords(robots);

	deleteList(robots);

	std::cout << total << '\n';

	return 0;

}

