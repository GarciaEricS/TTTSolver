#pragma once
#include "solver.h"
#include <string>

namespace CLI {
	class CLIPosition : public Solver::Position {
		public:
			virtual CLIPosition *doMove(int move) = 0;
			virtual std::string getName(bool typeSpecified) = 0;
			virtual std::string getBoard() = 0;
			virtual std::string moveToStr(int move) = 0;
			virtual CLIPosition *getAndSetVariant() = 0;
			
			virtual int getAIMove(std::vector<int> *moves, std::unordered_map<long, std::pair<Solver::Result, int>> *solveMap) = 0;
			virtual int getPlayerMove(std::vector<int> *moves) = 0;
	};
}
