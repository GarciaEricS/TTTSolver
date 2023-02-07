#include <vector>
#include "10-to-0.h"

namespace TTZ {
	Solver::Primitive TTZPosition::primitiveValue() {
		if (currInt == 0) {
			return Solver::Primitive::LOSE; 
		}
		return Solver::Primitive::NOT_PRIMITIVE;
	}

	int TTZPosition::hash() {
		return currInt;
	}

	std::vector<int> *TTZPosition::generateMoves() {
		std::vector<int> *moves = new std::vector<int>();
		if (currInt >= 1) {
			moves->push_back(1);
		}
		if (currInt >= 2) {
			moves->push_back(2);
		}
		return moves;

	}

	Solver::Position *TTZPosition::doMove(int move) {
		TTZ::TTZPosition *new_position = new TTZ::TTZPosition();
		new_position->currInt = currInt - move;
		return new_position;
	}
}
