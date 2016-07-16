#include "bigWall.hpp"
#include "../../../inputActions.hpp"

//Deprecated
Wall::Wall(int x, int width, int z, int depth, int min, int max){
   this->shader = new Shader("../src/shaders/map/wallShader.vs","../src/shaders/map/wallShader.frag");
   this->vertices.resize(8*3);
   this->indices.resize(10);
   this->vertices = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, (float)max,  0.0f, 0.0f, 1.0f,
      (float)width, 0.0f, 0.0f, 1.0f, 0.0f,
      (float)width, (float)max, 0.0f, 1.0f, 1.0f,
      (float)width, 0.0f, float(depth), 0.0f, 0.0f,
      (float)width, (float)max, float(depth), 0.0f, 1.0f,
      0.0f, 0.0f, float(depth), 1.0f, 0.0f,
      0.0f, (float)max, float(depth), 1.0f, 1.0f
   };
   this->indices = {
      0,1,2,3,4,5,6,7,0,1
   };
   this->bindBuffers(5,5,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/wall.png");
}

Wall::Wall(char *filename, int x, int width, int z, int depth, int min, int max){
   this->shader = new Shader("../src/shaders/catterShader.vs","../src/shaders/catterShader.frag");
   this->size.x = width;
   this->size.y = max; //Tu nie wiem jaka wartosc
   this->size.z = depth;
   this->scl.x=width/2;
   this->scl.y=max/2;
   this->scl.z=depth/2;
   this->pos.x=width/2;
   this->pos.y=max/2;
   this->pos.z=depth/2;
   this->recalculateMatrix();
   loadObj::load(filename,&this->vertices, &this->indices);
   this->bindBuffers(5,8,GL_STATIC_DRAW);
   this->bindTexture2D("../src/img/wall.png");
   this->bindLightMap2D("../src/img/light/example.png");
   this->bindShadwMap2D("../src/img/shadow/example.png");
}

Wall::~Wall(){}

void Wall::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->shader->useShaderProgram(0);
   this->uniformTextures();

   printf("%f %f %f %f\n",sun.x,sun.y,sun.z,sun.a);
   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint M = glGetUniformLocation(this->shader->shaderProgram[0], "M");
   GLint L = glGetUniformLocation(this->shader->shaderProgram[0], "L");
   GLint SUN = glGetUniformLocation(this->shader->shaderProgram[0], "SUN");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(M, 1, GL_FALSE, glm::value_ptr(this->posM*this->sclM));
   glUniformMatrix4fv(L, 1, GL_FALSE, glm::value_ptr(lights));
   glUniform4fv(SUN, 1, glm::value_ptr(sun));
   
   glBindVertexArray(this->currentVAO());
   glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
   glBindVertexArray(1);

   //Deprecated
   /*
   glBindVertexArray(this->currentVAO());
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);
   glBindVertexArray(1);
   */
}
