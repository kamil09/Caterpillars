#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

using namespace std;

static void error_callback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window,int key, int scancode, int action, int mods ){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


int main(void){
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) {
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	GLFWwindow* window = glfwCreateWindow(640, 480, "Caterpillars", NULL, NULL);
	if(!window) {
		std::cerr << "terminated" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	GLenum error_code = glewInit();
	if(error_code != GLEW_OK) {
		std::cerr << "Glew init error: " << glewGetErrorString(error_code) << std::endl;
	}

	glfwSetKeyCallback(window, key_callback);

	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Informacje o sprzęcie:" << std::endl << vendor << std::endl << renderer << std::endl << version << std::endl << shading << std::endl;


	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
