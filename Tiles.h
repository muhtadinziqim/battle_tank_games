#ifndef TILES_H
#define TILES_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

//using namespace glm;

//The dimensions of the level
const int LEVEL_WIDTH = 1;
const int LEVEL_HEIGHT = 1;

//Tile constants
const float TILE_WIDTH = 0.05;
const float TILE_HEIGHT = 0.05;
const int TOTAL_TILES = 100;
const int TOTAL_TILE_SPRITES = 2;

//The different tile sprites
const int TILE_WHITE = 0;
const int TILE_BLACK = 1;

class Tiles :
	public Engine::Game
{
public:
	Tiles();
	~Tiles();
	Tiles(float x, float y, int tyleType);
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void BuildSprite();
	void DrawSprite();
	void Destroy();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	float oldxpos;
	float oldypos;
	float frame_dur = 0, frame_width = 0, xpos = 0, ypos = 0, degree = 0, spriteWidth, spriteHeight;
	unsigned int frame_idx = 0, flip = 0;
	bool active;
	int n;
private:
	GLuint VBO, VAO, EBO, texture, program;
	bool walk_anim = false;

	//The tile type
	int mType;
};

#endif