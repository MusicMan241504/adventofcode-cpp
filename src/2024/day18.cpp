#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


struct Node {
	size_t x{};
	size_t y{};
	bool isPath{};
	int d{999999999};
};

struct CompareNodes {
	bool operator()(const Node* n1, const Node* n2) {
		return n1->d > n2->d;
	}
};

template <typename T>
void printArr(T& arr) {
	for (const auto& e : arr) {
		std::cout << e << '\n';
	}
	std::cout << '\n';
}


void deleteNodes(std::vector<std::vector<Node*>>& arr) {
	for (const auto& row : arr) {
		for (const auto& e : row) {
			delete e;
		}
	}
}

int main() {
	std::ifstream f{"day18.txt"};

	std::vector<std::vector<Node*>> grid(71, std::vector<Node*>(71));


	// fill grid with nodes of all paths
	for (size_t y{0}; y < grid.size(); y++) {
		for (size_t x{0}; x < grid[0].size(); x++) {
			grid[y][x] = new Node{x,y,1};
		}
	}

	std::string line;
	for (size_t i{0}; i < 1024 && std::getline(f,line); i++) {
		if (line == "") {
			break;
		}
		size_t x{stoul(line.substr(0, line.find(',')))};
		size_t y{stoul(line.substr(line.find(',')+1, line.size()-line.find(',')))};

		grid[y][x]->isPath = 0;
	}

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
	pq.push(grid[0][0]);
	grid[0][0]->d = 0;

	while (!pq.empty()) {
		// get minimum cost node
		Node* n {pq.top()};
		pq.pop();



		// go through possible moves

		// x+1
		if (n->x+1 < grid[0].size()) {
			if (grid[n->y][n->x+1]->isPath) { // if is path
				int newD{n->d+1};
				if (newD < grid[n->y][n->x+1]->d) {
					grid[n->y][n->x+1]->d = newD;
					pq.push(grid[n->y][n->x+1]);
				}
			}
		}
		// y+1
		if (n->y+1 < grid.size()) {
			if (grid[n->y+1][n->x]->isPath) { // if is path
				int newD{n->d+1};
				if (newD < grid[n->y+1][n->x]->d) {
					grid[n->y+1][n->x]->d = newD;
					pq.push(grid[n->y+1][n->x]);
				}
			}
		}
		// x-1
		if (n->x > 0) {
			if (grid[n->y][n->x-1]->isPath) { // if is path
				int newD{n->d+1};
				if (newD < grid[n->y][n->x-1]->d) {
					grid[n->y][n->x-1]->d = newD;
					pq.push(grid[n->y][n->x-1]);
				}
			}
		}
		// y-1
		if (n->y > 0){
			if (grid[n->y-1][n->x]->isPath) { // if is path
				int newD{n->d+1};
				if (newD < grid[n->y-1][n->x]->d) {
					grid[n->y-1][n->x]->d = newD;
					pq.push(grid[n->y-1][n->x]);
				}
			}
		}
	}



	// get path distance
	std::cout << grid[grid.size()-1][grid[0].size()-1]->d << '\n';



	// clear memory
	deleteNodes(grid);

	return 0;
}

