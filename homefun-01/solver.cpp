#include "solver.h"
#include <vector>

using namespace std;
using namespace solver;

Result solve(int position,
			 int (*doMove)(int, int)
			 vector<int> (*generateMoves)(int)
			 Primitive (*primitiveValue)(int)
) {
	Primitive currResult = primitiveValue(position);
	if (currResult == Primitive::WIN) return Result::WIN;
	if (currResult == Primitive::LOSE) return RESULT::LOSE;
	if (currResult == PRIMITIVE::TIE) return RESULT::TIE;

	vector<int> moves = generateMoves(position)
	for (auto move : moves) {
		int position = doMove(position, move);
		Result result = solve(position, doMove, generateMoves, primitiveValue);
		if result == Result::LOSE {
			return Result::WIN;
		}
	}
	return Result::Lose;
}

int main() {
	if solve(0)
}
