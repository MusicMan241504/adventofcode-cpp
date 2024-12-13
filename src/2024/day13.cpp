#include <fstream>
#include <iostream>
#include <string>



int main() {
	std::ifstream f{"day13.txt"};

	std::string line;
	int total{0};
	while (std::getline(f,line)) {
		int xA {std::stoi(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))};
		int yA {std::stoi(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))};

		std::getline(f,line);
		int xB {std::stoi(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))};
		int yB {std::stoi(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))};

		std::getline(f,line);
		int x0 {std::stoi(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))};
		int y0 {std::stoi(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))};

		std::getline(f,line);


		// calculate button presses and cost
		// by solving 2 simultaneous equations using matrices

		// calculate button A
		int a{0};
		int b{0};
		int det{xA*yB-xB*yA};

		if (det != 0) {
			if ((yB*x0-xB*y0)%det == 0 && (xA*y0-yA*x0)%det == 0) {
				a = (yB*x0-xB*y0)/det;
				b = (xA*y0-yA*x0)/det;
			}
		}
		int cost{3*a+b};
		//std::cout << cost << '\n';
		total += cost;



	}


	std::cout << total << '\n';


	return 0;

}

