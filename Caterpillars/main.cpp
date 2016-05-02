#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "src/settings.hpp"
#include "src/menu.hpp"

using namespace std;

static void error_callback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}
static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
//move
	//if(key == W && action == GLFW_PRESS)
	//if(key == W && action == GLFW_RELEASE)
	//if(key == A && action == GLFW_PRESS)
	//if(key == A && action == GLFW_RELEASE)
	//if(key == S && action == GLFW_PRESS)
	//if(key == S && action == GLFW_RELEASE)
	//if(key == D && action == GLFW_PRESS)
	//if(key == D && action == GLFW_RELEASE)
//jump (jeżeli połączony z jakimś z powyższych to skaczemy w kierunku)
	//if(key == SPACE && action == GLFW_PRESS)
	//if(key == SPACE && action == GLFW_RELEASE)
//show/close inventory
	//if(key == I && action == GLFW_PRESS)
	//if(key == I && action == GLFW_RELEASE)

//close / pause
	//if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

}

enum gameCase {START,OPTIONS,INFO,GAME,PAUSE,GAME_END,EXIT};
gameCase gameCase;

int main(void){
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) return 1;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Caterpillars",glfwGetPrimaryMonitor(), NULL);
	// GLFWwindow* window = glfwCreateWindow(Setting::getInstance()->getWidth(), mode->height, "Caterpillars",glfwGetPrimaryMonitor(), NULL);

	std::cout << Setting::getInstance().getHeight() << std::endl;
	std::cout << Setting::getInstance().getWidth() << std::endl;

	if(!window) {
		std::cerr << "terminated" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	GLenum error_code = glewInit();
	if(error_code != GLEW_OK) {
		std::cerr << "Glew init error: " << glewGetErrorString(error_code) << std::endl;
	}

	glfwSetKeyCallback(window, key_callback);
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	glfwSetCursor(window, cursor);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Informacje o sprzęcie:" << std::endl << vendor << std::endl << renderer << std::endl << version << std::endl << shading << std::endl;

	while (!glfwWindowShouldClose(window)) {
		glfwSetTime(0);
		switch (gameCase) {
		case START:
			//gameCase=mainMenuView();
			break;
		case OPTIONS:
			//gameCase=optionsView();
			break;
		case INFO:
			//gameCase=infoView();
			break;
		case GAME:
			//gameCase=gameView();
			break;
		case PAUSE:
			//gameCase=pauseView();
			break;
		case GAME_END:
			//gameCase=gameEndView();
			break;
		case EXIT:
			//gameCase=exitView();
			break;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwDestroyCursor(cursor);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}
