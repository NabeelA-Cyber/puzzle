#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#define XBOARD 3
#define YBOARD 3
using namespace std;


struct State {
	vector<vector<int> > p;
	int r, c;
};
typedef vector<State> Path;

queue<Path> frontier;
Path temp;
State currentState;
//unordered_map<State, Path> graph;
Path goal;
Path Explored;
Path start;

void build_graph() {
	goal.push_back( { { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} }, 2, 2});
	start.push_back({ { {4, 1, 3}, {0, 8, 5}, {2, 7, 6} }, 1, 0});
	
}

bool isGoal(State s) {
	for (unsigned int g=0; g<goal.size(); g++) {
		if (goal[0].r != s.r || goal[0].c != s.c) return false;
		for (unsigned int i=0; i<XBOARD; i++)
			for (unsigned int j=0; j<YBOARD; j++)
				if (goal[0].p[i][j] != s.p[i][j])
					return false;
	}
	return true;
}

Path getNeighbors(State s) {
	vector<int> moves = {-1, 1}; Path actions; int newMove;
	for (unsigned int a=0; a<moves.size(); a++) {
		newMove = s.r + moves[a];
		if (newMove >= 0 && newMove < XBOARD) {
			swap(s.p[s.r][s.c], s.p[newMove][s.c]);
			s.r = newMove;
			actions.push_back(s);
			s.r = s.r - moves[a];
			swap(s.p[newMove][s.c], s.p[s.r][s.c]);
		}
	}
	for (unsigned int a=0; a<moves.size(); a++) {
		newMove = s.c + moves[a];
		if (newMove < YBOARD && newMove >= 0) {
			swap(s.p[s.r][s.c], s.p[s.r][newMove]);
			s.c = newMove;
			actions.push_back(s);
			s.c = s.c - moves[a];
			swap(s.p[s.r][newMove], s.p[s.r][s.c]);
		}
	}
	return actions;
}

bool isExplored(State s) {
	bool match = false;
	for (int i=0; i<Explored.size(); i++) {
		if (s.r == Explored[i].r && s.c == Explored[i].c) {
			match = true;
			for (int i=0; i<XBOARD && match; i++)
				for (int j=0; j<YBOARD && match; j++)
					if (s.p[i][j] != Explored[i].p[i][j])
						match = false;
					if (match) return true;
		}
	}
	return false;
}


Path search() {
	Path neighbors;
	frontier.push(start);
	while (true) {
		if (frontier.empty()) return {};   	// frontier empty return null
		temp = frontier.front();			// retrieving a path from frontier
		frontier.pop();
		currentState = temp[temp.size()-1];	// retrieving last element in temp
		if (isGoal(currentState)) return temp; // check if currentState is goal
		if (isExplored(currentState)) continue;
		Explored.push_back(currentState);
		neighbors = getNeighbors(currentState); // retrieve neighbors
		for (unsigned int i=0; i<neighbors.size(); i++) { // insert neighbors in frontier.
			if (isExplored(neighbors[i])) continue;
			temp.push_back(neighbors[i]);
			frontier.push(temp);
			temp.pop_back();
		}
	}
}

void display(Path & path) {
// left to you to implement
// use two for loops to display the matrix:
 
// path[i].p
	for(int i=0;i<path.size();i++){
		for( int r=0; r<XBOARD;r++){
			for( int c=0; c<YBOARD;c++)
				cout << path[i].p[r][c] << " ";
			cout<<endl;
		}
		cout << endl;
	}
}

int main() {
	build_graph();
	temp = search();
	if (temp.size() != 0) { cout << "The goal is found: \n"; display(temp); }
	else cout << "Path not found\n";
	return 0;
}
