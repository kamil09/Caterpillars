#ifndef PAR
#define PAR

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "../../shaders/shader.hpp"
#include "../../loadData/lodepng.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <math.h>

struct Particle{
	glm::vec3 pos, speed;
	glm::vec4 color;
	float size;
	float life;
	int type;
};

class ParticleEffect{

public:
   static GLfloat particleEffectVertex[12];
   GLuint VerBuffer;
   GLuint ParPosBuffer;
   GLuint ParColBuffer;
	Shader *shader;
	GLuint texture;
	GLuint VAO;

   ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles,float life,float coef);
   void run();
   void draw(glm::mat4 projection, glm::mat4 modelView);
	void createFirstParticles(float coef);
	void createSimpleParticle();
	void bindBuffers();

   std::vector<Particle> particlesContainer;
   //Pozycja i mnożnik rozmiaru
   GLfloat *effectParticlePosAndSize;
   //współrzędne koloru tekstury
   GLfloat *effectColorData;

   glm::vec3 effectPos;
   float effectMaxTime;
	float effectTimeLeft;
   float effectMinSize;
   float effectMaxSize;
   int particlesCount;
   int effectMaxParticles;
   float singleParticleLife;
};

#endif
