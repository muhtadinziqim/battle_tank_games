#include "Enemy.h"


Enemy::Enemy()
{
	frame_dur = 0, frame_width = 0, degree = 0, xpos2 = 0.7, ypos2 = 0.7, crateWidth = 0, crateHeight = 0, oldxpos = ypos2, oldypos = ypos2;
	nyawa = 3;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	BuildSprite();
}

void Enemy::Spawn(float posx, float posy)
{
	xpos2 = posx, ypos2 = posy, crateWidth = 0, crateHeight = 0, oldxpos = ypos2, oldypos = ypos2;
}

void Enemy::Update(float deltaTime)
{
	//UpdateSprite(deltaTime);
	MoveSprite(deltaTime);
}

void Enemy::Render()
{
	//DrawSprite();
}


void Enemy::MoveSprite(float deltaTime)
{

	mat4 transform;
	transform = translate(transform, vec3(xpos2, ypos2, 0.0f));

	transform = glm::rotate(transform, glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint location = glGetUniformLocation(this->program2, "transform");
	UseShader(this->program2);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));

}

void Enemy::DrawTank() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_tank);
	glUniform1i(glGetUniformLocation(this->program2, "tank"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(this->program2, "agentMap_"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->program2, "fsmMap"), 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->program2, "worldMap"), 3);
	
	// Activate shader
	UseShader(this->program2);
	//glUniform1i(location2, 1);

	// Draw crate
	glBindVertexArray(VAO2);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

void Enemy::BuildSprite()
{
	this->program2 = BuildShader("tank.vert", "tank.frag");

	int width, height;

	// Load and create a texture 
	glGenTextures(1, &texture_tank);
	glBindTexture(GL_TEXTURE_2D, texture_tank); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture
	unsigned char* image = SOIL_load_image("tanks.png", &width, &height, 0, SOIL_LOAD_RGBA);
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
							
	// Set up vertex data (and buffer(s)) and attribute pointers
	float w = 0.04f;
	float x = w;
	float y = w;
	crateWidth = 2 * x;
	crateHeight = 2 * y;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
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


bool Enemy::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

void Enemy::Nabrak(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {
	if (IsCollided(x1, y1, width1, height1, x2, y2, width2, height2)) {
		xpos2 = oldxpos;
		ypos2 = oldypos;
	}
}

void Enemy::Destroy() {
	if (texture2 != NULL)
	{
		program2 = NULL;
		VBO2 = NULL;
		VAO2 = NULL;
		EBO2 = NULL;
		texture2 = NULL;
		crateWidth = 0;
		crateHeight = 0;
		xpos2 = 100000;
	}
}

float Enemy::HitungJarak(float x1, float y1, float x2, float y2) {
	float jarak, a, b, c;
	a = x1 - x2;
	b = y1 - y2;
	
	c = (a*a) + (b*b);
	jarak = sqrt(c);
	return jarak;
}

void Enemy::Kejar(float x1, float y1, float x2, float y2, float deltaTime) {
//	float jkanan = 99, jkiri = 99, jatas = 99, jbawah = 99;
//	if (x1 > x2) {
//		jkiri = x1 - x2;
//	}
//	if (x1 < x2) {
//		jkanan = 0;
//	}
	oldxpos = xpos2;
	oldypos = ypos2;


	float jarakx, jaraky, jx, jy;
	jarakx = x1 - x2;
	jaraky = y1 - y2;
	jx = pow(jarakx, 2);
	jy = pow(jaraky, 2);

	if (jx < jy) {
		if (jarakx > 0) {
			degree = 90;
			xpos2 -= deltaTime * SPEED;
			if(jarakx <= 0.01 && jarakx >= -0.01){
				if (jaraky > 0) {
					degree = 180;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
				else {
					degree = 0;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
			}
		}
		else {
			degree = 270;
			xpos2 += deltaTime * SPEED;
			if (jarakx <= 0.01 && jarakx >= -0.01) {
				if (jaraky > 0) {
					degree = 180;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
				else {
					degree = 0;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
			}
		}
	}
	else {
		if (jaraky > 0) {
			degree = 180;
			ypos2 -= deltaTime * SPEED;
			if (jaraky <= 0.01 && jaraky >= -0.01) {
				if (jarakx > 0) {
					degree = 90;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
				else {
					degree = 270;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
			}
		}
		else {
			degree = 0;
			ypos2 += deltaTime * SPEED;
			if (jaraky <= 0.01 && jaraky >= -0.01) {
				if (jarakx > 0) {
					degree = 90;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
				else {
					degree = 270;
					xpos2 = oldxpos;
					ypos2 = oldypos;
				}
			}
		}
	}
	MoveSprite(deltaTime);
}

void Enemy::Patroli(float deltaTime, int i) {
	oldxpos = xpos2;
	oldypos = ypos2;
	static int const index = i;

	floop++;
	static int a[7];
	if (floop == 100){
		a[i] = rand() % 4;
		floop = 0;
	}
	switch (a[i])
	{
	case 0 :
		degree = 90;
		xpos2 -= deltaTime * SPEED;
		break;
	case 1 :
		degree = 270;
		xpos2 += deltaTime * SPEED;
		break;
	case 2 :
		degree = 180;
		ypos2 -= deltaTime * SPEED;
		break;
	case 3 :
		degree = 0;
		ypos2 += deltaTime * SPEED;
		break;
	default:
		break;
	}
	MoveSprite(deltaTime);
}