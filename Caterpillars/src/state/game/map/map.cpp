#include "map.hpp"
#include "../../../inputActions.hpp"


Map::Map(){
   srand (time(NULL));
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
   this->fogHeight=0;
   this->shader = new Shader("../src/shaders/map/mapShader.vs","../src/shaders/map/mapShader.frag");
   this->rand();
   this->generateRandomMap();
   this->generateMeshNormals();
   this->genTriangleTab();
   this->bindBuffers(6,9,GL_DYNAMIC_DRAW);
    int numOfTex = 8;
//   GLchar *texturePath[numOfTex];
   std::vector<std::string> texturePath;
   texturePath.resize(8);
   texturePath[0] = "../src/img/map/map1.png";texturePath[1] = "../src/img/map/map2.png";
   texturePath[2] = "../src/img/map/map3.png";texturePath[3] = "../src/img/map/map4.png";
   texturePath[4] = "../src/img/map/map5.png";texturePath[5] = "../src/img/map/map6.png";
   texturePath[6] = "../src/img/map/map7.png";texturePath[7] = "../src/img/map/map8.png";
//   texturePath[0] = (char*)"../src/img/map/map1.png";texturePath[1] = (char*)"../src/img/map/map2.png";
//   texturePath[2] = (char*)"../src/img/map/map3.png";texturePath[3] = (char*)"../src/img/map/map4.png";
//   texturePath[4] = (char*)"../src/img/map/map5.png";texturePath[5] = (char*)"../src/img/map/map6.png";
//   texturePath[6] = (char*)"../src/img/map/map7.png";texturePath[7] = (char*)"../src/img/map/map8.png";
   this->bindTexture3D(numOfTex,texturePath);
   this->bindLightMap2D("../src/img/light/example.png");
   this->bindShadwMap2D("../src/img/shadow/example.png");
}
Map::~Map(){}

void Map::generateMeshNormals(){
   this->meshNormals = new glm::vec3**[2];

   this->meshNormals[0] = new glm::vec3*[vertX-1];
   this->meshNormals[1] = new glm::vec3*[vertX-1];
   for(int i=0;i<vertX-1;i++) {
      meshNormals[0][i] = new glm::vec3[vertY-1];
      meshNormals[1][i] = new glm::vec3[vertY-1];
   }
   calcMeshNormals(0,vertX-1,0,vertY-1);
}

void Map::calcMeshNormals(int xS, int xE, int yS, int yE){
   for(int i=xS;i<xE;i++)
      for(int j=yS;j<yE;j++){
         glm::vec3 vert1 = glm::vec3(i,mapVert[i][j],j);
         glm::vec3 vert2 = glm::vec3(i+1,mapVert[i+1][j],j);
         glm::vec3 vert3 = glm::vec3(i+1,mapVert[i+1][j+1],j+1);
         glm::vec3 vert4 = glm::vec3(i,mapVert[i][j+1],j+1);

         glm::vec3 vTriangleNorm0 = glm::cross(vert1-vert2, vert2-vert3);
         glm::vec3 vTriangleNorm1 = glm::cross(vert3-vert4, vert4-vert1);

         this->meshNormals[0][i][j] = glm::normalize(vTriangleNorm0);
         this->meshNormals[1][i][j] = glm::normalize(vTriangleNorm1);
      }
}

