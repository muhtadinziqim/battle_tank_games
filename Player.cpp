#include "Player.h"


Player::Player()
{
	frame_dur = 0, frame_width = 0, xpos = -0.5, ypos = -0.6, degree = 0, spriteWidth = 0, spriteHeight = 0;
	nyawa = 3;
}


Player::~Player()
{
}

void Player::Init()
{
	BuildSprite();
	//BuildTank2();
}

void Player::Update(float deltaTime)
{
	MoveSprite(deltaTime);
}

void Player::Render()
{
	DrawSprite();
}

void Player::MoveSprite(float deltaTime)
{

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

void Player::DrawSprite() {
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

void Player::BuildSprite()
{
	this->program = BuildShader("spriteAnim.vert", "spriteAnim.frag");

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program, "n");
	UseShader(this->program);
	glUniform1f(location, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

										   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("tanks.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES;
	float w = 0.04f;
	float x = w;
	float y = w;

	spriteWidth = 2 * x;
	spriteHeight = 2 * y;

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


bool Player::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

void Player::Destroy() {
	if (texture != NULL)
	{
		xpos = 90;
		ypos = 90;
		program = NULL;
		VBO = NULL;
		VAO = NULL;
		EBO = NULL;
		texture = NULL;
		spriteWidth = 0;
		spriteHeight = 0;
	}
}
