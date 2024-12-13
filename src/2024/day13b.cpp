#include <fstream>
#include <iostream>
#include <string>



int main() {
	std::ifstream f{"day13.txt"};

	std::string line;
	long long int total{0};
	while (std::getline(f,line)) {
		long long int xA {std::stoll(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))};
		long long int yA {std::stoll(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))};

		std::getline(f,line);
		long long int xB {std::stoll(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))};
		long long int yB {std::stoll(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))};

		std::getline(f,line);
		long long int x0 {std::stoll(line.substr(line.find('X')+2, line.find(',')-line.find('X')-2))+10000000000000};
		long long int y0 {std::stoll(line.substr(line.find('Y')+2, line.size()-line.find('Y')-2))+10000000000000};

		std::getline(f,line);


		// calculate button presses and cost
		// by solving 2 simultaneous equations using matrices

		// calculate button A
		long long int a{0};
		long long int b{0};
		long long int det{xA*yB-xB*yA};

		if (det != 0) {
			if ((yB*x0-xB*y0)%det == 0 && (xA*y0-yA*x0)%det == 0) {
				a = (yB*x0-xB*y0)/det;
				b = (xA*y0-yA*x0)/det;
			}
		}
		long long int cost{3*a+b};
		//std::cout << cost << '\n';
		total += cost;



	}


	std::cout << total << '\n';


	return 0;

}

