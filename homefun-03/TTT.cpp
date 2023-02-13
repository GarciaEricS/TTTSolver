#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include "TTT.h"
#include <bits/stdc++.h>
#include <algorithm>

namespace TTT {
	std::vector<int> *TTTPosition::generateMoves() {
		std::vector<int>* moves = new std::vector<int>();
		std::array<Tile, 9> tiles = this->tiles;

		for (int i = 0; i < 9; i++) {
			if (tiles[i] == Tile::B) {
				moves->push_back(i);
			}
		}
		return moves;
	}
	bool TTTPosition::line_at(int x, int y, int z) {
		return tiles[x] != Tile::B && tiles[x] == tiles[y] && tiles[y] == tiles[z];
	}

	Solver::Primitive TTTPosition::primitiveValue() {
		Tile whoseMove = this->whoseMove;
		if (
				line_at(0, 1, 2) ||
				line_at(3, 4, 5) ||
				line_at(6, 7, 8) ||
				line_at(0, 3, 6) || 
				line_at(1, 4, 7) || 
				line_at(2, 5, 8) || 
				line_at(0, 4, 8) || 
				line_at(2, 4, 6)
		) {
			return Solver::Primitive::LOSE;
		} for (int i = 0; i < 9; i++) {
			if (tiles[i] == Tile::B) {
				return Solver::Primitive::NOT_PRIMITIVE;
			}
		}
		return Solver::Primitive::TIE;
	}
	// Creates a new_position pointer which must later be freed
	Solver::Position *TTTPosition::doMove(int move) {
		auto tls = this->tiles;
		Tile whose_move = this->whoseMove;
		tls[move] = whose_move;
		TTTPosition *new_position = new TTTPosition();
		new_position->tiles = tls;
		new_position->whoseMove = 
			whose_move == Tile::X ? Tile::O : Tile::X;
		return new_position;
	}

	int TTTPosition::hash(bool removeSymmetries) {
		int allSymmetries[8][9] = {
			{0, 1, 2, 3, 4, 5, 6, 7, 8},
			{6, 3, 0, 7, 4, 1, 8, 5, 2},
			{8, 7, 6, 5, 4, 3, 2, 1, 0},
			{2, 5, 8, 1, 4, 7, 0, 3, 6},
			{2, 1, 0, 5, 4, 3, 8, 7, 6},
			{8, 5, 2, 7, 4, 1, 6, 3, 0},
			{6, 7, 8, 3, 4, 5, 0, 1, 2},
			{0, 3, 6, 1, 4, 7, 2, 5, 8}
		};
		int sum;
		int minHash = INT_MAX; 
		auto tls = this->tiles;
		int symmetriesToConsider = removeSymmetries ? 8 : 1;
		for (int i = 0; i < symmetriesToConsider; i++) {
			sum = 0;
			for (int j : allSymmetries[i]) {
				switch (tls[j]) {
					case (Tile::X):
						sum += 0;
						break;
					case (Tile::O):
						sum += 1;
						break;
					case (Tile::B):
						sum += 2;
						break;
				}
				sum *= 3;
			}
			minHash = std::min(minHash, sum); 
		}
		if (this->whoseMove == Tile::X) {
			minHash += 0;
		} else {
			minHash += 1;
		}
		return minHash;
	}
};
