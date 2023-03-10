#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Type {Regular, OnlyX, OnC};
	enum class Tile {X, O, B};
	using TTTMove = std::pair<int, Tile>;

	class TTTPosition : public Solver::Position<TTTMove> {
		public:
			TTTPosition(int m, int n, int k, Type type, bool misere);
			Position *doMove(TTTMove move);
			std::vector<TTTMove> *generateMoves();
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

    		bool kInARow(int XinARow, int OinARow);
    		std::pair<int, int> updateInARow(int i, int j, int XinARow, int OinARow);
			Tile getAt(int i, int j);
            void setAt(Tile tile, int i, int j);
	};
}