#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Type {Regular, OnlyX, OnC};
	class TTTPosition : public Solver::Position {
		public:
			TTTPosition(int m, int n, int k, Type type, bool misere);
			Position *doMove(std::pair<int, Solver::Tile> move);
			std::vector<std::pair<int, Solver::Tile>> *generateMoves();
			Solver::Primitive primitiveValue();
			int hash(bool removeSymmetries);
            int canonicalHash();
			Solver::Tile whoseMove;

		protected:
    		bool kInARow(int XinARow, int OinARow);
    		std::pair<int, int> updateInARow(int i, int j, int XinARow, int OinARow);
			bool line_at(int x, int y, int z);
			int m;
			int n;
			int k;
			Type type;
			bool misere;
			std::vector<Solver::Tile> tiles;
            Solver::Tile getAt(int i, int j);
            void setAt(Solver::Tile tile, int i, int j);
	};
}
