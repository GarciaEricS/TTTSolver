#include <iostream>
#include "TTT.h"
#include <vector>
#include <unordered_map>

Solver::Result solve(Solver::Position *position, 
		std::unordered_map<int, Solver::Result> *memo, 
		std::unordered_map<int, Solver::Result> *memo_prim) {

	int num = position->hash();
	if (memo->find(num) != memo->end()) return memo->at(num);

	auto currResult = position->primitiveValue();
	Solver::Result result;
	bool prim = false;
	switch (currResult) {
		case (Solver::Primitive::WIN):
			result = Solver::Result::WIN;
			prim = true;
			break;
		case (Solver::Primitive::LOSE):
			result = Solver::Result::LOSE;
			prim = true;
			break;
		case (Solver::Primitive::TIE):
			result = Solver::Result::TIE;
			prim = true;
			break;
	}
	if (prim) {
		memo->insert({num, result});
		memo_prim->insert({num, result});
		return result;
	}

	auto moves = position->generateMoves();
	bool win_found = false;
	bool tie_found = false;
	for (auto move : *moves) {
		auto new_position = position->doMove(move);
		auto result = solve(new_position, memo, memo_prim); 
		delete new_position;
		if (result == Solver::Result::TIE) {
			tie_found = true;
		} else if (result == Solver::Result::LOSE) {
			win_found = true;
		}
	}
	delete moves;
	if (win_found) {
		result = Solver::Result::WIN;
	} else if (tie_found) {
		result = Solver::Result::TIE;
	} else {
		result = Solver::Result::LOSE;
	}
	memo->insert({num, result});
	return result;
}

int main() {
	TTT::TTTPosition position;
	position.tiles = {TTT::Tile::B, TTT::Tile::B, TTT::Tile::B, 
					  TTT::Tile::B, TTT::Tile::B, TTT::Tile::B,
					  TTT::Tile::B, TTT::Tile::B, TTT::Tile::B};
	position.whoseMove = TTT::Tile::X;
	std::unordered_map<int, Solver::Result> memo;
	std::unordered_map<int, Solver::Result> memo_prim;
	solve(&position, &memo, &memo_prim);

	int lost = 0;
	int tie = 0;
	int win = 0;
	for (auto pair : memo) {
		if (pair.second == Solver::Result::LOSE) {
			lost += 1;		
		} else if (pair.second == Solver::Result::TIE) {
			tie += 1;
		} else {
			win += 1;
		}
	}
	int lost_prim = 0;
	int tie_prim = 0;
	int win_prim = 0;
	for (auto pair : memo_prim) {
		if (pair.second == Solver::Result::LOSE) {
			lost_prim += 1;		
		} else if (pair.second == Solver::Result::TIE) {
			tie_prim += 1;
		} else {
			win_prim += 1;
		}
	}
	std::cout << lost << " lost (" << lost_prim << " primitive)\n";
	std::cout << tie << " tied (" << tie_prim << " primitive)\n";
	std::cout << win << " won (" << win_prim << " primitive)\n";
	std::cout << lost + tie + win << " total (" << 
		lost_prim + tie_prim + win_prim << " primitive)\n";
	return 0;
}
