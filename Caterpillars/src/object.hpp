#ifndef objectCl
#define objectCl

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "shaders/shader.hpp"
// #include "SOIL/SOIL.h"

// #include <Magick++.h>
#include "lodepng.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "buffers.hpp"
#include "errorGL.hpp"


class OurTexture {
public:
    const char* texturePath;
    std::vector<unsigned char> image;
    int textureWidth;
    int textureHeight;
    int textureDepth;
};


class Object{
private:
   float speedX;
   float speedY;
   float speedZ;
   GLfloat posX;
   GLfloat posY;
   GLfloat posZ;
   bool canKick;     //Czy można zadziałać na dany obiekt. Jezeli false to obiekt znajduje się w powietrzu i nie da rady w niego ingerować
   double kickTime;  //Czas od rozpoczęcia rzutu

public:
   glm::mat4 modM;   //Maciez modelu
   glm::mat4 posM;   //Maciez przesuniecia
   glm::mat4 rotM;   //Maciez obrotu
   glm::mat4 sclM;   //Maciez skalowania

    int verticesCount;
    int indicesCount;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int buffersCount;
    std::vector<Buffers*> buffers;
    Shader *shader;
    Object();
    ~Object();

   void draw();
   float windMul; // od 0 do 1. Jak wiatr wpływa na dany obiekt. Dla mapy np 0, dla pocisku 1 a dla robala delikatnie
   void kick(float x,float y, float z);
   void recalculatePhysics();
   GLfloat getPosX();
   void setPosX(GLfloat newValue);
   GLfloat getPosY();
   void setPosY(GLfloat newValue);
   GLfloat getPosZ();
   void setPosZ(GLfloat newValue);

   //Funkcje i zmienne do textur 2D
   void bindTexture2D(const GLchar *texturePath);
   void loadTexture2D(const GLchar *texturePath);
   int textureWidth;
   int textureHeight;
   GLuint texture2D;

   void bindTexture3D();
   void loadTexture3D();


   // GLuint texture3D;
   // std::vector<const char*> listaTekstur;
   // unsigned char* image;
   std::vector<OurTexture*> listaTekstur;
   int teksturCount;
   void newBinding();
   void initBinding(bool newBuffer);
   int currentBinding;
   void endBinding();
   GLuint currentVAO();
};

#endif
