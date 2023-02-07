#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Tile {X, O, B};
	class TTTPosition : public Solver::Position {
		protected:
			std::array<Tile, 9> tiles;
			Tile whoseMove;
	};
}
