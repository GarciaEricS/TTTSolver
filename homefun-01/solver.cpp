#include <iostream>
#include "solver.h"
#include <vector>
#include <map>

using namespace std;
using namespace solver;

Result solve(int position) {
	Primitive currResult = primitiveValue(position);
	if (currResult == Primitive::WIN) return Result::WIN;
	if (currResult == Primitive::LOSE) return Result::LOSE;
	if (currResult == Primitive::TIE) return Result::TIE;

	vector<int> moves = *generateMoves(position);
	for (auto move : moves) {
		int new_position = doMove(position, move);
		if (solve(new_position) == Result::LOSE) {
			return Result::WIN;
		}
	}
	return Result::LOSE;
}

int main() {
	map<Result, char> conversion = {{Result::LOSE, 'L'},
									{Result::WIN, 'W'},
									{Result::TIE, 'T'},
									{Result::DRAW, 'D'}};


	for (int i = 0; i <= 25; i++) {
		cout << i;
		cout << ':';
		cout << ' ';
		cout << conversion[solve(i)];
		cout << '\n';
	}
	return 0;
}

