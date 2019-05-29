#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <iostream>


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <unordered_map>
#include "libxl.h"

using namespace libxl;
using namespace std;
using namespace glm;

enum class Status { MAIN_MENU, LEVEL, LVL1_MAP1, LVL2_MAP1, LVL3_MAP1, LVL1_MAP2, LVL2_MAP2, LVL3_MAP2, LVL1_MAP3, LVL2_MAP3, LVL3_MAP3,
						NPC1, NPC5, NPC10, NPC15,
						MAP1, MAP2, MAP3
					};
enum class Budal {};
enum class State { RUNNING, EXIT };
enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS};

namespace Engine {
	class Game
	{
	public:
		Game();
		~Game();
		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		// Input Handling
		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);
		void SetMouseCoords(float x, float y);
		/// Returns true if the key is held down
		bool IsKeyDown(unsigned int keyID);
		/// Returns true if the key was just pressed
		bool IsKeyPressed(unsigned int keyID);
		bool IsKeyUp(unsigned int keyID);
		//getters
		vec2 GetMouseCoords() const { return _mouseCoords; }

		SDL_Window* window;
		unsigned int fps = 0;

	protected:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void UseShader(GLuint program);
		unsigned int screenWidth, screenHeight; 
		void InputMapping(string mappingName, unsigned int keyId);
	
	private:
		unsigned int lastFrame = 0, last = 0, _fps = 0;
		float targetFrameTime = 0, timeScale;
		State state;
		float GetDeltaTime();
		void GetFPS();
		void PollInput();
		void Err(string errorString);
		void LimitFPS();
		void CheckShaderErrors(GLuint shader, string type);
		
		// Input Handling
		/// Returns true if the key is held down
		unordered_map<unsigned int, string> _mapNames;
		bool WasKeyDown(unsigned int keyID);
		unordered_map<unsigned int, bool> _keyMap;
		unordered_map<unsigned int, bool> _previousKeyMap;
		vec2 _mouseCoords;
	};
}
#endif

