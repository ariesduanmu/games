#include "game.h"

int main(int argc, char** agrv)
{
	AceyDucey game;
	game.Introduction();
	while (!game.IsGameOver()) {
		game.RoundStart();
	}
	return 0;
}