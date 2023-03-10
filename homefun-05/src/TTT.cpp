#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include "../include/TTT.h"
#include <bits/stdc++.h>
#include <algorithm>

namespace TTT {
TTTPosition::TTTPosition(int m, int n, int k, Type type, bool misere) {
	this->type = type;	
	this->misere = misere;
	this->m = m;
	this->n = n;
	this->k = k;
	for (int i = 0; i < m * n; i++) {
		this->tiles.push_back(Tile::B);
	};
}

Tile TTTPosition::getAt(int i, int j) {
	return tiles[i * n + j];
}

void TTTPosition::setAt(Tile tile, int i, int j) {
	tiles[i * n + j] = tile;
}

std::vector<std::pair<int, Tile>> *TTTPosition::generateMoves() {
	std::vector<std::pair<int, Tile>>* moves = new std::vector<std::pair<int, Tile>>();
	auto tiles = this->tiles;

	for (int i = 0; i < m * n; i++) {
		if (tiles[i] == Tile::B) {
			if (type == Type::Regular) {
				moves->push_back({i, whoseMove});
			} else if (type == Type::OnlyX) {
				moves->push_back({i, Tile::X});
			} else { // Order and Chaos
				moves->push_back({i, Tile::X});
				moves->push_back({i, Tile::O});
			}
		}
	}
	return moves;
}

std::pair<int, int> TTTPosition::updateInARow(int i, int j, int XinARow, int OinARow) {
	switch (getAt(i, j)) {
		case (Tile::X):
			XinARow++;
			OinARow = 0;
			break;
		case (Tile::O):
			XinARow = 0;
			OinARow++;
			break;
		default:
			XinARow = 0;
			OinARow = 0;
	}
	return {XinARow, OinARow};
}

bool TTTPosition::kInARow(int XinARow, int OinARow) {
	switch (type) {
		case (Type::Regular):
			return (whoseMove == Tile::X) ? (OinARow == k) : (XinARow == k);
		case (Type::OnlyX):
			return XinARow == k;
		case (Type::OnC):
			return (XinARow == k) || (OinARow == k);
	}
	return false; // Never reached.
}

Solver::Primitive TTTPosition::primitiveValue() {
	bool winOrLoseCondition = (type == Type::OnC) ? (whoseMove == Tile::X) : misere;
	auto winOrLose = winOrLoseCondition ? Solver::Primitive::WIN : Solver::Primitive::LOSE;
	int XinARow;
	int OinARow;
	for (int i = 0; i < m; i++) {
		XinARow = OinARow = 0;
		for (int j = 0; j < n; j++) {
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}
	}

	for (int j = 0; j < n; j++) {
		XinARow = OinARow = 0;
		for (int i = 0; i < m; i++) {
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}
	}

	for (int s = 0; s < m; s++) {
		XinARow = OinARow = 0;
		int maxOffset = std::min(n - 1, m - 1 - s);
		for (int off = 0; off <= maxOffset; off++) {
			int i = s + off;
			int j = off;
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}	
	}

	for (int s = 0; s < n; s++) {
		XinARow = OinARow = 0;
		int maxOffset = std::min(m - 1, n-1-s);
		for (int off = 0; off <= maxOffset; off++) {
			int i = off;
			int j = s + off;
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}
	}

	for (int s = 0; s < m; s++) {
		XinARow = OinARow = 0;
		int maxOffset = std::min(n - 1, m - 1 - s);
		for (int off = 0; off <= maxOffset; off++) {
			int i = s + off;
			int j = n - 1 - off;
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}	
	}

	for (int s = 0; s < n; s++) {
		XinARow = OinARow = 0;
		int maxOffset = std::min(m - 1, n-1-s);
		for (int off = 0; off <= maxOffset; off++) {
			int i = m - 1 - off;
			int j = s + off;
			auto inARows = updateInARow(i, j, XinARow, OinARow);
			XinARow = inARows.first;
			OinARow = inARows.second;
			if (kInARow(XinARow, OinARow)) {
				return winOrLose;
			}
		}
	}

	for (int i = 0; i < m * n; i++) {
		if (tiles[i] == Tile::B) {
			return Solver::Primitive::NOT_PRIMITIVE;
		}
	}
	return Solver::Primitive::TIE;
}

// Creates a new_position pointer which must later be freed
TTTPosition::Position *TTTPosition::doMove(std::pair<int, Tile>  move) {
	auto tls = this->tiles;
	int index = move.first;
	Tile tile = move.second;
	tls[index] = tile;
	TTTPosition *new_position = new TTTPosition(m, n, k, type, misere);
	new_position->tiles = tls;
	new_position->whoseMove = 
		whoseMove == Tile::X ? Tile::O : Tile::X;
	return new_position;
}

int hashPos(std::vector<Tile> tiles, int m, int n) {
	int sum = 0;
	for (int i = 0; i < m * n; i++) {
		switch (tiles[i]) {
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
	return sum;
}

std::vector<Tile> rotateBoard(std::vector<Tile> tiles, int m, int n) {
	std::vector<Tile> rotated;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			rotated.push_back(tiles[j * n + n - 1 - i]);
		}
	}
	return rotated;
}

int minReflectionHash(std::vector<Tile> tiles, int m, int n) {
	int hashNoReflect = hashPos(tiles, m, n);

	std::vector<Tile> reflected;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			reflected.push_back(tiles[(m - 1 - i) * n + j]);
		}
	}
	int hashVerticalReflect = hashPos(reflected, m, n);

	reflected.clear();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			reflected.push_back(tiles[i * n + n - 1 - j]);
		}
	}
	int hashHorizontalReflect = hashPos(reflected, m, n);

	reflected.clear();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			reflected.push_back(tiles[(m - 1 - i) * n + n - 1 - j]);
		}
	}
	int hashBothReflect = hashPos(reflected, m, n);

	return std::min(std::min(hashNoReflect, hashVerticalReflect), 
					std::min(hashHorizontalReflect, hashBothReflect));
}

int TTTPosition::canonicalHash() {
	int minHash = minReflectionHash(tiles, m, n);
	if (m == n) {
		std::vector<Tile> rotated = rotateBoard(tiles, m, n);
		int minRotatedHash = minReflectionHash(rotated, m, n);
		minHash = std::min(minHash, minRotatedHash);
	}
	return minHash;
}

int TTTPosition::hash(bool removeSymmetries) {
	return removeSymmetries ? canonicalHash() : hashPos(tiles, m, n);
}
};

