#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

// Texture samplers
uniform sampler2D ourTexture;

void main()
{
    gl_FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);
}