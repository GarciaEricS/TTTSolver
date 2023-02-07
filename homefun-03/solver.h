#include <vector>
#include <unordered_map>
#include <utility>

namespace Solver {
	enum class Result {WIN, TIE, LOSE, DRAW};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};
	class Position {
		public:
			virtual Position *doMove(int move) = 0;
			virtual std::vector<int> *generateMoves() = 0;
			virtual Primitive primitiveValue() = 0;
			virtual int hash() = 0;
			virtual ~Position() = default;
	};
}