void makeHill(float **map){
   float hillHeight = rand() % (maxMapHeight*5/6-minMapHeight)+minMapHeight;
   int hillRadius = rand() % (maxHillRadius-minHillRadius)+minHillRadius;
   float hillGeometry = ((float)(rand() % 101)-50)/50;
   int hillX = rand() % vertX;
   int hillY = rand() % vertY;

   float mulX=1;
   float mulY=1;
   int k=0;
   while(hillGeometry>-0.7 && hillGeometry< 0.7 && k!=10){
      hillGeometry+=(hillGeometry*1/2);
      k++;
   }
   if(hillGeometry>-0.7 && hillGeometry< 0.7) hillGeometry=1;
   printf("hillH:%f hillRad:%d hillGeo:%f X:%d Y:%d \n",hillHeight,hillRadius,hillGeometry,hillX,hillY);
   hillGeometry=1;
   if(hillGeometry < 0){
      mulX/=fabs(hillGeometry);
      mulY*=fabs(hillGeometry);
   }
   if(hillGeometry > 0){
      mulX*=fabs(hillGeometry);
      mulY/=fabs(hillGeometry);
   }
   int radX=hillRadius*mulX;
   int radY=hillRadius*mulY;
   int left = hillX-(float)radX*1.3;
   int right = hillX+(float)radX*1.3;
   int top = hillY-(float)radY*1.3;
   int bottom = hillY+(float)radY*1.3;

   if(left<0) left=0;
   if(right>=vertX) right=vertX-1;
   if(top<0) top=0;
   if(bottom>=vertY) bottom=vertY-1;

   for(int i=left;i<=right;i++){
      for(int j=top;j<=bottom;j++){
         float rotDifX=fabs(hillX-i);
         float rotDifY=fabs(hillY-j);

         float odl=sqrt(pow(rotDifX,2)+pow(rotDifY,2));
         float maxOdl=sqrt(pow(radX,2)+pow(radY,2));
         float odlNor=(odl/maxOdl);
         if(odlNor < 0  )puts("k");

         float toADD = cos(odlNor*3.14/2)*hillHeight;
         if(toADD<=0) toADD=0;

         //printf("%f %f %d %d %f\n",highPerOneX, highPerOneY, rotDifX, rotDifY, toADD);
         if(map[i][j] < toADD + baseHeight)
            map[i][j]=toADD+baseHeight;

      }
   }
   // for(int i=0;i<vertX;i++)
   //    for(int j=0;j<vertY;j++){
   //       if (map[i][j] < baseHeight) printf("TO LOW %d - %d",i,j);
   //       if (map[i][j] > maxMapHeight) puts("TO HIGH");
   //    }
}

void Map::generateRandomMap(){
   //DEKLARACJA PAMIĘCI I USTAWIENIE BAZOWEJ WYSOKOŚCI
   this->mapVert = new float*[vertX];
   this->mapVertFirst = new float*[vertX];
   for(int i=0;i<vertX;i++) {
      mapVert[i] = new float[vertY];
      mapVertFirst[i] = new float[vertY];
   }


   for(int i=0;i<vertX;i++)
      for(int j=0;j<vertY;j++)
         this->mapVert[i][j]=baseHeight;

   //WYLOSOWANIE n WZNIESIEN I URUCHOMIENIE n WĄTKÓW BUDOWY WZNIESIENIA
   int hillNumbers=0;
   hillNumbers = std::rand() % (maxHillNum-minHillNum) + minHillNum;

   for(int i=0;i<hillNumbers;i++)
      makeHill(this->mapVert);

   puts("RENDERED MAP!");
}

void Map::rand(){
   //To bedzie ok tylko trzeba zrobic losowanie <-50;50>
   //zeby bylo we wszystkich kierunkach
   this->windForce.x = std::rand() % 50-25;
   this->windForce.y = std::rand() % 50-25;
   this->windForce.z = std::rand() % 50-25;
}

void Map::kaboom(float x, float y, float z, float radius){
   //Zmniejszamy wysokość w punkcie kaboom i okolicznych
   //Dajemy efekt dźwiękowy i odpryski jakieś.
   int xx = round(x);
   //int yy = round(y);
   int zz = round(z);
   int rr = round(radius);

   int left = xx-rr;
   int right= xx+rr;
   int top = zz-rr;
   int bottom = zz+rr;

   float minTab[2*rr+1][2*rr+1];
   /**
   * tablica nowych wartości
   */
   for(int j=0;j<=2*rr;j++){
      for(int i=0;i<=2*rr;i++){
         float difX=fabs(xx-(i+left));
         float difY=fabs(zz-(j+top));

         float diff=sqrt(pow((float)difX,2)+pow((float)difY,2));
         float tmp = (pow((float)rr,2)-pow((float)diff,2))/2;
         if(tmp<0)tmp=0;
         minTab[i][j]=sqrt(tmp);
      }
   }

   int tabKoorX=0;
   int tabKoorZ=0;
   for(int i=left;i<=right;i++){
      tabKoorX=0;
      for(int j=top;j<=bottom;j++){
         if(i>=0 && j>=0 && i<vertX && j<vertY){
            //if((this->mapVert[i][j] > yy+minTab[tabKoorX][tabKoorZ]) ){
               this->mapVert[i][j] -= minTab[tabKoorX][tabKoorZ];
            //}
            if( this->mapVert[i][j] < this->minHeight ) this->mapVert[i][j] = this->minHeight;
         }
         tabKoorX++;
      }
      tabKoorZ++;
   }

   this->recalculateTriangleMap();
   this->bindBuffers(6,9,GL_DYNAMIC_DRAW);
   puts("kaboom done");
}

