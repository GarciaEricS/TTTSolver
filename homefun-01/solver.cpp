#include <iostream>
#include <stdio.h>
#include "solver.h"
#include <vector>
#include <assert.h>
#include <map>

using namespace std;
using namespace solver;

map<Result, char> conversion = {{Result::LOSE, 'L'},
								{Result::WIN, 'W'},
								{Result::TIE, 'T'},
								{Result::DRAW, 'D'}};

Result solve(int position) {
	Primitive currResult = primitiveValue(position);
	if (currResult == Primitive::WIN) return Result::WIN;
	if (currResult == Primitive::LOSE) return Result::LOSE;
	if (currResult == Primitive::TIE) return Result::TIE;

	bool won = false;
	vector<int> moves = *generateMoves(position);
	for (auto move : moves) {
		int new_position = doMove(position, move);
		Result result = solve(new_position);
		if (result == Result::LOSE) {
			won = true;
		}
	}
	if (won) {
		return Result::WIN;
	}
	return Result::LOSE;
}

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

