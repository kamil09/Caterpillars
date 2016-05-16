#include "map.hpp"

Map::Map(){
   srand (time(NULL));
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
   this->fogHeight=0;
   this->shader = new Shader("../src/shaders/map/mapShader.vs","../src/shaders/map/mapShader.frag");
   this->rand();
   this->generateRandomMap();
   this->genTriangleTab();
   this->bindBuffers(true);
   int numOfTex = 8;
   GLchar *texturePath[numOfTex];
   texturePath[0] = (char*)"../src/img/map/map1.png";texturePath[1] = (char*)"../src/img/map/map2.png";
   texturePath[2] = (char*)"../src/img/map/map3.png";texturePath[3] = (char*)"../src/img/map/map4.png";
   texturePath[4] = (char*)"../src/img/map/map5.png";texturePath[5] = (char*)"../src/img/map/map6.png";
   texturePath[6] = (char*)"../src/img/map/map7.png";texturePath[7] = (char*)"../src/img/map/map8.png";
   this->bindTexture3D(numOfTex,texturePath);

}
Map::~Map(){}

void makeHill(float **map){
   float hillHeight = rand() % (maxMapHeight*3/5-minMapHeight)+minMapHeight;
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
   for(int i=0;i<vertX;i++) mapVert[i]=new float[vertY];

   for(int i=0;i<vertX;i++)
      for(int j=0;j<vertY;j++)
         this->mapVert[i][j]=baseHeight;

   //WYLOSOWANIE n WZNIESIEN I URUCHOMIENIE n WĄTKÓW BUDOWY WZNIESIENIA
   int hillNumbers=0;
   hillNumbers = std::rand() % (maxHillNum-minHillNum) + minHillNum;

   //threads fight : START
   for(int i=0;i<hillNumbers;i++)
      makeHill(this->mapVert);

   puts("RENDERED MAP!");
}

void Map::rand(){
   this->windForce = std::rand() % 50;
}

void Map::kaboom(float x, float y, float z, float radius){
   //Zmniejszamy wysokość w punkcie kaboom i okolicznych
   //Dajemy efekt dźwiękowy i odpryski jakieś.
   int xx = round(x);
   int yy = round(y);
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

         minTab[i][j]=sqrt(pow((float)rr,2)-pow((float)diff,2));
      }
   }

   int tabKoorX=0;
   int tabKoorZ=0;
   for(int i=left;i<=right;i++){
      tabKoorX=0;
      for(int j=top;j<=bottom;j++){
         if(i>=0 && j>=0 && i<vertX && j<vertY){
            if((this->mapVert[i][j] > yy+minTab[tabKoorX][tabKoorZ]) ){
               this->mapVert[i][j] -= minTab[tabKoorX][tabKoorZ];
               //printf("%d %d, %f\n",i,j,this->mapVert[i][j]);
            }
            if( this->mapVert[i][j] < this->minHeight ) this->mapVert[i][j] = this->minHeight;
         }
         tabKoorX++;
      }
      tabKoorZ++;
   }

   this->recalculateTriangleMap();
   this->bindBuffers(false);
   puts("kaboom done");
}

void Map::genTriangleTab(){
   int index=0;
   this->vertices.resize(vertX*vertY*6);
   this->indices.resize(2*vertX*(vertY-1)+vertY-1);

   for(int j=0;j<vertY;j++)
      for(int i=0;i<vertX;i++){
         this->vertices[index] = (float)i;
         this->vertices[index+1] = this->mapVert[i][j];
         this->vertices[index+2] = (float)j;
         this->vertices[index+3] = (float)(vertX%101)/100; //tesktura
         this->vertices[index+4] = (float)(vertY%101)/100;
         this->vertices[index+5] = this->mapVert[i][j]/maxMapHeight;
         index+=6;
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
   // this->bindBuffers(false);
}

void Map::bindBuffers(bool newBuffer){
   // std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
   this->initBinding(newBuffer);

   glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_DYNAMIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_DYNAMIC_DRAW);

   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(vertX*vertY);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(1);

   this->endBinding();
}


void Map::draw(glm::mat4 projection, glm::mat4 modelView){
   this->shader->useShaderProgram(0);
   glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, this->texture3D);
   glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);

   GLint iProjectionLoc = glGetUniformLocation(this->shader->shaderProgram[0], "projectionMatrix");
   GLint iModelViewLoc = glGetUniformLocation(this->shader->shaderProgram[0], "modelViewMatrix");

   glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
   glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(modelView));

   glBindVertexArray(this->currentVAO());

	glDrawElements(GL_TRIANGLE_STRIP, 2*vertX*(vertY-1)+vertY-1, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

   //Rysujemy i teksturujemy mapę
   //Rysujemy i teksturujemy mur (4 pionowe sciany)
   //Rysujemy mgłę zamiast wody lub wodę :)
}


void Map::recalculateTriangleMap(){
   int index=0;
   for(int j=0;j<vertY;j++)
      for(int i=0;i<vertX;i++){
         if(this->vertices[index+1] != this->mapVert[i][j]){
            this->vertices[index+1] = this->mapVert[i][j];
         }
         index+=3;
      }
}

Map& Map::getInstance(){
	static Map instance;
	return instance;
}
