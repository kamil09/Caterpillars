#include "errorGL.hpp"

void errorCheck(const char* napis){
    int i=0;
    GLenum err;
    // std::cout << "ERROR::Początek: " << napis << std::endl;
    while((err = glGetError())!=GL_NO_ERROR) {
        i++;
        std::cerr << "opengl error: " << err << std::endl;
    }
    if(i!=0){
        std::cout << "ERROR::Koniec: " << napis << " ERROR::COUNT: " << i << std::endl;
    }
}
