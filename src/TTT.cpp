#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "../include/TTT.h"
#include "../include/CLIPosition.h"
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
	}
}

Tile TTTPosition::getAt(int i, int j) {
	return tiles[i * n + j];
}

void TTTPosition::setAt(Tile tile, int i, int j) {
	tiles[i * n + j] = tile;
}

std::vector<int> *TTTPosition::generateMoves() {
	availableMoves.clear();
	std::vector<int>* moves = new std::vector<int>();
	auto tiles = this->tiles;

	for (int i = 0; i < m * n; i++) {
		if (tiles[i] == Tile::B) {
			if (type == Type::Regular) {
				moves->push_back(moves->size());
				availableMoves.push_back({i, whoseMove});
			} else if (type == Type::OnlyX) {
				moves->push_back(moves->size());
				availableMoves.push_back({i, Tile::X});
			} else { // Order and Chaos
				moves->push_back(moves->size());
				moves->push_back(moves->size());
				availableMoves.push_back({i, Tile::X});
				availableMoves.push_back({i, Tile::O});
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
TTTPosition *TTTPosition::doMove(int move) {
	auto tls = this->tiles;
	auto movePair = availableMoves.at(move);
	int index = movePair.first;
	Tile tile = movePair.second;
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

// CLI Methods
std::string TTTPosition::getName(bool typeSpecified) {
	return "Tic-Tac-Toe";
}

std::string TTTPosition::getBoard() {
	std::string board = "";

	board.push_back(' ');
	board.push_back(' ');
	for (int j = 0; j < n; j++) {
		board.push_back(' ');
		board.append(std::to_string(j + 1));
		board.push_back(' ');
		if (j != n-1) {
			board.push_back(' ');
		}
	}
	board.push_back('\n');

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) {
				board.append(std::to_string(i + 1));
				board.push_back(' ');
			}
			auto tile = getAt(i, j);
			char tileChar;
			board.push_back(' ');
			switch (tile) {
				case TTT::Tile::X:
					tileChar = 'X';
					break;
				case TTT::Tile::O:
					tileChar = 'O';
					break;
				default:
					tileChar = ' ';
					break;
			}
			board.push_back(tileChar);
			board.push_back(' ');
			if (j != n - 1) board.push_back('|');
		}
		board.push_back('\n');
		if (i != m-1) {
			board.push_back(' ');
			board.push_back(' ');
			for (int j = 0; j < n; j++) {
				board.append("---");
				if (j != n-1) {
					board.push_back('+');
				}
			}
			board.push_back('\n');
		}
	}
	return board;
}

std::string TTTPosition::moveToStr(int move) {
	std::string retStr;
	auto movePair = availableMoves.at(move);
	int row = movePair.first / n + 1;
	int col = movePair.first % m + 1;
	retStr = "(";
	retStr.append(std::to_string(row));
	retStr.append(", ");
	retStr.append(std::to_string(col));
	retStr.push_back(')');
	if (type == Type::OnC) {
		retStr.append(" as ");
		if (movePair.second == TTT::Tile::O) {
			retStr.push_back('O');
		} else {
			retStr.push_back('X');
		}
	}
	return retStr;
}

int TTTPosition::getAIMove(std::vector<int> *moves, std::unordered_map<int, std::pair<Solver::Result, int>> *solveMap) {
	auto resultAndRemote = Solver::solve(this, true, solveMap);
	Solver::Result resultNeeded;
	int remoteNeeded;
	switch (resultAndRemote.first) {
		case (Solver::Result::WIN):
			resultNeeded = Solver::Result::LOSE;
			break;
		case (Solver::Result::LOSE):
			resultNeeded = Solver::Result::WIN;
			break;
		default: // Tie or Draw
			resultNeeded = resultAndRemote.first;
			break;
	}

	remoteNeeded = resultAndRemote.second - 1;
	TTTPosition *position;
	for (int move: *moves) {
		position = doMove(move);
		auto newResultAndRemotePair = Solver::solve(position, true, solveMap);
		if (newResultAndRemotePair.first == resultNeeded && newResultAndRemotePair.second == remoteNeeded) {
			return move;
		}
	}
	std::cout << "Error in generating AI Move.\n";
	return -1;
}

int TTTPosition::getPlayerMove(std::vector<int> *moves) {
	int inMove;
	std::string inString;
	int retMove;
	std::cout << "Undo (u) Or Predict (p) OR\n";
	for (int i = 0; i < moves->size(); i++) {
		auto move = moves->at(i);
		std::cout << i + 1 << ": " << moveToStr(move) << '\t'; 	
	}
	std::cout << '\n';
	std::cout << "Move number: ";
	std::cin >> inString; 
	if (inString == "u") {
		retMove = -1;
	} else if (inString == "p") {
		retMove = -2;
	}
	else {
		inMove = std::stoi(inString);
		retMove = moves->at(inMove - 1);
	}
	return retMove;
}

TTTPosition *TTTPosition::getAndSetVariant() {
	std::cout << "Num Rows: ";
	std::cin >> m;  
	std::cout << "Num Cols: ";
	std::cin >> n;  
	std::cout << "In-A-Row: ";
	std::cin >> k;  

	std::cout << "(1, Regular), (2, Only X), (3, Order and Chaos)" << '\n';
	int gameType;
	std::cin >> gameType;
	switch (gameType) {
		case (1):
			type = Type::Regular;
			break;
		case (2):
			type = Type::OnlyX;
			break;
		case (3):
			type = Type::OnC;
			break;
		default:
			std::cout << "Not a valid number";
			break;
	}

	std::cout << "Misere (t or f)\n";
	char misereChar;
	std::cin >> misereChar;
	switch (misereChar) {
		case ('t'):
			misere = true;
			break;
		case ('f'):
			misere = false;
			break;
		default:
			std::cout << "Please enter t or f.";
			break;
	}
	TTTPosition *newPos = new TTTPosition(m, n, k, type, misere);
	delete this;
	return newPos;
}
};

