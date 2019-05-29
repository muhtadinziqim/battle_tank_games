#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>
#include <thread>
#include <iostream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "Peluru.h"
#include "Map.h"
#include "Menu.h"
#include "loading.h"
#include "fsm.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80
#define SPEED 0.0003f

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
private:
	GLuint VBO, VAO, EBO, texture, program;
	float frame_dur = 0, frame_width = 0, xpos = 0, ypos = 0, degree = 0, xpos2 = 0, ypos2 = 0, crateWidth, crateHeight, spriteWidth, spriteHeight;
	int nPeluru = 1;
	unsigned int frame_idx = 0, flip = 0;
	bool walk_anim = false;
	void Input(float deltaTime);
	void Collision(float deltaTime);
	void Fsm(float deltaTime);
	void BuildSprite();
	void BuildTank2();
	void DrawSprite();
	void UpdateSprite(float deltaTime);
	void MoveSprite(float deltaTime);
	int count = 0;
};

void membuatMap(string map, int jumlahTile);
void kurangiNyawa();
void kurangiNyawaPlayer();
float hitungPosx(float xpos);
float hitungPosy(float ypos);

bool setTiles(string maps, int jumlahTile);
#endif

