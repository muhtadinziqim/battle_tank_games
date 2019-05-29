#include "Map.h"

//Tiles tileTexture;
//Tiles TileClips[TOTAL_TILE_SPRITES];

Map::Map() {

}

Map::~Map() {

}

void Map::Init() {
	loadMedia(tileSet);
	
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileSet[i]->BuildSprite();
	}
}

bool Map::loadMedia(Tiles* tiles[])
{

	//Loading success flag
	bool success = true;

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

void Map::close(Tiles* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] == NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	//Free loaded images
	//gTileTexture.free();

	//Destroy window	
	//SDL_DestroyRenderer(gRenderer);
	//gRenderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	//SDL_Quit();
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool Map::setTiles(Tiles* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	float x = 0, y = 0;

	//Open the map
	std::ifstream map("lazy.map");

	//If the map couldn't be loaded
	if (false)
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	if (true)
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tileSet[i] = new Tiles(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			TileClips[TILE_WHITE].frame_idx = 0;
			TileClips[TILE_WHITE].spriteWidth = TILE_WIDTH;
			TileClips[TILE_WHITE].spriteHeight = TILE_HEIGHT;

			TileClips[TILE_BLACK].frame_idx = 1;
			TileClips[TILE_BLACK].spriteWidth = TILE_WIDTH;
			TileClips[TILE_BLACK].spriteHeight = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool Map::touchesWall(SDL_Rect box, Tiles* tiles[])
{
	//Go through the tiles
//	for (int i = 0; i < TOTAL_TILES; ++i)
//	{
		//If the tile is a wall type tile
//		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
//		{
			//If the collision box touches the wall tile
//			if (checkCollision(box, tiles[i]->getBox()))
//			{
				return true;
//			}
//		}
//	}

	//If no wall tiles were touched
	return false;
}

void Map::Draw() {
	//Clear screen
	//	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//	SDL_RenderClear(gRenderer);

	//Render level
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileSet[i]->DrawSprite();
	}

	//Update screen
//	SDL_RenderPresent(gRenderer);
}

void Map::Update(float deltaTime)
{
}

void Map::Render()
{
}
