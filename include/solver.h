#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <bits/stdc++.h>

namespace Solver {
	enum class Result {WIN, TIE, LOSE, DRAW, NIL};
	enum class Primitive {WIN, TIE, LOSE, NOT_PRIMITIVE};

	
	class Position {
		public:
			virtual Position *doMove(int move) = 0;
			virtual std::vector<int> *generateMoves() = 0;
			virtual Primitive primitiveValue() = 0;
			virtual long hash(bool removeSymmetries) = 0;
			virtual std::string getName(bool typeSpecified) = 0;
			virtual ~Position() {};
	};

	
	std::pair<Solver::Result, int> solve(Solver::Position *position, 
			bool removeSymmetries,
			std::unordered_map<long, std::pair<Solver::Result, int>> *memo);
}

