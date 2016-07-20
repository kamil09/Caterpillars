#include "particle.hpp"
#include "../../inputActions.hpp"


ParticleEffect::ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles){
   this->effectPos = pos;
   this->effectMaxTime=maxTime;
   this->effectMinSize=minSize;
   this->effectMaxSize=maxSize;
   this->effectMaxParticles=maxParticles;
   this->particlesContainer.resize(this->effectMaxParticles);
   puts("created particle effect");
}
//Calculate particles
void ParticleEffect::run(){
   this->effectMaxTime-=inputActions::getInstance().deltaTime;


   
}
//draw particles
void ParticleEffect::draw(){

}
