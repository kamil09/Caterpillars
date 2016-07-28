#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "src/settings.hpp"
#include "src/state/game/map/map.hpp"
#include "src/inputActions.hpp"
#include "src/state/state.hpp"
#include "src/state/game/game.hpp"
#include "src/state/menu/menu.hpp"
#include "src/state/menu/mainMenu/mainMenu.hpp"
#include <unistd.h>
#include "src/errorGL.hpp"
#include "src/info.hpp"
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <thread>
#include <mutex>

using namespace std;
using namespace glm;

//ERROR
static void error_callback(int error, const char* description);
//INICJALIZACJA
void initOpenGLProgram(GLFWwindow* window,GLFWcursor* cursor);
//MAIN
int main(void){
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) return 1;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//We don't want resizable window

	GLfloat deltaTime = 0.0f;		// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame

	GLFWwindow* window;
	if ( Setting::getInstance().getFullWindow() ){
		std::cout << "full screen" << std::endl;
		if (Setting::getInstance().getFullResolution() ){
			std::cout << "full resolution" << std::endl;
			window = glfwCreateWindow(mode->width, mode->height, "Caterpillars",glfwGetPrimaryMonitor(), NULL);
		}
		else{
			std::cout << "no full resolution" << std::endl;
			window = glfwCreateWindow(Setting::getInstance().getWidth(), Setting::getInstance().getHeight(), "Caterpillars",glfwGetPrimaryMonitor(), NULL);
		}
	}
	else{
		std::cout << "no full screen" << std::endl;
		if (Setting::getInstance().getFullResolution() ){
			std::cout << "full resolution" << std::endl;
			window = glfwCreateWindow(mode->width, mode->height, "Caterpillars",NULL, NULL);
		}
		else{
			std::cout << "no full resolution" << std::endl;
			window = glfwCreateWindow(Setting::getInstance().getWidth(), Setting::getInstance().getHeight(), "Caterpillars",NULL, NULL);
		}
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::cout << Setting::getInstance().getHeight() << std::endl;
	std::cout << Setting::getInstance().getWidth() << std::endl;
	if(!window) {
		std::cerr << "terminated" << std::endl;
		glfwTerminate();
		return 1;
	}

	GLFWcursor* cursor=0;
	initOpenGLProgram(window,cursor);

	int width,height;
	glfwGetWindowSize(window,&width,&height);
	std::cout << "Current Window width: " << width << std::endl;
	std::cout << "Current Window height: " << height << std::endl;

	glViewport(0,0,width,height);

	Info *info = new Info();
	errorCheck("inicjalizacja");

	//Dzwiek
	inputActions::getInstance().createSoundEngine();
	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		inputActions::getInstance().deltaTime = deltaTime;
		glClearColor(0.294f, 0.176f, 0.451f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(inputActions::getInstance().currentState->customPollEvents == false){
			glfwPollEvents();
		}

		inputActions::getInstance().currentState->run();
		errorCheck("Rysowanie");
		//Liczenie deltatime
		//INFORMACJE
		info->draw();
		glfwSwapBuffers(window);
		//Czyścimy niektóre inputy przed kolejną klatką.
		inputActions::getInstance().clear();
	}
	glfwDestroyCursor(cursor);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

void initOpenGLProgram(GLFWwindow* window,GLFWcursor* cursor){
	glewExperimental = GL_TRUE;
	glClearColor(0, 0, 0, 1);

	errorCheck("Przed glewInit");
	GLenum error_code = glewInit();
	if(error_code != GLEW_OK) std::cerr << "Glew init error: " << glewGetErrorString(error_code) << std::endl;
	errorCheck("Po glewInit");

	//depth test
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cursor = inputActions::getInstance().setCallbacks(window,cursor);
	inputActions::getInstance().changeState('m',window,cursor);

	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Informacje o sprzęcie:" << std::endl << vendor << std::endl << renderer << std::endl << version << std::endl << shading << std::endl;
}

static void error_callback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}
