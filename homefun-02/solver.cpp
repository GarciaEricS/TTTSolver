#include <iostream>
#include "solver.h"
#include <vector>
#include <unordered_map>

using namespace std;

int pos_to_int(TTTsolver::Position position) {
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

TTTsolver::Result TTTsolver::solve(TTTsolver::Position *position, unordered_map<int, TTTsolver::Result> *memo) {
	int num = pos_to_int(*position);
	if (memo->find(num) != memo->end()) return memo->at(num);

	TTTsolver::Primitive currResult = TTTsolver::primitiveValue(position);
	if (currResult == TTTsolver::Primitive::WIN) return TTTsolver::Result::WIN;
	if (currResult == TTTsolver::Primitive::LOSE) return TTTsolver::Result::LOSE;
	if (currResult == Primitive::TIE) return Result::TIE;

	vector<int> moves = *generateMoves(position);
	TTTsolver::Result result;
	bool win_found = false;
	bool tie_found = false;
	for (auto move : moves) {
		TTTsolver::Position *new_position = doMove(position, move);
		TTTsolver::Result result = solve(new_position, memo); delete new_position;
		if (result == TTTsolver::Result::TIE) {
			tie_found = true;
		} else if (result == TTTsolver::Result::LOSE) {
			win_found = true;
			break;
		}
	}
	if (win_found) {
		result = TTTsolver::Result::WIN;
	} else if (tie_found) {
		result = TTTsolver::Result::TIE;
	} else {
		result = Result::LOSE;
	}
	memo->insert({num, result});
	return result;
}



/*
int main() {
	map<Result, char> conversion = {{Result::LOSE, 'L'},
									{Result::WIN, 'W'},
									{Result::TIE, 'T'},
									{Result::DRAW, 'D'}};

	for (int i = 0; i <= 10; i++) {
		cout << i;
		cout << ':';
		cout << ' ';
		cout << conversion[solve(i)];
		cout << '\n';
	}
	return 0;
}
*/
