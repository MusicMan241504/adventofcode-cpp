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

int findShortestPath(std::vector<std::vector<Node*>>& grid, size_t startX, size_t startY, size_t endX, size_t endY, std::vector<std::vector<int>>& moves) {
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
	pq.push(grid[startY][startX]);
	grid[startY][startX]->d = 0;

	while (!pq.empty()) {
		// get minimum cost node
		Node* n {pq.top()};
		pq.pop();

		// go through possible moves
		for (auto move : moves) {
			if (n->x+1 + move[0] > 0 && n->y+1 + move[1] > 0 && n->x + move[0] < grid[0].size() && n->y + move[1] < grid.size()) {
				size_t newX{n->x + move[0]};
				size_t newY{n->y + move[1]};
				if (grid[newY][newX]->isPath) { // if is path
					int newD{n->d+1};
					if (newD < grid[newY][newX]->d) {
						grid[newY][newX]->d = newD;
						pq.push(grid[newY][newX]);
					}
				}
			}
		}
	}

	return grid[endY][endX]->d;
}

void extractDistances(std::vector<std::vector<int>>& out, std::vector<std::vector<Node*>>& grid) {
	for (size_t y{0}; y < grid.size(); y++) {
		for (size_t x{0}; x < grid[0].size(); x++) {
			out[y][x] = grid[y][x]->d;
		}
	}
}

int main() {
	std::ifstream f{"day20.txt"};

	std::vector<std::vector<Node*>> grid;


	std::vector<std::vector<int>> moves{
		{1,0},
			{0,1},
			{-1,0},
			{0,-1}};



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

	// distance from start
	int normalDistance{findShortestPath(grid, startX, startY, endX, endY, moves)};
	//std::cout << normalDistance << '\n';
	std::vector<std::vector<int>> distanceFromStart(grid.size(), std::vector<int>(grid[0].size(), 999999999));
	extractDistances(distanceFromStart, grid);
	resetDistances(grid);

	// distance from end
	findShortestPath(grid, endX, endY, startX, startY, moves);
	std::vector<std::vector<int>> distanceFromEnd(grid.size(), std::vector<int>(grid[0].size(), 999999999));
	extractDistances(distanceFromEnd, grid);
	resetDistances(grid);

	int total{0};
	for (size_t y{0}; y < grid.size(); y++) {
		for (size_t x{0}; x < grid[0].size(); x++) {
			if (!grid[y][x]->isPath) {
				// grid[y][x] is start of cheat
				// cheats must start on wall and end on path

				// for each surrounding path to end
				for (auto move : moves) {
					if (x+1 + move[0] > 0 && y+1 + move[1] > 0 && x + move[0] < grid[0].size() && y + move[1] < grid.size()) {
						size_t x2{x + move[0]};
						size_t y2{y + move[1]};
						if (grid[y2][x2]->isPath) {
							int newDistance{999999999};
							// for each surrounging path to start
							for (auto move : moves) {
								if (x+1 + move[0] > 0 && y+1 + move[1] > 0 && x + move[0] < grid[0].size() && y + move[1] < grid.size()) {
									size_t x1{x + move[0]};
									size_t y1{y + move[1]};
									if (grid[y1][x1]->isPath) {
										int tmpD{distanceFromStart[y1][x1] + distanceFromEnd[y2][x2] + 2};
										if (tmpD < newDistance) {
											newDistance = tmpD;
										}
									}
								}
							}
							if (normalDistance - newDistance >= 100) {
								total++;
							}
						}
					}
				}
			}
		}
	}

	std::cout << total << '\n';

	// clear memory
	deleteNodes(grid);

	return 0;
}

