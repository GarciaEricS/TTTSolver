#include <iostream>
#include <vector>
#include "solver.h"

using namespace std;

vector<int>* solver::generateMoves(int position) {
	vector<int>* moves = new vector<int>();
	if (position <= 0) {
	}
	else if (position == 1 || position == 2) {
		moves->push_back(1);
	}
	else if (position == 3) {
		moves->push_back(1);
		moves->push_back(3);
	} else {
		moves->push_back(1);
		moves->push_back(3);
		moves->push_back(4);
	}
	return moves;
}

solver::Primitive solver::primitiveValue(int position) {
	if (position == 0) {
		return Primitive::LOSE;
	} else {
		return Primitive::NOT_PRIMITIVE;
	}
}

int solver::doMove(int position, int move) {
	return position - move;
}

