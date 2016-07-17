#ifndef objectCl
#define objectCl

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "shaders/shader.hpp"
#include <time.h>//Pawelek
#include <ctime>//Pawelek
#include "loadData/lodepng.h"
#include "loadData/loadOBJ.hpp"
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
};

class Object{
private:
   bool canKick;     //Czy można zadziałać na dany obiekt. Jezeli false to obiekt znajduje się w powietrzu i nie da rady w niego ingerować
   double kickTime;  //Czas od rozpoczęcia rzutu
   bool sec_time = false;//zmienna ktora okresla ze drugi raz juz weszla do funkcji grawitacji
   //chodzi o to zeby uwzglednialo wiatr tylko gdy jest w powietrzu
   int in_meter;
   float bet_time;
   float diff;
   float nextX, nextY, nextZ;
   float windX, windY, windZ;
   clock_t start, end;
public:
   glm::mat4 modM;   //Maciez modelu
   glm::mat4 posM;   //Maciez przesuniecia
   glm::mat4 rotM;   //Maciez obrotu
   glm::mat4 rotMY;  //Maciez obrotu tylko Y
   glm::mat4 sclM;   //Maciez skalowania

   glm::vec3 pos;
   glm::vec3 rot;
   glm::vec3 scl;
   glm::vec3 speed;
   glm::vec3 size;

   bool colission;

   int verticesCount;
   int indicesCount;
   int normalsCount;
   std::vector<GLfloat> vertices;
   std::vector<GLuint> indices;
   int buffersCount;
   std::vector<Buffers*> buffers;
   Shader *shader;
   int czyNormalMap;
   Object();
   ~Object();
   bool on_the_ground = false;//gdy bedzie skakal to sie ustawi na false

   float windMul; // od 0 do 1. Jak wiatr wpływa na dany obiekt. Dla mapy np 0, dla pocisku 1 a dla robala delikatnie
   void kick(float x,float y, float z);
   void recalculatePhysics();
   void recalculateGravity(); //Pawelek
   void diagonalThrow(glm::vec3 throw_speed); //Rzut ukosny
   //Funkcje i zmienne do textur 2D
   void bindTexture2D(const GLchar *texturePath);
   void bindShadwMap2D(const GLchar *texturePath);
   void bindLightMap2D(const GLchar *texturePath);
   void bindNormalMap2D(const GLchar *texturePath);

   virtual void loadTexture2D(const GLchar *texturePath);
   virtual void paramText2D();
   int textureWidth;
   int textureHeight;

   GLuint texture2D;
   GLuint shadowMap;
   GLuint lightMap;
   GLuint texture3D;
   GLuint normalMap;

   void bindTexture3D(int number, std::vector<std::string> texturePath);

   void loadTexture3D(int number);
   std::vector<OurTexture> listaTekstur;

   int teksturCount;
   void newBinding();
   void initBinding();
   int currentBinding;
   int currentShader = 0;
   void endBinding();
   GLuint currentVAO();
   GLint getUniform(const char *nazwa);
   void bindBuffers(int stride,int stride2,GLenum usage);
   void recalculateMatrix();
   void bufferData(GLenum usage);
   void vAttributePointer(int firstVertex, int stride, int stride2);
   void setPos(float x,float y,float z);

   void uniformTextures();
   virtual void inBinding(){};
   void draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun);
};

#endif
