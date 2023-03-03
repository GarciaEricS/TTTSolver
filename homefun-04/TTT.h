#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"

namespace TTT {
	enum class Tile {X, O, B};
	enum class Type {Regular, OnlyX, OnC};
	class TTTPosition : public Solver::Position {
		public:
			TTTPosition(int m, int n, int k, Type type, bool misere);
			Position *doMove(int move);
			std::vector<int> *generateMoves();
			Solver::Primitive primitiveValue();
			int hash(bool removeSymmetries);
            int canonicalHash();
			Tile whoseMove;

		protected:
			bool line_at(int x, int y, int z);
			int m;
			int n;
			int k;
			Type type;
			bool misere;
			std::vector<Tile> tiles;
            Tile getAt(int i, int j);
            void setAt(Tile tile, int i, int j);
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
