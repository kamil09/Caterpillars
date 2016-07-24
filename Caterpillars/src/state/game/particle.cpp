#include "particle.hpp"
#include "../../inputActions.hpp"

GLfloat ParticleEffect::particleEffectVertex[12] = {-0.5f,-0.5f,0.0f,0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f,0.5f,0.5f,0.0f};

ParticleEffect::ParticleEffect(glm::vec3 pos, float maxTime, float minSize, float maxSize, int maxParticles, float life, float coef){

   this->effectPos = pos;
   this->effectMaxTime=maxTime;
   this->effectTimeLeft=maxTime;
   this->effectMinSize=minSize;
   this->effectMaxSize=maxSize;
   this->effectMaxParticles=maxParticles;
   this->particlesCount=0;
   this->singleParticleLife = life;

   this->effectParticlePosAndSize = new GLfloat[4*this->effectMaxParticles];
   this->effectColorData = new GLfloat[2*this->effectMaxParticles];
   for(int i=0; i< effectMaxParticles*4;i++) effectParticlePosAndSize[i]=0;
   for(int i=0; i< effectMaxParticles*2;i++) effectColorData[i]=0;

   puts("created particle effect");

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

   srand( time( NULL ) );
   this->createFirstParticles(coef);
   this->run();

   //glGenVertexArrays(1, &this->VAO);
   //glBindVertexArray(this->VAO);

   this->shader = new Shader("../src/shaders/particle.vs","../src/shaders/particle.frag");

   this->bindBuffers();
}

void ParticleEffect::bindBuffers(){
   this->VerBuffer=0;
   this->ParPosBuffer=0;
   this->ParColBuffer=0;

   glGenVertexArrays(1, &this->VerBuffer);
   glGenBuffers(1, &this->ParPosBuffer);
   glGenBuffers(1, &this->ParColBuffer);


   glBindVertexArray(this->VerBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(particleEffectVertex), particleEffectVertex, GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParPosBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParColBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 2 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

   //glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 4, this->effectParticlePosAndSize);

   //glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 2 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
   //glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 2, this->effectColorData);

   //1rst attribute buffer : vertices
   glEnableVertexAttribArray(0);
   glBindVertexArray(this->VerBuffer);
   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
   //2nd attribute buffer : positions of particles' centers
   glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, this->ParPosBuffer);
   glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
   //3rd attribute buffer : particles' colors
   glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, this->ParColBuffer);
   glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);

   //glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
   // //1rst attribute buffer : vertices
   // glEnableVertexAttribArray(0);
   // glBindBuffer(GL_ARRAY_BUFFER, this->VerBuffer);
   // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
   // // //2nd attribute buffer : positions of particles' centers
   // glEnableVertexAttribArray(1);
   // glBindBuffer(GL_ARRAY_BUFFER, this->ParPosBuffer);
   // glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)0);
   // // //3rd attribute buffer : particles' colors
   // glEnableVertexAttribArray(2);
   // glBindBuffer(GL_ARRAY_BUFFER, this->ParColBuffer);
   // glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void*)0);

}

void ParticleEffect::createFirstParticles(float coef){
   for(int i=0 ; i < (int)(this->effectMaxParticles*coef);i++) this->createSimpleParticle();
}

void ParticleEffect::createSimpleParticle(){
   //TODO powinno być losowanie w kuli, a nie w kwadracie
   float posX=(float)(rand()%( (int)this->effectMinSize*10 )) / 10 -this->effectMinSize;
   float posY=(float)(rand()%( (int)this->effectMinSize*10 )) / 10 -this->effectMinSize;
   float posZ=(float)(rand()%( (int)this->effectMinSize*10 )) / 10 -this->effectMinSize;

   Particle p;
   p.pos=glm::vec3(posX,posY,posZ);
   p.life=this->singleParticleLife*((float)(rand()%20+80)/120);
   int tmp = rand()%100;
   if(tmp < (this->effectMaxTime-this->effectTimeLeft)*(100/this->effectMaxTime) ) p.type=0;
   else p.type=1;

   float maxSpeed=(float)(this->effectMaxSize-this->effectMinSize)/p.life;
   //TODO Sensowniejsze losowanie
   float speedX=(float)(rand()%5-2)*maxSpeed/3 ;
   float speedY=(float)(rand()%5-2)*maxSpeed/3 ;
   float speedZ=(float)(rand()%5-2)*maxSpeed/3 ;
   p.speed=glm::vec3(speedX,speedY,speedZ);

   //TODO pomysleć nad rozmiarem
   p.size=(float)(rand()%10+10)/30+0.2;

   this->particlesContainer.push_back(p);
}

//Calculate particles
void ParticleEffect::run(){
   this->effectTimeLeft-=inputActions::getInstance().deltaTime;

      //TODO CREATE NEW PARTICLES, but not to much :)

   //main loop
   this->particlesCount=0;
   for(unsigned int i=0;i<this->particlesContainer.size();i++){
      Particle& p = this->particlesContainer[i];
      if(p.life>0){
         p.life-=inputActions::getInstance().deltaTime;
         //TODO ZMIANA PRĘDKOŚCI I ROZMIARU

         p.pos+=p.speed*inputActions::getInstance().deltaTime; //pozycja
         this->effectParticlePosAndSize[4*particlesCount]=p.pos.x + this->effectPos.x;
         this->effectParticlePosAndSize[4*particlesCount+1]=p.pos.y + this->effectPos.y;
         this->effectParticlePosAndSize[4*particlesCount+2]=p.pos.z + this->effectPos.z;
         this->effectParticlePosAndSize[4*particlesCount+3]=p.size;

         //printf("POZYCJA: %f %f %f\n",this->effectParticlePosAndSize[4*particlesCount],this->effectParticlePosAndSize[4*particlesCount+1],this->effectParticlePosAndSize[4*particlesCount+2]);

         //TODO POPRAWIĆ LOSOWANIE KOLORU, DODAĆ 2 TYP
         float rad = sqrt( pow(p.pos.x,2)+pow(p.pos.y,2)+pow(p.pos.z,2) );
         this->effectColorData[2*particlesCount]= 0.5-(rad/this->effectMaxSize/2);
         this->effectColorData[2*particlesCount+1]= 0.5-(rad/this->effectMaxSize/2);

         this->particlesCount++;
      }
   }
   printf("%d\n",particlesCount);
}
//draw particles
void ParticleEffect::draw(glm::mat4 projection, glm::mat4 modelView){
   this->shader->useShaderProgram(0);
   glBindVertexArray(this->VerBuffer);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParPosBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 4 * sizeof(GLfloat), this->effectParticlePosAndSize, GL_DYNAMIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 4, this->effectParticlePosAndSize);

   glBindBuffer(GL_ARRAY_BUFFER, this->ParColBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->effectMaxParticles * 2 * sizeof(GLfloat), this->effectColorData, GL_DYNAMIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, this->particlesCount * sizeof(GLfloat) * 2, this->effectColorData);

   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
   glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));

   glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
   glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
   glVertexAttribDivisor(2, 1); // color : one per quad -> 1
   // This is equivalent to :
   // for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
   // but faster.
   glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particlesCount);

//   glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);

}
