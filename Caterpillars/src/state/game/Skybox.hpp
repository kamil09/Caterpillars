//
// Created by lewin on 22.07.16.
//

#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <string.h>
#include "../../object.hpp"
#include "map/map.hpp"

class Skybox : public Object {
public:
    Skybox();
    void draw(glm::mat4 projection,glm::mat4 modelView);
    GLuint textureCube;
};


#endif //CATERPILLARS_SKYBOX_HPP
