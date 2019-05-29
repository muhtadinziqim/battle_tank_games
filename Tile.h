#ifndef TILE_H
#define TILE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The dimensions of the level
const int LEVEL_WIDTH = 800;
const int LEVEL_HEIGHT = 600;

//Tile constants
const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture * mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//The tile
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render();

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};

class Tiling
{
public:
	Tiling();
	~Tiling();

	//Starts up SDL and creates window
	bool init(SDL_Window* window);

	//Loads media
	bool loadMedia(Tile* tiles[]);

	//Frees media and shuts down SDL
	void close(Tile* tiles[]);

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box, Tile* tiles[]);

	//Sets tiles from tile map
	bool setTiles(Tile *tiles[]);

	Tile* tileSet[TOTAL_TILES];

	void Draw();

private:

};

class DemoTile
{
public:
	DemoTile();
	~DemoTile();
private:

};

#endif