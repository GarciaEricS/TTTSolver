

namespace solver {
	enum class Result {WIN, TIE, LOSE, DRAW};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};
	Result solve(int position,
             int (*doMove)(int, int)
             vector<int> (*generateMoves)(int)
             Primitive (*primitiveValue)(int)
			);

	int doMove(int position, int move);
	vector<int> generateMoves(int);
	Primitive primitiveValue(int);
}

