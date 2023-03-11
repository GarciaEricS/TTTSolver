#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Type {Regular, OnlyX, OnC};
	enum class Tile {X, O, B};
	using TTTMove = std::pair<int, Tile>;

	class TTTPosition : public Solver::Position {
		public:
			TTTPosition(int m, int n, int k, Type type, bool misere);
			Position *doMove(int move);
			std::vector<int> *generateMoves();
			Solver::Primitive primitiveValue();
			int hash(bool removeSymmetries);
            int canonicalHash();

		private:
			Tile whoseMove;
			int m;
			int n;
			int k;
			Type type;
			bool misere;
			std::vector<Tile> tiles;
			std::vector<TTTMove> availableMoves;

    		bool kInARow(int XinARow, int OinARow);
    		std::pair<int, int> updateInARow(int i, int j, int XinARow, int OinARow);
			Tile getAt(int i, int j);
            void setAt(Tile tile, int i, int j);
	};
}
