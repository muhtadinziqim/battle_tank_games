#ifndef ENEMY_H
#define ENEMY_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80
#define SPEED 0.0003f

using namespace glm;

class Enemy :
	public Engine::Game
{
public:
	Enemy();
	void Spawn(float posx, float posy);
	~Enemy();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void MoveSprite(float deltaTime);
	void DrawTank();
	void Destroy();
	void Serang(int i);
	void Kejar(float x1, float y1, float x2, float y2, float deltaTime);
	void Patroli(float deltaTime, int i);
	float HitungJarak(float x1, float y1, float x2, float y2);
	void Nabrak(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	float frame_dur = 0, frame_width = 0, degree = 0, xpos2 = 0, ypos2 = 0, crateWidth, crateHeight, oldxpos = -10, oldypos =10;
	GLuint program2;
	int nPeluru = 0;
	int floop = 0;
	int nyawa;
private:
	GLuint VBO, VBO2, VAO, VAO2, EBO, EBO2, texture1, texture2, texture3, program1, program3, program_tank, texture_tank;
	unsigned int frame_idx = 0, flip = 0;
	bool walk_anim = false;
	void BuildSprite();
	void UpdateSprite(float deltaTime);
	int indexEnemy[7];
};
#endif

