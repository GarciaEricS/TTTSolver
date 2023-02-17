#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include "TTT.h"
#include <bits/stdc++.h>
#include <algorithm>

namespace TTT {
	TTTPosition::TTTPosition(int m, int n, int k) {
		this->m = m;
		this->n = n;
		this->k = k;
		for (int i = 0; i < m * n; i++) {
			this->tiles.push_back(Tile::B);
		};
	}

    Tile getAt(int i, int j) {
        return tiles[i * n + j];
    }

    void setAt(Tile tile, int i, int j) {
        tiles[i * n + j] = tile;
    }

	std::vector<int> *TTTPosition::generateMoves() {
		std::vector<int>* moves = new std::vector<int>();
		auto tiles = this->tiles;

		for (int i = 0; i < m * n; i++) {
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
		auto piece = (whoseMove == Tile::X) ? Tile::O : Tile::X;
		int inARow;
		for (int i = 0; i < m; i++) {
			inARow = 0;
			for (int j = 0; j < n; j++) {
				if (getAt(i, j) == piece) {
					inARow += 1;
				} else {
					inARow = 0;
				}
				if (inARow == k) {
					return Solver::Primitive::LOSE;
				}
			}
		}

		for (int j = 0; j < n; j++) {
			inARow = 0;
			for (int i = 0; i < m; i++) {
				if (getAt(i, j) == piece) {
					inARow += 1;
				} else {
					inARow = 0;
				}
				if (inARow == k) {
					return Solver::Primitive::LOSE;
				}
			}
		}

		for (int s = 0; s < m; s++) {
			inARow = 0;
			int maxOffset = std::min(n, m - 1 - s);
			for (int off = 0; off <= maxOffset; off++) {
				int i = s + off;
				int j = off;
				if (getAt(i, j) == piece) {
					inARow += 1;
				} else {
					inARow = 0;
				}
				if (inARow == k) {
					return Solver::Primitive::LOSE;
				}
			}	
		}

		for (int s = 0; s < m; s++) {
			inARow = 0;
			int maxOffset = std::min(n, m - 1 - s);
			for (int off = 0; off <= maxOffset; off++) {
				int i = s + off;
				int j = n - 1 - off;
				if (getAt(i, j) == piece) {
					inARow += 1;
				} else {
					inARow = 0;
				}
				if (inARow == k) {
					return Solver::Primitive::LOSE;
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
	Solver::Position *TTTPosition::doMove(int move) {
		auto tls = this->tiles;
		Tile whose_move = this->whoseMove;
		tls[move] = whose_move;
		TTTPosition *new_position = new TTTPosition(m, n, k);
		new_position->tiles = tls;
		new_position->whoseMove = 
			whose_move == Tile::X ? Tile::O : Tile::X;
		return new_position;
	}

    int hash(std::vector<Tile> tiles, int m, int n) {
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

    int TTTPosition::canonicalHash() {
        int minHash = minReflectionHash(tiles, m, n);
        if (m == n) {
            std::vector<Tile> rotated = rotateBoard(tiles, m, n);
            int minRotatedHash = minReflectionHash(rotated, m, n);
            minHash = std::min(minHash, minRotatedHash);
        }
        return minHash;
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
        int hashNoReflect = hash(tiles, m, n);

        std::vector<Tile> reflected;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                reflected.push_back(tiles[(m - 1 - i) * n + j]);
            }
        }
        int hashVerticalReflect = hash(reflected, m, n);

        reflected.clear();
        for (int i = 0; i < m; i++) {
            for (int  = 0; j < n; j++) {
                reflected.push_back(tiles[i * n + n - 1 - j]);
            }
        }
        int hashHorizontalReflect = hash(relfected, m, n);

        reflected.clear();
        for (int i = 0; i < m; i++) {
            for (int  = 0; j < n; j++) {
                reflected.push_back(tiles[(m - 1 - i) * n + n - 1 - j]);
            }
        }
        int hashBothReflect = hash(reflected, m, n);

        return std::min(min(hashNoReflect, hashVerticalReflect), 
                        min(hashHorizontalReflect, hashBothReflect));
    }

	int TTTPosition::hash(bool removeSymmetries) {
        return removeSymmetries : canonicalHash() ? hash(tiles, m, n);
	}
};
