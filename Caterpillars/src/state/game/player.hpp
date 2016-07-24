//
// Created by lewin on 16.07.16.
//

#ifndef PLAYER
#define PLAYER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <string.h>
#include <string>
#include "../../settings.hpp"

class Caterpillar;

class Player{
public:
    Player(int id);
    int id;
    std::string nazwa;
    glm::vec3 kolor;
    std::vector<Caterpillar*> caterpillars;
    std::vector<Caterpillar*> aliveCaterpillars;
    int activeCaterpillar = -1;
    Caterpillar *changeCaterpillar();
};

#endif //CATERPILLARS_PLAYER_HPP
