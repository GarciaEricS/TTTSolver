#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Tile {X, O, B};
	class TTTPosition : public Solver::Position {
		public:
			Position *doMove(int move);
			std::vector<int> *generateMoves();
			Solver::Primitive primitiveValue();
			int hash(bool removeSymmetries);
			std::array<Tile, 9> tiles;
			Tile whoseMove;

		protected:
			bool line_at(int x, int y, int z);
	};
}

namespace TTZ {
	class TTZPosition : public Solver::Position {
		public:
			Position *doMove(int move);
			std::vector<int> *generateMoves();
			Solver::Primitive primitiveValue();
			int hash(bool removeSymmetries);
			int currInt;
	};
}
