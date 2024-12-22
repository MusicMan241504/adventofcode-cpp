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

void resetDistances(std::vector<std::vector<Node*>>& arr) {
	for (auto& row : arr) {
		for (auto& e : row) {
			e->d = 999999999;
		}
	}
}

int findShortestPath(std::vector<std::vector<Node*>>& grid, size_t startX, size_t startY, size_t endX, size_t endY) {
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
	pq.push(grid[startY][startX]);
	grid[startY][startX]->d = 0;

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

	return grid[endY][endX]->d;
}

int main() {
	std::ifstream f{"day20.txt"};

	std::vector<std::vector<Node*>> grid;


	size_t startX{0};
	size_t startY{0};
	size_t endX{0};
	size_t endY{0};

	std::string line;
	for(size_t y{0}; std::getline(f,line); y++) {
		if (line == "") {
			break;
		}
		std::vector<Node*> row;
		for (size_t x{0}; x < line.size(); x++){
			if (line[x] == 'S') {
				startX = x;
				startY = y;
			} else if (line[x] == 'E') {
				endX = x;
				endY = y;
			}
			row.push_back(new Node{x,y,!(line[x]=='#')});
		}
		grid.push_back(row);
	}

	int normalDistance{findShortestPath(grid, startX, startY, endX, endY)};
	resetDistances(grid);

	int total{0};
	for (size_t y{0}; y < grid.size(); y++) {
		for (size_t x{0}; x < grid[0].size(); x++) {
			if (!grid[y][x]->isPath) {
				grid[y][x]->isPath = 1;
				int newDistance{findShortestPath(grid, startX, startY, endX, endY)};
				//std::cout << normalDistance - newDistance << '\n';
				if (normalDistance - newDistance >= 100) {
					total++;
				}
				grid[y][x]->isPath = 0;
				resetDistances(grid);
			}
		}
	}
	
	std::cout << total << '\n';

	// clear memory
	deleteNodes(grid);

	return 0;
}

