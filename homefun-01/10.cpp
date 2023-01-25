#include <iostream>
#include <vector>
#include "solver.h"

using namespace std;
using namespace solver;

vector<int>* generateMoves(int position) {
	vector<int>* moves = new vector<int>();
	if (position <= 0) {
	}
	else if (position == 1) {
		moves->push_back(1);
	}
	else {
		moves->push_back(1);
		moves->push_back(2);
	}
	return moves;
}

Primitive primtiveValue(int position) {
	if (position == 0) {
		return Primitive::LOSE;
	} else {
		return Primitive::NOT_PRIMITIVE;
	}
}

int doMove(int position, int move) {
	return position - move;
}

void printVec(vector<int>* vectptr) {
	vector<int> vect = *vectptr;
	for (auto x : vect) {
		cout << x;
		cout << '\n';
	}
	cout << '\n';
}
