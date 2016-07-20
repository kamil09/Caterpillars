#ifndef PAR
#define PAR

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

struct Particle{
	glm::vec3 pos, speed;
	glm::vec4 color; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if < 0 : dead and unused.
};

class ParticleEffect{

public:
   ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles);
   void run();
   void draw();

   std::vector<Particle> particlesContainer;

   glm::vec3 effectPos;
   float effectMaxTime;
   float effectMinSize;
   float effectMaxSize;
   int effectMaxParticles;
};

#endif
