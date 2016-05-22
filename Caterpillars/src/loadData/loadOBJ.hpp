#ifndef LOADOBJ_H
#define LOADOBJ_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

   namespace loadObj{
      bool load(char * path,std::vector<GLfloat> *vertices, std::vector<GLuint> *indices);

   }

#endif
