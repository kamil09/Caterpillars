#include "buffers.hpp"

Buffers::Buffers(){
    this->VAO = 0;
    this->EBO = 0;
    this->VBO = 0;
}

Buffers::~Buffers(){
    this->usuwanie();
}


void Buffers::usuwanie(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    this->VAO=0;
    this->VBO=0;
    this->EBO=0;
}
