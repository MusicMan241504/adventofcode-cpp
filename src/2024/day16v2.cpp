#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


struct Node {
	size_t x{};
	size_t y{};
	size_t dir{};
	bool isPath{};
	int cost{999999999};
};

struct CompareNodes {
	bool operator()(const Node* n1, const Node* n2) {
		return n1->cost > n2->cost;
	}
};

template <typename T>
void printArr(T& arr) {
	for (const auto& e : arr) {
		std::cout << e << '\n';
	}
	std::cout << '\n';
}

void deleteNodes(std::vector<std::vector<std::vector<Node*>>>& arr) {
	for (const auto& row : arr) {
		for (const auto& square : row) {
			for (const auto& e : square) {
				delete e;
			}
		}
	}
}


int main() {
	std::ifstream f{"day16.txt"};

// 3D array to store all squares in maze
// Each square is stored 4 times, once for each possible direction
// 0 = x+1
// 1 = y+1
// 2 = x-1
// 3 = y-1
// maze[y][x][dir]
	std::vector<std::vector<std::vector<Node*>>> maze;

	std::vector<std::vector<int>> dirs{
		{1,0},
		{0,1},
		{-1,0},
		{0,-1}};

	std::string line;
	for (size_t y{0}; std::getline(f,line); y++) {
		if (line == "") {
			break;
		}
		std::vector<std::vector<Node*>> row;
		for (size_t x{0}; x < line.size(); x++) {
			std::vector<Node*> square(4);
			for (size_t dir{0}; dir < 4; dir++) {
				bool isPath;
				if (line[x] != '#') {
					isPath = 1;
				} else {
					isPath = 0;
				}
				square[dir] = new Node{x,y,dir,isPath};
			}
			row.push_back(square);
		}
		maze.push_back(row);
	}

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
	pq.push(maze[maze.size()-2][1][0]);
	maze[maze.size()-2][1][0]->cost = 0;

	while (!pq.empty()) {
		// get minimum cost node
		Node* n {pq.top()};
		pq.pop();



		// go through possible moves
		
		// forward
		size_t newY{n->y + dirs[n->dir][1]};
		size_t newX{n->x + dirs[n->dir][0]};
		//std::cout << newX << ' ' << newY << '\n';
		if (maze[newY][newX][n->dir]->isPath) { // if is path
			int newCost{n->cost+1};
			if (newCost < maze[newY][newX][n->dir]->cost) {
				maze[newY][newX][n->dir]->cost = newCost;
				pq.push(maze[newY][newX][n->dir]);
			}
		}

		// rotate
		int newCost{n->cost+1000};
		// right
		if (newCost < maze[n->y][n->x][(n->dir+1)%4]->cost) {
			maze[n->y][n->x][(n->dir+1)%4]->cost = newCost;
			pq.push(maze[n->y][n->x][(n->dir+1)%4]);
		}
		// left
		if (newCost < maze[n->y][n->x][(n->dir+3)%4]->cost) {
			maze[n->y][n->x][(n->dir+3)%4]->cost = newCost;
			pq.push(maze[n->y][n->x][(n->dir+3)%4]);
		}

	}


	// get min answer
	int ans{999999999};
	for (const auto& n : maze[1][maze[0].size()-2]) {
		if (n->cost < ans) {
			ans = n->cost;
		}
	}
	std::cout << ans << '\n';


	// clear memory
	deleteNodes(maze);



	return 0;
}

