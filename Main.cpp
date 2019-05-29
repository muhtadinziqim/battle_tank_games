
#include <iostream>
#include "Demo.h"
#include <thread>

int main(int argc, char** argv) {
	Engine::Game &game = Demo();
	game.Start("Battle Tank Sayya", 700, 700, true, WindowFlag::WINDOWED, 0, 1);
	return 0;
}
