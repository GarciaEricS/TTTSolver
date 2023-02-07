#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include "TTT.h"

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

	int TTTPosition::hash() {
		int sum = 0;
		auto tls = this->tiles;
		for (int i = 0; i < 9; i++) {
			switch (tls[i]) {
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
		if (this->whoseMove == Tile::X) {
			sum += 0;
		} else {
			sum += 1;
		}
		return sum;
	}
};
