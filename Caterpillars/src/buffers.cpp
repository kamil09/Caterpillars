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
    // std::cout << "Usuwam buffery" << std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    this->VAO=0;
    this->VAO=0;
    this->EBO=0;
}
