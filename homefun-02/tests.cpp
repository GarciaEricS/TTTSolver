#include "solver.h"
#include <assert.h>
#include <vector>

using namespace std;
using namespace TTTsolver;

int main() {
	// Blank board has no result
	Position position;
	Position *position_ptr;
	position.tiles =  {Tile::B, Tile::B, Tile::B, 
					   Tile::B, Tile::B, Tile::B,
					   Tile::B, Tile::B, Tile::B};
	position.whoseMove = Tile::X;
	assert (primitiveValue(&position) == Primitive::NOT_PRIMITIVE);

	//3 x's in a row is a lose for Os
	position.tiles = {Tile::X, Tile::X, Tile::X, 
					  Tile::B, Tile::B, Tile::B,
					  Tile::B, Tile::B, Tile::B};
	assert (primitiveValue(&position) == Primitive::LOSE);
	std::vector<int> test = {3, 4, 5, 6, 7, 8};
	assert (*generateMoves(&position) == test);

    position.tiles = {Tile::B, Tile::B, Tile::B, 
					  Tile::B, Tile::B, Tile::B,
					  Tile::B, Tile::B, Tile::B};
	// Playing a game from the beginning
	position_ptr = &position;
	position_ptr = doMove(position_ptr, 0);
	position_ptr = doMove(position_ptr, 3);
	position_ptr = doMove(position_ptr, 1);
	position_ptr = doMove(position_ptr, 4);
	position_ptr = doMove(position_ptr, 2);
	assert(primitiveValue(position_ptr) == Primitive::LOSE);	
	
	// Testing default gamestate is TIE
    position.tiles =  {Tile::B, Tile::B, Tile::B, 
					   Tile::B, Tile::B, Tile::B,
					   Tile::B, Tile::B, Tile::B};
	position.whoseMove = Tile::X;
	assert (solve(&position) == Result::TIE);
	
	// Testing for a guaranteed win
	position.tiles = {Tile::B, Tile::X, Tile::X, 
					   Tile::X, Tile::O, Tile::O,
					   Tile::X, Tile::O, Tile::O};
	position.whoseMove = Tile::X;
	assert(solve(&position) == Result::WIN);

    position.tiles = {Tile::X, Tile::X, Tile::B, 
					   Tile::X, Tile::B, Tile::O,
					   Tile::B, Tile::O, Tile::O};
	position.whoseMove = Tile::X;
	assert(solve(&position) == Result::WIN);
	
	// Testing for a guaranteed loss
	position.tiles = {Tile::X, Tile::X, Tile::B, 
					   Tile::X, Tile::O, Tile::B,
					   Tile::B, Tile::B, Tile::O};
	position.whoseMove = Tile::O;
	assert(solve(&position) == Result::LOSE);


}
