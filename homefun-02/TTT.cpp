#include <iostream>
#include <vector>
#include <array>
#include "solver.h"
#include <unordered_map>

using namespace std;

vector<int>* TTTsolver::generateMoves(TTTsolver::Position *position) {
	vector<int>* moves = new vector<int>();
	array<TTTsolver::Tile, 9> tiles = position->tiles;

	for (int i = 0; i < 9; i++) {
		if (tiles[i] == TTTsolver::Tile::B) {
			moves->push_back(i);
		}
	}
	return moves;
}
bool line_at(array<TTTsolver::Tile, 9> &tiles, int x, int y, int z) {
	return tiles[x] != TTTsolver::Tile::B && tiles[x] == tiles[y] && tiles[y] == tiles[z];
}

TTTsolver::Primitive TTTsolver::primitiveValue(TTTsolver::Position *position) {
	array<TTTsolver::Tile, 9> tiles = position->tiles;
	TTTsolver::Tile whoseMove = position->whoseMove;
	if (
			line_at(tiles, 0, 1, 2) ||
			line_at(tiles, 3, 4, 5) ||
			line_at(tiles, 6, 7, 8) ||
			line_at(tiles, 0, 3, 6) || 
			line_at(tiles, 1, 4, 7) || 
			line_at(tiles, 2, 5, 8) || 
			line_at(tiles, 0, 4, 8) || 
			line_at(tiles, 2, 4, 6)
	) {
		return TTTsolver::Primitive::LOSE;
	} for (int i = 0; i < 9; i++) {
		if (tiles[i] == TTTsolver::Tile::B) {
			return TTTsolver::Primitive::NOT_PRIMITIVE;
		}
	}
	return TTTsolver::Primitive::TIE;
}
// Creates a new_position pointer which must later be freed
TTTsolver::Position *TTTsolver::doMove(TTTsolver::Position *position, int move) {
	array<TTTsolver::Tile, 9> tiles = position->tiles;
	TTTsolver::Tile whose_move = position->whoseMove;
	tiles[move] = whose_move;
	TTTsolver::Position *new_position = new TTTsolver::Position();
	new_position->tiles = tiles;
	new_position->whoseMove = 
		whose_move == TTTsolver::Tile::X ? TTTsolver::Tile::O : TTTsolver::Tile::X;
	return new_position;
}

