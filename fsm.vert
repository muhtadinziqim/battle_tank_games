#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform float n = 1.0f;
uniform int frameIndex = 0;
uniform mat4 transform;
uniform int flip = 0;
uniform mat4 rotation;

out vec3 ourColor;
out vec2 TexCoord;
void main()
{
    gl_Position = transform * vec4(position, 1.0f);
    ourColor = color;
    // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis.
	
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

	//if(flip == 1)
	//	TexCoord = vec2(1.0f - (n * (texCoord.x + frameIndex)), 1.0f - texCoord.y);
    //else
	//	TexCoord = vec2((n * (texCoord.x + frameIndex)), 1.0f - texCoord.y);
}



