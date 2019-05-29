#ifndef PLAYER_H
#define PLAYER_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80
#define SPEED 0.0003f

using namespace glm;

class Player :
	public Engine::Game
{
public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void MoveSprite(float deltaTime);
	void BuildSprite();
	void DrawSprite();
	void Destroy();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	float oldxpos;
	float oldypos;
	float frame_dur = 0, frame_width = 0, xpos = 0, ypos = 0, degree = 0, spriteWidth, spriteHeight;
	int nyawa = 3;
private:
	GLuint VBO, VAO, EBO, texture, texture_2, program;
	unsigned int frame_idx = 0, flip = 0;
	bool walk_anim = false;
};
#endif

