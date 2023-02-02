#include <vector>
#include <array>
#include <unordered_map>

namespace TTTsolver {
	enum class Tile {X, O, B};
	enum class Result {WIN, TIE, LOSE, DRAW};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};
	struct Position {
		std::array<Tile, 9> tiles;
		Tile whoseMove;
	};

	Position *doMove(Position *position, int move);
	std::vector<int>* generateMoves(Position *position);
	Primitive primitiveValue(Position *position);
	Result solve(Position *position, std::unordered_map<int, Result> *memo);

}

