#include <vector>

namespace solver {
	enum class Result {WIN, TIE, LOSE, DRAW};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};

	int doMove(int position, int move);
	std::vector<int>* generateMoves(int position);
	Primitive primitiveValue(int position);
}

