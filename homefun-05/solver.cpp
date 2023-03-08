#include <iostream>
#include "TTT.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>

struct Counts {
	int wins;
	int loses;
	int draws;
	int ties;
};

Solver::Result prim_to_result(Solver::Primitive prim) {
	Solver::Result result;
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
	return result;
}

template <class Move>
std::pair<Solver::Result, int> solve(Solver::Position<Move> *position, 
		bool removeSymmetries,
		std::unordered_map<int, std::pair<Solver::Result, int>> *memo) {

	int canonicalHash = position->hash(removeSymmetries);
	if (memo->find(canonicalHash) != memo->end()) {
		return memo->at(canonicalHash);
	}

	auto prim = position->primitiveValue();
	auto result = prim_to_result(prim);
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

void print_memo(std::unordered_map<int, std::pair<Solver::Result, int>> *memo, int m, int n, int k, bool removeSymmetries, int typeInt, bool misere) {
	std::vector<Counts> remote_count;
	std::string typeStr;
	switch (typeInt) {
		case (0):
			typeStr = "Regular";
			break;
		case (1):
			typeStr = "Only X";
			break;
		case (2):
			typeStr = "Order and Chaos";
			break;
	}
	std::string misereStr;
	misereStr = misere ? " Misere" : "";
	for (auto pair : *memo) {
		auto result = pair.second.first;
		auto remoteness = pair.second.second;	
		int prev_size = remote_count.size();
		if (remoteness >= prev_size) {
			remote_count.resize(remoteness + 1);
		}
		for (int i = prev_size; i <= remoteness; i++) {
			remote_count[i] = {0, 0, 0, 0};
		}	
		if (result == Solver::Result::LOSE) {
			remote_count[remoteness].loses += 1;		
		} else if (result == Solver::Result::TIE) {
			remote_count[remoteness].ties += 1;;
		} else {
			remote_count[remoteness].wins += 1;
		}
	}
	std::cout << m << 'x' << n << " (" << k << "-in-a-row) " <<"TicTacToe (" << typeStr << misereStr << ") Anaylsis: (Symmetries removal is " <<
		(removeSymmetries ? "On" : "Off") << ')' << '\n'; 
	std::cout << "-------------------------------------------\n";
	std::cout << "R:\tW\tL\tT\tTotal\n";
	int overall_wins = 0;
	int overall_ties = 0;
	int overall_loses = 0;
	for (int i = remote_count.size() - 1; i >= 0; i--) {
		int total = remote_count[i].wins + remote_count[i].ties + remote_count[i].loses;
		auto counts = remote_count[i];
		overall_wins += counts.wins;
		overall_loses += counts.loses;
		overall_ties += counts.ties;
		std::cout << i << ":\t" << counts.wins << '\t' <<
		counts.loses << '\t' << counts.ties << '\t' << 
		total << '\n';
	}
	std::cout << "-------------------------------------------\n";
	std::cout << "Total Wins: " << overall_wins << '\n' <<
		"Total Loses: " << overall_loses << '\n' <<
		"Total Ties: " << overall_ties << '\n' <<
		"Total Positions: " << overall_wins + overall_loses + overall_ties << '\n';
}

int main(int argc, char *argv[]) {
	bool removeSymmetries = true;
	int m = 3;
	int n = 3;
	int k = 3;
	int typeInt;
	TTT::Type type = TTT::Type::Regular;
	bool misere = false;
	if (argc > 3) {
		m = atoi(argv[1]);
		n = atoi(argv[2]);
		k = atoi(argv[3]);
	}
	if (argc > 4) {
		typeInt = atoi(argv[4]);
		switch (typeInt) {
			case (0):
				type = TTT::Type::Regular;
				break;
			case (1):
				type = TTT::Type::OnlyX;
				break;
			case (2):
				type = TTT::Type::OnC;
		}
	}
	if (argc > 5) {
		if (argv[5][0] == 't') {
			misere = true;
		}
	}
	if (argc > 6) {	
		if (argv[6][0] == 'f') {	
		removeSymmetries = false;
		}
	}
	TTT::TTTPosition position(m, n, k, type, misere);
	TTT::TTTPosition *position_ptr = &position;
	std::unordered_map<int, std::pair<Solver::Result, int>> memo;
	solve(position_ptr, removeSymmetries, &memo);
	print_memo(&memo, m, n, k, removeSymmetries, typeInt, misere);	
	return 0;
}
