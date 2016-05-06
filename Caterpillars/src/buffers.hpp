#ifndef BUFFERS
#define BUFFERS

#include <GL/glew.h>
#include <iostream>

class Buffers {
public:
    Buffers();
    ~Buffers();
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    void usuwanie();
};

#endif
