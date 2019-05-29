#include "Menu.h"


Menu ::Menu()
{
	
}


Menu::~Menu()
{
}

void Menu::Init()
{
	
}

void Menu::Update(float deltaTime)
{
	
}

void Menu::Render()
{
	//DrawSprite();
}

void Menu::DrawLogo() {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	GLint location = glGetUniformLocation(this->program2, "ourTexture");
	// Activate shader
	UseShader(this->program2);

	// Draw sprite
	glBindVertexArray(VAO2);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	mat4 model;
	model = translate(model, vec3(0.0f, 0.6f , 0.0f));
//	model = scale(model, vec3(2 / 2, 1 / 2, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program2, "model"), 1, GL_FALSE, value_ptr(model));

	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Menu::BuildLogo()
{
	this->program2 = BuildShader("logo.vert", "logo.frag");

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program2, "n");
	UseShader(this->program2);

	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

										   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("res/mm_logo.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	float w = 0.2f;
	float x = w * 3;
	float y = w;

	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

void Menu::BuildMenu()
{
	this->program = BuildShader("menu.vert", "menu.frag");

	float x, y;
	string buttons[NUM_BUTTON] = { "res/mm_exit_hover.png", "res/mm_play_hover.png" };
	string hover_buttons[NUM_BUTTON] = { "res/mm_exit.png", "res/mm_play.png" };
	////
	glGenTextures(2, &BtnTexture[0]);
	glGenTextures(2, &BtnHoverTexture[0]);

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program, "n");
	UseShader(this->program);

	// Load and create a texture 
	for (int i = 0; i < NUM_BUTTON; i++)
	{
	//	glGenTextures(2, &BtnTexture[i]);
		glBindTexture(GL_TEXTURE_2D, BtnTexture[i]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

												// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);/*
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

		// Load, create texture 
		int width, height;
		unsigned char* image = SOIL_load_image(buttons[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		float w = 0.15f;
		x = w;
		y = w / 2.5;

		BtnHeight[i] = (float)height;
		BtnWidth[i] = (float)width;


		//HOVER
		glBindTexture(GL_TEXTURE_2D, BtnHoverTexture[i]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

													 // Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);/*
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

																		 // Load, create texture 
		image = SOIL_load_image(hover_buttons[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		x = w;
		y = w / 2.5;

		BtnHoverHeight[i] = (float)height;
		BtnHoverWidth[i] = (float)width;
	}
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Menu::DrawMenu() {

	int texture_id[NUM_BUTTON] = { GL_TEXTURE0, GL_TEXTURE1};
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate shader
	UseShader(this->program);
	// Bind Textures using texture units
	glBindVertexArray(VAO);
	for (int i = 0; i < NUM_BUTTON; i++)
	{
		/*glActiveTexture(texture_id[i]);
		glBindTexture(GL_TEXTURE_2D, BtnTexture[i]);
		GLint location = glGetUniformLocation(this->program, "ourTexture");
*/
		glActiveTexture(texture_id[i]);
		glBindTexture(GL_TEXTURE_2D, (ActiveButtonIndex == i) ? BtnHoverTexture[i] : BtnTexture[i]);
		glUniform1i(glGetUniformLocation(this->program, "ourTexture"), i);

		mat4 model;
		model = translate(model, vec3(0.0f, ((i + 1) / 4.0) - 0.5, 0.0f));
		//	model = scale(model, vec3(2 / 2, 1 / 2, 1));
		glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

		glDrawArrays(GL_QUADS, 0, 4);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	}
	// Draw sprite
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Menu::BuildLvl()
{
	this->program3 = BuildShader("menu.vert", "menu.frag");

	float x, y;
	string hover_buttons[NUM_LEVEL] = { 
		"res/bt_npc1_hover.png", 
		"res/bt_npc5_hover.png",
		"res/bt_npc10_hover.png",
		"res/bt_npc15_hover.png",
		"res/bt_20x20_hover.png",
		"res/bt_30x30_hover.png",
		"res/bt_40x40_hover.png"
	};
	string buttons[NUM_LEVEL] = {
		"res/bt_npc1.png",
		"res/bt_npc5.png",
		"res/bt_npc10.png",
		"res/bt_npc15.png",
		"res/bt_20x20.png",
		"res/bt_30x30.png",
		"res/bt_40x40.png"
	};
	////
	glGenTextures(9, &LvlTexture[0]);
	glGenTextures(9, &LvlHoverTexture[0]);

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program3, "n");
	UseShader(this->program3);

	// Load and create a texture 
	for (int i = 0; i < NUM_LEVEL; i++)
	{
		//	glGenTextures(2, &BtnTexture[i]);
		glBindTexture(GL_TEXTURE_2D, LvlTexture[i]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

													 // Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);/*
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

																		 // Load, create texture 
		int width, height;
		unsigned char* image = SOIL_load_image(buttons[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		float w = 0.10f;
		x = w;
		y = w / 3;

		LvlHeight[i] = (float)height;
		LvlWidth[i] = (float)width;


		//HOVER
		glBindTexture(GL_TEXTURE_2D, LvlHoverTexture[i]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

														  // Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);/*
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
																		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

																		 // Load, create texture 
		image = SOIL_load_image(hover_buttons[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		x = w;
		y = w / 3;

		LvlHoverHeight[i] = (float)height;
		LvlHoverWidth[i] = (float)width;
	}
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Menu::DrawLvl() {

	int texture_id[NUM_LEVEL] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6 };
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate shader
	UseShader(this->program3);
	// Bind Textures using texture units
	glBindVertexArray(VAO3);
	for (int i = 0; i < NUM_LEVEL; i++)
	{
		/*glActiveTexture(texture_id[i]);
		glBindTexture(GL_TEXTURE_2D, BtnTexture[i]);
		GLint location = glGetUniformLocation(this->program, "ourTexture");
		*/
		glActiveTexture(texture_id[i]);
		glBindTexture(GL_TEXTURE_2D, (ActiveButtonLevel == i) ? LvlHoverTexture[i] : LvlTexture[i]);
		glUniform1i(glGetUniformLocation(this->program3, "ourTexture"), i);

		mat4 model;
		if (i == 0) 
		{
			model = translate(model, vec3(-0.4f, 0.2, 0.0f));
		}
		if (i == 1)
		{
			model = translate(model, vec3(0.0f, 0.2, 0.0f));
		}
		if (i == 2)
		{
			model = translate(model, vec3(0.4f, 0.2, 0.0f));
		}
		if (i == 3)
		{
			model = translate(model, vec3(-0.4f, -0.1, 0.0f));
		}
		if (i == 4)
		{
			model = translate(model, vec3(0.0f, -0.1, 0.0f));
		}
		if (i == 5)
		{
			model = translate(model, vec3(0.4f, -0.1, 0.0f));
		}
		if (i == 6)
		{
			model = translate(model, vec3(-0.4f, -0.4, 0.0f));
		}
		if (i == 7)
		{
			model = translate(model, vec3(0.0f, -0.4, 0.0f));
		}
		if (i == 8)
		{
			model = translate(model, vec3(0.4f, -0.4, 0.0f));
		}
		//	model = scale(model, vec3(2 / 2, 1 / 2, 1));
		glUniformMatrix4fv(glGetUniformLocation(this->program3, "model"), 1, GL_FALSE, value_ptr(model));

		glDrawArrays(GL_QUADS, 0, 4);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	}
	// Draw sprite
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Menu::DrawGameOver() {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexGameOver);
	GLint location = glGetUniformLocation(this->programGameOver, "ourTexture");
	// Activate shader
	UseShader(this->programGameOver);

	// Draw sprite
	glBindVertexArray(VAOGameOver);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	mat4 model;
	model = translate(model, vec3(0.0f, 0.0f, 0.0f));
	//	model = scale(model, vec3(2 / 2, 1 / 2, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->programGameOver, "model"), 1, GL_FALSE, value_ptr(model));

	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Menu::BuildGameOver()
{
	this->programGameOver = BuildShader("logo.vert", "logo.frag");


	// Load and create a texture 
	glGenTextures(1, &TexGameOver);
	glBindTexture(GL_TEXTURE_2D, TexGameOver); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("res/mm_game_over.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	float w = 0.2f;
	float x = w * 3;
	float y = w;

	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAOGameOver);
	glGenBuffers(1, &VBOGameOver);
	glGenBuffers(1, &EBOGameOver);

	glBindVertexArray(VAOGameOver);

	glBindBuffer(GL_ARRAY_BUFFER, VBOGameOver);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOGameOver);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

void Menu::DrawWin() {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexWin);
	GLint location = glGetUniformLocation(this->programWin, "ourTexture");
	// Activate shader
	UseShader(this->programWin);

	// Draw sprite
	glBindVertexArray(VAOWin);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	mat4 model;
	model = translate(model, vec3(0.0f, 0.0f, 0.0f));
	//	model = scale(model, vec3(2 / 2, 1 / 2, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->programWin, "model"), 1, GL_FALSE, value_ptr(model));

	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Menu::BuildWin()
{
	this->programWin = BuildShader("logo.vert", "logo.frag");


	// Load and create a texture 
	glGenTextures(1, &TexWin);
	glBindTexture(GL_TEXTURE_2D, TexWin); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("res/mm_win.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	float w = 0.2f;
	float x = w * 3;
	float y = w;

	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAOWin);
	glGenBuffers(1, &VBOWin);
	glGenBuffers(1, &EBOWin);

	glBindVertexArray(VAOWin);

	glBindBuffer(GL_ARRAY_BUFFER, VBOWin);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWin);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}