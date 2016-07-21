#include "particle.hpp"
#include "../../inputActions.hpp"

ParticleEffect::ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles, float life){
   GLfloat tmp[12] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f,};
   (*this->particleEffectVertex)=(*tmp);
   this->effectPos = pos;
   this->effectMaxTime=maxTime;
   this->effectMinSize=minSize;
   this->effectMaxSize=maxSize;
   this->effectMaxParticles=maxParticles;
   this->particlesContainer.resize(this->effectMaxParticles);
   this->particlesCount=0;
   this->singleParticleLife = life;

   puts("created particle effect");
   this->shader = new Shader("../src/shaders/particle.vs","../src/shaders/particle.frag");

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
   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
   //2nd attribute buffer : positions of particles' centers
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
   //3rd attribute buffer : particles' colors
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   errorCheck("Po bindowaniu");

   glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   std::vector<unsigned char> image;
	unsigned width,height;
	unsigned error = lodepng::decode(image,width,height,"../src/img/fire.png");
	if(error != 0) std::cout << "ERROR:: " << error << std::endl;
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, 0);
   errorCheck("Po loadTexture");

}


//Calculate particles
void ParticleEffect::run(){
   this->effectMaxTime-=inputActions::getInstance().deltaTime;
   if(this->effectMaxTime >= this->singleParticleLife){
      //TODO CREATE NEW PARTICLES, but not to much :)
   }

   //main loop
   this->particlesCount=0;
   for(int i=0;i<this->effectMaxParticles;i++){
      Particle& p = this->particlesContainer[i];
      if(p.life>0){
         p.life-=inputActions::getInstance().deltaTime;

         //TODO CALCULATE EVERYTHING

         this->particlesCount++;
      }
   }
}
//draw particles
void ParticleEffect::draw(){
   //this->shader->useShaderProgram(0);

   //glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
   //glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
   //glVertexAttribDivisor(2, 1); // color : one per quad -> 1

   //glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
   //glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, this->texture);

   // This is equivalent to :
   // for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
   // but faster.
   //glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particlesCount);
}
