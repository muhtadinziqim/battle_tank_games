#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

// Texture samplers
uniform sampler2D tank;
uniform sampler2D agentMap_;
uniform sampler2D fsmMap;
uniform sampler2D worldMap;

uniform float state = 0;
uniform float jarak = 0;
uniform float nyawa = 0.1;

float indexJarak()
{
	float ij = 0;
	if (jarak > 0.7){
		ij = 0.9;
	}else{
		ij = 0.1;
	}
	return ij;
}

float indexNyawa()
{
	float iN = 0;
	if (nyawa > 0){
		iN = 0.1;
	}else{
		iN = 0.9;
	}
	return iN;
}

float hitung(float a)
{
	float h = a;
	if (a >= 1){
		h = a - 0.01;
	}
	if(a <= 0 ){
		h = a + 0.01;
	}
	return h;
}


void main()
{
	float soilLabel = texture(worldMap, vec2(indexJarak(), indexNyawa())).g;
	vec3 agentLookUp = texture(agentMap_, vec2(hitung(soilLabel), hitung(state))).rgb;
	vec2 agentPos = agentLookUp.gb;
	float agentState = agentLookUp.r;
	vec3 fsmOut = texture(fsmMap, vec2(hitung(soilLabel), hitung(agentState))).rgb;
    gl_FragColor = texture(tank, TexCoord) * vec4(1.0, 0.0, 0.0, 1);
}