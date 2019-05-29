#include "loading.h"


Loading::Loading()
{
	frame_dur = 0, frame_width = 0, xpos = -10, ypos = -10, degree = 0, spriteWidth = 0, spriteHeight = 0;
	active = false;
}


Loading::~Loading()
{
}

void Loading::Init()
{
	BuildSprite();
	//BuildTank2();
}

void Loading::Update(float deltaTime)
{
}

void Loading::Render()
{
	DrawSprite();
}

void Loading::MoveSprite(float deltaTime)
{
	if (degree == 0) {
		ypos += deltaTime * SPEED;
	}
	else if (degree == 90) {
		xpos -= deltaTime * SPEED;
	}
	else if (degree == 180) {
		ypos -= deltaTime * SPEED;
	}
	else if (degree == 270) {
		xpos += deltaTime * SPEED;
	}

	mat4 transform;
	transform = translate(transform, vec3(xpos, ypos, 0.0f));

	glm::mat4 rotation;
	transform = glm::rotate(transform, glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint location = glGetUniformLocation(this->program, "transform");
	GLint location2 = glGetUniformLocation(this->program, "rotation");
	UseShader(this->program);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));
	glUniformMatrix4fv(location2, 1, GL_FALSE, value_ptr(rotation));

}

void Loading::DrawTeks() {
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


	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Loading::BuildTeks()
{
	this->program2 = BuildShader("spriteAnim.vert", "spriteAnim.frag");

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
	unsigned char* image = SOIL_load_image("res/loadingteks.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	float w = 0.6f;
	float x = w;
	float y = w/3;

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

void Loading::DrawSprite() {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLint location = glGetUniformLocation(this->program, "ourTexture");
	// Activate shader
	UseShader(this->program);

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	//	glDisable(GL_BLEND);
}

void Loading::BuildSprite()
{
	this->program = BuildShader("spriteAnim.vert", "spriteAnim.frag");

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program, "n");
	UseShader(this->program);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

										   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("res/loading.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	float w = 0.1f;
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

void Loading::Destroy() {
	if (texture != NULL)
	{
		program = NULL;
		VBO = NULL;
		VAO = NULL;
		EBO = NULL;
		texture = NULL;
		xpos = 10;
		ypos = 10;
		spriteWidth = 0;
		spriteHeight = 0;
	}
}

bool Loading::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

