#include "../include/CLIPosition.h"
#include "../include/TTT.h"
#include <stack>
#include <unordered_map>

std::string solveAndGetResultStr(CLI::CLIPosition *position, std::unordered_map<int, std::pair<Solver::Result, int>> *solveMap) {
	std::string resultStr;
	auto resultAndRemote = Solver::solve(position, true, solveMap); 
	auto result = resultAndRemote.first;
	auto remoteness = resultAndRemote.second;
	switch (result) {
		case (Solver::Result::WIN):
			resultStr = "Win";
			break;
		case (Solver::Result::LOSE):
			resultStr = "Lose";
			break;
		case (Solver::Result::TIE):
			resultStr = "Tie";
			break;
		case (Solver::Result::DRAW):
			resultStr = "Draw";
			break;
		default:
			resultStr = "You should not be here, message the dev on Github";
			break;
	}
	resultStr.append(" in ");
	resultStr.append(std::to_string(remoteness));
	return resultStr;
}

std::pair<CLI::CLIPosition*, bool> undo(CLI::CLIPosition *position, std::stack<CLI::CLIPosition*> *prevPositions, bool playerOneTurn, bool AIPresent) {
	int repeat = AIPresent ? 2 : 1;
	for (int i = 0; i < repeat; i++) {
		delete position;
		position = prevPositions->top();
		prevPositions->pop();
		playerOneTurn = !playerOneTurn;
	}
	return {position, playerOneTurn};
} 


std::pair<bool, bool> getHumanPlayers() {
	std::cout << "Select:\n" << "(1, Human vs Human), (2, Human vs AI), (3, AI vs Human)\n";
	bool playerOneHuman;
	bool playerTwoHuman;
	char in;
	std::cin >> in;
	switch (in) {
		case ('1'):
			playerOneHuman = true;
			playerTwoHuman = true;
			break;
		case ('2'):
			playerOneHuman = true;
			playerTwoHuman = false;
			break;
		case ('3'):
			playerOneHuman = false;
			playerTwoHuman = true;
			break;
		default:
			playerOneHuman = true;
			playerOneHuman = true;
			std::cout << "Incorrect option given. Defaulting to Human vs Human." << '\n';
			break;
	}
	return {playerOneHuman, playerTwoHuman};
}

void play(CLI::CLIPosition *position, bool playerOneTurn, bool playerOneHuman, bool playerTwoHuman, std::stack<CLI::CLIPosition*> *prevPositions, std::unordered_map<int, std::pair<Solver::Result, int>> *solverMap) {
	std::cout << "----------------------" << '\n';
	Solver::Primitive primVal;
	while ((primVal = position->primitiveValue()) == Solver::Primitive::NOT_PRIMITIVE) {
		std::cout << position->getBoard();
		auto moves = position->generateMoves();
		int move;
		if ((playerOneTurn && playerOneHuman) || (!playerOneTurn && playerTwoHuman)) {
			move = position->getPlayerMove(moves);
		} else {
			move = position->getAIMove(moves, solverMap);
		}
		if (move == -1) { // Undo
			auto posAndTurn = undo(position, prevPositions, playerOneTurn, !playerOneHuman || !playerTwoHuman);
			position = posAndTurn.first;
			playerOneTurn = posAndTurn.second;
		} else if (move == -2) { // Prediction
			std::cout << "\nRESULT: " << solveAndGetResultStr(position, solverMap) << '\n';	
		} else {
			prevPositions->push(position);
			auto newPosition = position->doMove(move);
			position = newPosition;
			playerOneTurn = !playerOneTurn;
		}
		std::cout << "----------------------" << '\n' << '\n';
	}
	std::cout << position->getBoard() << '\n';
	std::string result;
	if ((primVal == Solver::Primitive::WIN && playerOneTurn) ||
			(primVal == Solver::Primitive::LOSE && !playerOneTurn)) {
		result = "Player One Wins!";
	} else if ((primVal == Solver::Primitive::WIN && !playerOneTurn) ||
			(primVal == Solver::Primitive::LOSE && playerOneTurn)) {
		result = "Player Two Wins!";
	}
	else {
		result = "Tie!";
	}
	char undoChar;
	std::cout << result << '\n';
	std::cout << "Undo? (y or n)" << '\n';
	std::cin >> undoChar;
	if (undoChar == 'y') {
		auto posAndTurn = undo(position, prevPositions, playerOneTurn, !playerOneHuman || !playerTwoHuman);
		position = posAndTurn.first;
		playerOneTurn = posAndTurn.second;
		play(position, playerOneTurn, playerOneHuman, playerTwoHuman, prevPositions, solverMap);
	}
	while (!prevPositions->empty()) {
		delete prevPositions->top();
		prevPositions->pop();
	}
}

void play(CLI::CLIPosition *position) {
	std::stack<CLI::CLIPosition*> *prevPos = new std::stack<CLI::CLIPosition*>();
	std::unordered_map<int, std::pair<Solver::Result, int>> *solverMap = new std::unordered_map<int, std::pair<Solver::Result, int>>();
	auto playerHumanPair = getHumanPlayers(); 
	auto playerOneHuman = playerHumanPair.first;
	auto playerTwoHuman = playerHumanPair.second;
	play(position, true, playerOneHuman, playerTwoHuman, prevPos, solverMap);
	delete prevPos;
	delete solverMap;
}

int main() {
	std::cout << "Welcome to The Homefun CLI!\n";
	std::cout << "Press s to change variant settings. Press p to play with default settings.\n";
	TTT::TTTPosition *pos = new TTT::TTTPosition(3, 3, 3, TTT::Type::Regular, false);
	char option;
	std::cin >> option;
	if (option == 's') {
		pos = pos->getAndSetVariant();
	}
	play(pos);
}
