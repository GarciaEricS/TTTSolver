#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include "solver.h"
#include "CLIPosition.h"

namespace TTT {
	enum class Type {Regular, OnlyX, OnC};
	enum class Tile {X, O, B};
	using TTTMove = std::pair<int, Tile>;

	class TTTPosition : public CLI::CLIPosition {
		public:
			TTTPosition(int m, int n, int k, Type type, bool misere);
			TTTPosition *doMove(int move);
			std::vector<int> *generateMoves();
			Solver::Primitive primitiveValue();
			long hash(bool removeSymmetries);
            int canonicalHash();

			std::string getName(bool typeSpecified);
			std::string getBoard();
			std::string moveToStr(int move);
			TTTPosition *getAndSetVariant();
			int getAIMove(std::vector<int> *moves, std::unordered_map<long, std::pair<Solver::Result, int>> *solveMap);
			int getPlayerMove(std::vector<int> *moves);


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
