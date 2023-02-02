#include <iostream>
#include "solver.h"
#include <vector>
#include <map>

using namespace std;

TTTsolver::Result TTTsolver::solve(TTTsolver::Position *position) {
	TTTsolver::Primitive currResult = TTTsolver::primitiveValue(position);
	if (currResult == TTTsolver::Primitive::WIN) return TTTsolver::Result::WIN;
	if (currResult == TTTsolver::Primitive::LOSE) return TTTsolver::Result::LOSE;
	if (currResult == Primitive::TIE) return Result::TIE;

	vector<int> moves = *generateMoves(position);
	bool win_found = false;
	bool tie_found = false;
	for (auto move : moves) {
		TTTsolver::Position *new_position = doMove(position, move);
		TTTsolver::Result result = solve(new_position); delete new_position;
		if (result == TTTsolver::Result::TIE) {
			tie_found = true;
		} else if (result == TTTsolver::Result::LOSE) {
			win_found = true;
			break;
		}
	}
	if (win_found) {
		return TTTsolver::Result::WIN;
	} else if (tie_found) {
		return TTTsolver::Result::TIE;
	}
	return Result::LOSE;
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
