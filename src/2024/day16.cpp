#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


struct Node {
	size_t x{};
	size_t y{};
	int xDir{};
	int yDir{};
	int cost{};
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

template <typename T>
void deleteNodes(T& pq) {
	while (!pq.empty()) {
		auto e{pq.top()};
		pq.pop();
		delete e;
	}
}

int main() {
	std::ifstream f{"day16.txt"};


	std::vector<std::string> maze;
	std::string line;
	while (std::getline(f,line)) {
		if (line == "") {
			break;
		}
		maze.push_back(line);
	}

	//printArr(maze);

	int cost{0};


	// check if has been visited before by using
	// visited[y][x][xDir+1][yDir+1]
	std::vector<std::vector<std::vector<std::vector<bool>>>> visited
		(maze.size(), std::vector<std::vector<std::vector<bool>>>
		 (maze[0].size(), std::vector<std::vector<bool>>
		  (3, std::vector<bool>
		   (3,0)
		  )
		 )
		);
	//std::cout << sizeof(visited) << '\n';

	std::priority_queue<Node*,std::vector<Node*>, CompareNodes> pq;

	pq.push(new Node{1, maze.size()-2,1,0,0});

	while (!pq.empty()) {
		Node* n {pq.top()};
		pq.pop();

		//std::cout << n->x << ' ' << n->y << '\n';
		//std::cout << n->cost << '\n';

		// if done
		if (n->x == maze[0].size()-2 && n->y == 1) {
			cost = n->cost;
			delete n;
			break;
		}

		if (maze[n->y + n->yDir][n->x + n->xDir] != '#') {
			if (!visited[n->y + n->yDir][n->x + n->xDir][n->xDir+1][n->yDir+1]) {
				pq.push(new Node{n->x + n->xDir, n->y + n->yDir, n->xDir, n->yDir, n->cost+1});
			}
		}

		// Use rotation matrix to transform direction vector 90 deg clockwise
		// X = y
		// Y = -x
		if (!visited[n->y][n->x][n->yDir+1][-n->xDir+1]) {
			pq.push(new Node{n->x, n->y, n->yDir, -n->xDir, n->cost+1000});
		}
		// 90 deg anticlockwise
		// X = -y
		// Y = X
		if (!visited[n->y][n->x][-n->yDir+1][n->xDir+1]) {
			pq.push(new Node{n->x, n->y, -n->yDir, n->xDir, n->cost+1000});
		}

		visited[n->y][n->x][n->xDir+1][n->yDir+1] = 1;
		//maze[n->y][n->x] = 'O';
		//printArr(maze);

		delete n;
	}

	deleteNodes(pq);

	std::cout << cost << '\n';


	return 0;

}

