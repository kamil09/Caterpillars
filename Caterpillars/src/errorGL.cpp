#include "errorGL.hpp"

void errorCheck(const char* napis){
    int i=0;
    GLenum err;
    bool glewInit = false;
    while((err = glGetError())!=GL_NO_ERROR) {
        i++;
        if (err == 1280){
            glewInit = true;
        }
        std::cerr << "opengl error: " << err << std::endl;
    }
    if(i!=0){
        std::cout << "ERROR::Koniec: " << napis << " ERROR::COUNT: " << i << std::endl;
        if(!glewInit){
        }
    }
}
