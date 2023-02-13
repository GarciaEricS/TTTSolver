#include <array>
#include <iostream>
#include "TTT.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <bits/stdc++.h>
#include <algorithm>
#include <tuple>
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

std::pair<Solver::Result, int> solve(Solver::Position *position, 
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

void print_memo(std::unordered_map<int, std::pair<Solver::Result, int>> *memo, bool removeSymmetries) {
	std::vector<Counts> remote_count;
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
	std::cout << "10 to 0 Anaylsis: (Symmetries removal is " <<
		(removeSymmetries ? "On" : "Off") << ')' << '\n'; 
	std::cout << "-------------------------------------------\n";
	std::cout << "R: W L T Total\n";
	int overall_wins = 0;
	int overall_ties = 0;
	int overall_loses = 0;
	for (int i = remote_count.size() - 1; i >= 0; i--) {
		int total = remote_count[i].wins + remote_count[i].ties + remote_count[i].loses;
		auto counts = remote_count[i];
		overall_wins += counts.wins;
		overall_loses += counts.loses;
		overall_ties += counts.ties;
		std::cout << i << ": " << counts.wins << ' ' <<
		counts.loses << ' ' << counts.ties << ' ' << 
		total << '\n';
	}
	std::cout << "-------------------------------------------\n";
	std::cout << "Overall: " << overall_wins << " Wins, " <<
		overall_loses << " Loses, " <<
		overall_ties << " Ties, " <<
		overall_wins + overall_loses + overall_ties << " Total\n";
}

int main(int argc, char *argv[]) {
	bool removeSymmetries = true;
	Solver::Position *position_ptr;
	/*
	TTT::TTTPosition position;
	position.tiles = {TTT::Tile::B, TTT::Tile::B, TTT::Tile::B, 
					  TTT::Tile::B, TTT::Tile::B, TTT::Tile::B,
					  TTT::Tile::B, TTT::Tile::B, TTT::Tile::B};
	position.whoseMove = TTT::Tile::X;
	*/
	TTZ::TTZPosition position;
	position.currInt = 10;
	position_ptr = &position;
	std::unordered_map<int, std::pair<Solver::Result, int>> memo;

	if (argc > 1) {	
		if (argv[1][0] == 'f') {	
		removeSymmetries = false;
		}
	} /*
	if (argc == 3) {
		std::string game(argv[2]);
		if (game == "TTZ") {
			TTZ::TTZPosition TTZpos;
			TTZpos.currInt = 10;
			position_ptr = &TTZpos;
		}
	} */
	solve(position_ptr, removeSymmetries, &memo);
	print_memo(&memo, removeSymmetries);	
	return 0;
}
