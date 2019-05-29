#ifndef MENU_H
#define MENU_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80
#define SPEED 0.0003f
#define NUM_BUTTON 2
#define NUM_LEVEL 7

using namespace glm;

class Menu :
	public Engine::Game
{
public:
	Menu();
	~Menu();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void DrawMenu();
	void BuildMenu();
	void DrawLogo();
	void BuildLogo();
	void DrawLvl();
	void BuildLvl();
	void BuildGameOver();
	void DrawGameOver();
	void BuildWin();
	void DrawWin();
	float frame_dur = 0, frame_width = 0, degree = 0, xpos2 = 0, ypos2 = 0, crateWidth, crateHeight, oldxpos = -10, oldypos = 10;
	GLuint program2;
	int ActiveButtonIndex = 0;
	int ActiveButtonLevel = 0;
private: 
	GLuint BtnTexture[NUM_BUTTON], BtnHoverTexture[NUM_BUTTON], LvlTexture[NUM_LEVEL], LvlHoverTexture[NUM_LEVEL];
	GLuint VBO, VBO2, VAO, VAO2, EBO, EBO2, texture1, texture2, texture3, program, program3, program_tank, texture_tank, VAO3, VBO3, EBO3;
	GLuint programGameOver, VBOGameOver, VAOGameOver, EBOGameOver, TexGameOver;
	GLuint programWin, VBOWin, VAOWin, EBOWin, TexWin;
	unsigned int frame_idx = 0, flip = 0;
	bool walk_anim = false;
	float BtnWidth[NUM_BUTTON], BtnHeight[NUM_BUTTON], BtnHoverWidth[NUM_BUTTON], BtnHoverHeight[NUM_BUTTON];
	float LvlWidth[NUM_LEVEL], LvlHeight[NUM_LEVEL], LvlHoverWidth[NUM_LEVEL], LvlHoverHeight[NUM_LEVEL];
};
#endif

