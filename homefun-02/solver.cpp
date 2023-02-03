#include <iostream>
#include "solver.h"
#include <vector>
#include <unordered_map>

using namespace std;

int pos_to_int(TTTsolver::Position &position) {
	int sum = 0;
	array<TTTsolver::Tile, 9> tiles = position.tiles;
	for (int i = 0; i < 9; i++) {
		switch (tiles[i]) {
			case (TTTsolver::Tile::X):
				sum += 0;
				break;
			case (TTTsolver::Tile::O):
				sum += 1;
				break;
			case (TTTsolver::Tile::B):
				sum += 2;
				break;
		}
		sum *= 3;
	}
	if (position.whoseMove == TTTsolver::Tile::X) {
		sum += 0;
	} else {
		sum += 1;
	}
	return sum;
}

TTTsolver::Result TTTsolver::solve(TTTsolver::Position *position, 
		unordered_map<int, TTTsolver::Result> *memo, 
		unordered_map<int, TTTsolver::Result> *memo_prim) {

	int num = pos_to_int(*position);
	if (memo->find(num) != memo->end()) return memo->at(num);

	TTTsolver::Primitive currResult = TTTsolver::primitiveValue(position);
	TTTsolver::Result result;
	bool prim = false;
	switch (currResult) {
		case (TTTsolver::Primitive::WIN):
			result = TTTsolver::Result::WIN;
			prim = true;
			break;
		case (TTTsolver::Primitive::LOSE):
			result = TTTsolver::Result::LOSE;
			prim = true;
			break;
		case (TTTsolver::Primitive::TIE):
			result = TTTsolver::Result::TIE;
			prim = true;
			break;
	}
	if (prim) {
		memo->insert({num, result});
		memo_prim->insert({num, result});
		return result;
	}

	vector<int> moves = *generateMoves(position);
	bool win_found = false;
	bool tie_found = false;
	for (auto move : moves) {
		TTTsolver::Position *new_position = doMove(position, move);
		TTTsolver::Result result = solve(new_position, memo, memo_prim); 
		delete new_position;
		if (result == TTTsolver::Result::TIE) {
			tie_found = true;
		} else if (result == TTTsolver::Result::LOSE) {
			win_found = true;
		}
	}
	if (win_found) {
		result = TTTsolver::Result::WIN;
	} else if (tie_found) {
		result = TTTsolver::Result::TIE;
	} else {
		result = TTTsolver::Result::LOSE;
	}
	memo->insert({num, result});
	return result;
}

int main() {
	TTTsolver::Position position;
	position.tiles = {TTTsolver::Tile::B, TTTsolver::Tile::B, TTTsolver::Tile::B, 
					  TTTsolver::Tile::B, TTTsolver::Tile::B, TTTsolver::Tile::B,
					  TTTsolver::Tile::B, TTTsolver::Tile::B, TTTsolver::Tile::B};
	position.whoseMove = TTTsolver::Tile::X;
	unordered_map<int, TTTsolver::Result> memo;
	unordered_map<int, TTTsolver::Result> memo_prim;
	solve(&position, &memo, &memo_prim);

	int lost = 0;
	int tie = 0;
	int win = 0;
	for (auto pair : memo) {
		if (pair.second == TTTsolver::Result::LOSE) {
			lost += 1;		
		} else if (pair.second == TTTsolver::Result::TIE) {
			tie += 1;
		} else {
			win += 1;
		}
	}
	int lost_prim = 0;
	int tie_prim = 0;
	int win_prim = 0;
	for (auto pair : memo_prim) {
		if (pair.second == TTTsolver::Result::LOSE) {
			lost_prim += 1;		
		} else if (pair.second == TTTsolver::Result::TIE) {
			tie_prim += 1;
		} else {
			win_prim += 1;
		}
	}
	cout << lost << " lost (" << lost_prim << " primitive)\n";
	cout << tie << " tied (" << tie_prim << " primitive)\n";
	cout << win << " won (" << win_prim << " primitive)\n";
	return 0;
}
