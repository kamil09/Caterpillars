#include "particle.hpp"
#include "../../inputActions.hpp"


ParticleEffect::ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles){
   GLfloat tmp[12] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f,};
   (*this->particleEffectVertex)=(*tmp);

   this->effectPos = pos;
   this->effectMaxTime=maxTime;
   this->effectMinSize=minSize;
   this->effectMaxSize=maxSize;
   this->effectMaxParticles=maxParticles;
   this->particlesContainer.resize(this->effectMaxParticles);
   this->particlesCount=0;
   puts("created particle effect");

   glGenBuffers(1, &this->VerBuffer);
   glGenBuffers(1, &this->ParPosBuffer);
   glGenBuffers(1, &this->ParColBuffer);

   glBindBuffer(GL_ARRAY_BUFFER, this->VerBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(this->particleEffectVertex), this->particleEffectVertex, GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParPosBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 4, this->effectParticlePosAndSize);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParColBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 2 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 2, this->effectColorData);

   //1rst attribute buffer : vertices
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, VerBuffer);
   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
   //2nd attribute buffer : positions of particles' centers
   glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, ParPosBuffer);
   glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)0);
   //3rd attribute buffer : particles' colors
   glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, ParColBuffer);
   glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void*)0);
}
//Calculate particles
void ParticleEffect::run(){
   this->effectMaxTime-=inputActions::getInstance().deltaTime;



}
//draw particles
void ParticleEffect::draw(){
   glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
   glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
   glVertexAttribDivisor(2, 1); // color : one per quad -> 1

   glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particlesCount);
}
