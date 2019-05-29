#ifndef LOADING_H
#define LOADING_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define SPEED 0.0005f

using namespace glm;

class Loading :
	public Engine::Game
{
public:
	Loading();
	~Loading();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void MoveSprite(float deltaTime);
	void BuildSprite();
	void DrawSprite();
	void BuildTeks();
	void DrawTeks();
	void Destroy();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	float oldxpos;
	float oldypos;
	float frame_dur = 0, frame_width = 0, xpos = 0, ypos = 0, degree = 0, spriteWidth, spriteHeight, xpos2, ypos2, spriteWidth2, spriteHeight2;
	bool active;
	int n;
	int iPeluru = 0;
private:
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
	unsigned int frame_idx = 0, flip = 0;
	bool walk_anim = false;
};
#endif