void Map::genTriangleTab(){
   int index=0;
   this->vertices.resize(vertX*vertY*9);
   this->indices.resize(2*vertX*(vertY-1)+vertY-1);
   int modX=50;
   int modY=50;

   for(int j=0;j<vertY;j++)
      for(int i=0;i<vertX;i++){
         //wierzchołek
         this->vertices[index] = (float)i;
         this->vertices[index+1] = this->mapVert[i][j];
         this->vertices[index+2] = (float)j;
         //Tektura
         this->vertices[index+3] = (float)(i%modX)/(modX); //tesktura
         if(i/modX % 2 == 1)this->vertices[index+3]=1-this->vertices[index+3];
         this->vertices[index+4] = (float)(j%modY)/(modY);
         if(j/modY % 2 == 1)this->vertices[index+4]=1-this->vertices[index+4];
         this->vertices[index+5] = ((float)this->mapVert[i][j]/maxMapHeight+1)/2;
         //Normals
         glm::vec3 normal = glm::vec3(0,0,0);
         if(i!=0 && j!=0) for(int x=0;x<2;x++) normal+=this->meshNormals[x][i-1][j-1];
         if(i!=0 && j!=vertY-1) normal+=this->meshNormals[1][i-1][j];
         if(i!=vertX-1 && j!=vertY-1) for(int x=0;x<2;x++) normal+=this->meshNormals[x][i][j];
         if(i!=vertX-1 && j!=0) normal+=this->meshNormals[0][i][j-1];
         normal=glm::normalize(normal);
         this->vertices[index+6] = normal.x;
         this->vertices[index+7] = normal.y;
         this->vertices[index+8] = normal.z;

         index+=9;
      }

   GLuint indiVal=0;
   index=0;
   for(int j=0;j<vertY-1;j++){
      indiVal=j*vertX;
      for(int i=0;i<vertX;i++){
         this->indices[index]=indiVal;
         this->indices[++index]=indiVal+vertX;
         indiVal++;
         index++;
      }
      this->indices[index]=vertX*vertY;
      index++;
   }
}

void Map::draw(glm::mat4 projection, glm::mat4 modelView, glm::mat4 lights,glm::vec4 sun){
   this->shader->useShaderProgram(0);

   glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, this->texture3D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
   glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->shadowMap);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "shadowMap"), 1);
   glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->lightMap);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "lightMap"), 2);

   GLint P = glGetUniformLocation(this->shader->shaderProgram[0], "P");
   GLint V = glGetUniformLocation(this->shader->shaderProgram[0], "V");
   GLint L = glGetUniformLocation(this->shader->shaderProgram[0], "L");
   GLint SUN = glGetUniformLocation(this->shader->shaderProgram[0], "SUN");

   glUniformMatrix4fv(P, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(V, 1, GL_FALSE, glm::value_ptr(modelView));
   glUniformMatrix4fv(L, 1, GL_FALSE, glm::value_ptr(lights));
   glUniformMatrix4fv(SUN, 1, GL_FALSE, glm::value_ptr(sun));


   glBindVertexArray(this->currentVAO());

	glDrawElements(GL_TRIANGLE_STRIP, 2*vertX*(vertY-1)+vertY-1, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

}

void Map::recalculateTriangleMap(){
   calcMeshNormals(0,vertX-1,0,vertY-1);
   int index=0;
   for(int j=0;j<vertY;j++)
      for(int i=0;i<vertX;i++){
         if(this->vertices[index+1] != this->mapVert[i][j]){
            this->vertices[index+1] = this->mapVert[i][j];
            this->vertices[index+5] = ((float)this->mapVert[i][j]/maxMapHeight+0.2)/1.2;

            glm::vec3 normal = glm::vec3(0,0,0);
            if(i!=0 && j!=0) for(int x=0;x<2;x++) normal+=this->meshNormals[x][i-1][j-1];
            if(i!=0 && j!=vertY-1) normal+=this->meshNormals[1][i-1][j];
            if(i!=vertX-1 && j!=vertY-1) for(int x=0;x<2;x++) normal+=this->meshNormals[x][i][j];
            if(i!=vertX-1 && j!=0) normal+=this->meshNormals[0][i][j-1];
            normal=glm::normalize(normal);
            this->vertices[index+6] = normal.x;
            this->vertices[index+7] = normal.y;
            this->vertices[index+8] = normal.z;
         }
         index+=9;
      }
}

Map& Map::getInstance(){
	static Map instance;
	return instance;
}

void Map::inBinding() {
   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(vertX*vertY);
}
