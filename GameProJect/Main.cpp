#include "GameStructure.h"


int main(int argc, char* argv[]) {
	GameBase* game = new GameBase();

	game->run();

	delete game;

	game = NULL;

	return 1;
}


