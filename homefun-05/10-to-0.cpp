#include <vector>
#include "TTT.h"

namespace TTZ {
	Solver::Position *TTZPosition::doMove(int move) {
		auto new_position = new TTZPosition();
		new_position->currInt = currInt - move;
		return new_position;
	}

	std::vector<int> *TTZPosition::generateMoves() {
		auto moves = new std::vector<int>();
		if (currInt >= 1) {
			moves->push_back(1);
		}
		if (currInt >= 2) {
			moves->push_back(2);
		}
		return moves;
	}

	Solver::Primitive TTZPosition::primitiveValue() {
		if (currInt == 0) {
			return Solver::Primitive::LOSE;
		}
		return Solver::Primitive::NOT_PRIMITIVE;
	}

	int TTZPosition::hash(bool removeSymmetries) {
		return currInt;
	}
}
