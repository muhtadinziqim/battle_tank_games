#include "fsm.h"


Fsm::Fsm()
{
	frame_dur = 0, frame_width = 0, xpos = -10, ypos = -10, degree = 0, spriteWidth = 0, spriteHeight = 0;
	active = false;
}


Fsm::~Fsm()
{
}

Fsm::Fsm(float x, float y) {
	xpos = x;
	ypos = y;
}

void Fsm::Init()
{
	//BuildSprite();
	//BuildTank2();
}

void Fsm::Update(float deltaTime)
{
	MoveSprite(deltaTime);
}

void Fsm::Render()
{
	//DrawSprite();
}

void Fsm::MoveSprite(float deltaTime)
{
	mat4 transform;
	transform = translate(transform, vec3(xpos, ypos, 0.0f));

	GLint location = glGetUniformLocation(this->program, "transform");
	UseShader(this->program);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));

}


void Fsm::DrawFsm() {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_fsm);
	glUniform1i(glGetUniformLocation(this->program, "fsm"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(this->program, "agentMap_"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->program, "fsmMap"), 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->program, "worldMap"), 3);

	// Activate shader
	UseShader(this->program);
	//glUniform1i(location2, 1);

	// Draw crate
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Fsm::BuildFsm()
{
	this->program = BuildShader("fsm.vert", "fsm.frag");
	
	int width, height;

	// Load and create a texture 
	glGenTextures(1, &texture_fsm);
	glBindTexture(GL_TEXTURE_2D, texture_fsm); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

												// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture
	unsigned char* image = SOIL_load_image("peluru.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Load and create a texture 
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture
	unsigned char* agentMap = SOIL_load_image("agentMap.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, agentMap);
	SOIL_free_image_data(agentMap);
	glBindTexture(GL_TEXTURE_2D, 1); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture
	unsigned char* fsmMap = SOIL_load_image("fsm_map.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, fsmMap);
	SOIL_free_image_data(fsmMap);
	glBindTexture(GL_TEXTURE_2D, 2); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture
	unsigned char* wMap = SOIL_load_image("world_map.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, wMap);
	SOIL_free_image_data(wMap);
	glBindTexture(GL_TEXTURE_2D, 3); // Unbind texture when done, so we won't accidentily mess up our texture.


	float w = 0.01f;
	float x = w;
	float y = w;

	spriteWidth = 2.5 * x;
	spriteHeight = 2.5 * y;

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

void Fsm::Destroy() {
	if (texture_fsm != NULL)
	{
		program = NULL;
		VBO = NULL;
		VAO = NULL;
		EBO = NULL;
		texture_fsm = NULL;
		xpos = 10;
		ypos = 10;
		spriteWidth = 0;
		spriteHeight = 0;
	}
}

bool Fsm::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

void Fsm::Posisi(float x, float y) {
	xpos = x;
	ypos = y;
}
