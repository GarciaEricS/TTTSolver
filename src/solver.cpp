#include <vector>
#include <unordered_map>
#include <utility>
#include <bits/stdc++.h>
#include "../include/solver.h"

std::pair<Solver::Result, int> Solver::solve(Solver::Position *position, 
			bool removeSymmetries,
			std::unordered_map<long, std::pair<Solver::Result, int>> *memo) {
		int canonicalHash = position->hash(removeSymmetries);
		if (canonicalHash == 76112698) {
			std::cout << "here" << std::endl;
		}
		if (memo->find(canonicalHash) != memo->end()) {
			return memo->at(canonicalHash);
		}

		auto prim = position->primitiveValue();
		Result result;
		switch (prim) {
			case (Solver::Primitive::WIN):
				result = Solver::Result::WIN;
				break;
			case (Solver::Primitive::LOSE):
				result = Solver::Result::LOSE;
				break;
			case (Solver::Primitive::TIE):
				result = Solver::Result::TIE;
				break;
			case (Solver::Primitive::NOT_PRIMITIVE):
				result = Solver::Result::NIL;
				break;
		}
		if (result != Solver::Result::NIL) {
			memo->insert({canonicalHash, {result, 0}});
			return {result, 0};
		}

		auto moves = position->generateMoves();
		bool win_found = false;	
		bool tie_found = false;
		int win_remote = INT_MAX;
		int tie_remote = INT_MAX;
		int lose_remote = -1;
		for (auto move : *moves) {
			auto new_position = position->doMove(move);
			auto result_and_remote = solve(new_position, removeSymmetries, memo); 
			result = result_and_remote.first;
			auto remote = result_and_remote.second + 1;
			delete new_position;
			if (result == Solver::Result::TIE) {
				tie_found = true;
				tie_remote = std::min(tie_remote, remote);
			} else if (result == Solver::Result::LOSE) {
				win_found = true;
				win_remote = std::min(win_remote, remote);
			} else if (result == Solver::Result::WIN) {
				lose_remote = std::max(lose_remote, remote);
			} 
		}
		delete moves;
		int remoteness;
		if (win_found) {
			result = Solver::Result::WIN;
			remoteness = win_remote;
		} else if (tie_found) {
			result = Solver::Result::TIE;
			remoteness = tie_remote;
		} else {
			remoteness = lose_remote;
			result = Solver::Result::LOSE;
		}
		memo->insert({canonicalHash, {result, remoteness}});
		return {result, remoteness};
	}

