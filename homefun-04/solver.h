#include <vector>
#include <unordered_map>
#include <utility>

namespace Solver {
	enum class Result {WIN, TIE, LOSE, DRAW, NIL};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};
	enum class Tile {X, O, B};
	class Position {
		public:
			virtual Position *doMove(int move) = 0;
			virtual std::vector<std::pair<int, Tile>> *generateMoves() = 0;
			virtual Primitive primitiveValue() = 0;
			virtual int hash(bool removeSymmetries) = 0;
			virtual ~Position() {};
	};
}

