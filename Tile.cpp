#include "Tile.h"


//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

void Tile::render()
{
	//If the tile is on screen
	if (true)
	{
		//Show the tile
		gTileTexture.render(mBox.x, mBox.y, &gTileClips[mType]);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

Tiling::Tiling() {

}

Tiling::~Tiling() {

}

bool Tiling::init(SDL_Window* window)
{
	cout << "Ziqi" << endl;
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		
		//Create renderer for window
		gRenderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
		
	}

	return success;
}

bool Tiling::loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;

	//Load tile texture
	if (!gTileTexture.loadFromFile("tiles.png"))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

void Tiling::close(Tile* tiles[])
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
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Tiling::checkCollision(SDL_Rect a, SDL_Rect b)
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

bool Tiling::setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

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
				tiles[i] = new Tile(x, y, tileType);
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
			gTileClips[TILE_RED].x = 0;
			gTileClips[TILE_RED].y = 0;
			gTileClips[TILE_RED].w = TILE_WIDTH;
			gTileClips[TILE_RED].h = TILE_HEIGHT;

			gTileClips[TILE_GREEN].x = 0;
			gTileClips[TILE_GREEN].y = 80;
			gTileClips[TILE_GREEN].w = TILE_WIDTH;
			gTileClips[TILE_GREEN].h = TILE_HEIGHT;

			gTileClips[TILE_BLUE].x = 0;
			gTileClips[TILE_BLUE].y = 160;
			gTileClips[TILE_BLUE].w = TILE_WIDTH;
			gTileClips[TILE_BLUE].h = TILE_HEIGHT;

			gTileClips[TILE_TOPLEFT].x = 80;
			gTileClips[TILE_TOPLEFT].y = 0;
			gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_LEFT].x = 80;
			gTileClips[TILE_LEFT].y = 80;
			gTileClips[TILE_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMLEFT].x = 80;
			gTileClips[TILE_BOTTOMLEFT].y = 160;
			gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_TOP].x = 160;
			gTileClips[TILE_TOP].y = 0;
			gTileClips[TILE_TOP].w = TILE_WIDTH;
			gTileClips[TILE_TOP].h = TILE_HEIGHT;

			gTileClips[TILE_CENTER].x = 160;
			gTileClips[TILE_CENTER].y = 80;
			gTileClips[TILE_CENTER].w = TILE_WIDTH;
			gTileClips[TILE_CENTER].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOM].x = 160;
			gTileClips[TILE_BOTTOM].y = 160;
			gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

			gTileClips[TILE_TOPRIGHT].x = 240;
			gTileClips[TILE_TOPRIGHT].y = 0;
			gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_RIGHT].x = 240;
			gTileClips[TILE_RIGHT].y = 80;
			gTileClips[TILE_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMRIGHT].x = 240;
			gTileClips[TILE_BOTTOMRIGHT].y = 160;
			gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool Tiling::touchesWall(SDL_Rect box, Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

void Tiling::Draw() {
	//Clear screen
//	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//	SDL_RenderClear(gRenderer);

	//Render level
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileSet[i]->render();
	}

	//Update screen
	SDL_RenderPresent(gRenderer);

	close(tileSet);
}

DemoTile::DemoTile() {
	
}

DemoTile::~DemoTile() {

}