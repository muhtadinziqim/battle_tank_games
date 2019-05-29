#ifndef MAP_H
#define MAP_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Tiles.h"

using namespace glm;


class Map :
	public Engine::Game
{
	//Starts up SDL and creates window
public:
	Map();
	~Map();
	
	virtual void Update(float deltaTime);
	virtual void Render();

	void Init();

	//Loads media
	bool loadMedia(Tiles* tiles[]);

	//Frees media and shuts down SDL
	void close(Tiles* tiles[]);

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box, Tiles* tiles[]);

	//Sets tiles from tile map
	bool setTiles(Tiles *tiles[]);

	Tiles* tileSet[TOTAL_TILES];
	Tiles TileClips[TOTAL_TILE_SPRITES];

	void Draw();

private:

};


#endif

