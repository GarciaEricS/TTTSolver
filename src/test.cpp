#include <string>
#include <iostream>
#include "../include/TTT.h"

int main() {
	TTT::TTTPosition position(3, 3, 3, TTT::Type::Regular, false);
	std::cout << position.getName(false) << '\n';
	std::cout << position.getBoard() << '\n';
	position.generateMoves();
	position = *position.doMove(0);
	std::cout << position.getBoard() << '\n';
}
