#include "map.hpp"

/**
 * Ustawienia mapy i genearatora
*/
const int vertX=2000;
const int vertY=2000;
const int baseHeight=50;
const int minMapHeight=60;
const int maxMapHeight=700;
const int maxHillRadius=300;
const int minHillRadius=50;
const int minHillNum=20;
const int maxHillNum=40;

Map::Map(){
   srand (time(NULL));
   this->windForce=10;
   this->gravity=9.81;
   this->minHeight=0;
   this->fogSpeed=0.005;
   this->windMul=0;
   this->air=0.4;
   this->fogHeight=0;

   this->rand();
   this->generateRandomMap();
   this->genTriangleTab();
   this->bindBuffers();
}
Map::~Map(){}

void makeHill(float **map){
   float hillHeight = rand() % (maxMapHeight/2-minMapHeight)+minMapHeight;
   int hillRadius = rand() % (maxHillRadius-minHillRadius)+minHillRadius;
   float hillGeometry = ((float)(rand() % 101)-50)/50;
   int hillX = rand() % vertX;
   int hillY = rand() % vertY;

   float mulX=1;
   float mulY=1;
   int k=0;
   while(hillGeometry>-0.5 && hillGeometry< 0.5 && k!=10){
      hillGeometry+=(hillGeometry*1/2);
      k++;
   }
   if(hillGeometry>-0.5 && hillGeometry< 0.5) hillGeometry=1;

   printf("hillH:%f hillRad:%d hillGeo:%f X:%d Y:%d \n",hillHeight,hillRadius,hillGeometry,hillX,hillY);

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


   int left = hillX-radX*1.3;
   int right = hillX+radX*1.3;
   int top = hillY-radY*1.3;
   int bottom = hillY+radY*1.3;

   if(left<0) left=0;
   if(right>=vertX) right=vertX-1;
   if(top<0) top=0;
   if(bottom>=vertY) bottom=vertY-1;

   float highPerOneX=(float)(hillHeight-baseHeight)/radX;
   float highPerOneY=(float)(hillHeight-baseHeight)/radY;

   for(int i=left;i<=right;i++)
      for(int j=top;j<=bottom;j++){
         int rotDifX=radX-pow(fabs(hillX-i),0.95);
         int rotDifY=radY-pow(fabs(hillY-j),0.95);
         if (rotDifX<0) rotDifX=0;
         if (rotDifY<0) rotDifY=0;
         float toADD = (highPerOneX*(float)rotDifX  +  highPerOneY+(float)rotDifY)/2;

         if(map[i][j] < toADD + baseHeight)
            map[i][j]=toADD+baseHeight;
      }

   for(int i=0;i<vertX;i++)
      for(int j=0;j<vertY;j++){
         if (map[i][j] < baseHeight) printf("TO LOW %d - %d",i,j);
         if (map[i][j] > maxMapHeight) puts("TO HIGH");
      }
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

   this->recalculateTriangleMap(1,2);
}


void Map::genTriangleTab(){
   int index=0;
   this->vertices.resize(vertX*vertY*3);
   this->indices.resize(2*vertX*(vertY-1)+vertY-1);

   for(int j=0;j<vertY;j++)
      for(int i=0;i<vertX;i++){
         this->vertices[index] = ((GLfloat)i)/1000-1;
         this->vertices[index+1] = (GLfloat)this->mapVert[i][j]/1000-1;
         this->vertices[index+2] = ((GLfloat)j)/1000-1;
         index+=3;
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
      this->indices[index]=2*vertX*vertY;
      index++;
   }
}

void Map::bindBuffers(){
   this->shader = new Shader("../src/shader.vs","../src/shader.frag");
   std::cout << "Bindowanie odpowiednich bufferow" << std::endl;
   this->initBinding();
	// GLuint VBO, VAO, EBO;
	// GLuint VBO, EBO;
   // GenVertexArrays(1, &(this->VAO));
   // GenBuffers(1, &this->VBO);
   // GenBuffers(1, &this->EBO);
   //  Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   // BindVertexArray(this->VAO);
   // BindBuffer(GL_ARRAY_BUFFER, this->VBO);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_STATIC_DRAW);

   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex((GLuint)(2*vertX*vertY));

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



   this->endBinding();
}


void Map::draw(){

   // glUseProgram(this->shader->shaderProgram[0]);
   this->shader->useShaderProgram(0);
	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "buttonColor");
   glUniform4f(vertexColorLocation, 0.2f, 1.0f, 0.1f, 1.0f);

   glBindVertexArray(this->buffers[0]->VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 2*vertX*(vertY-1)+vertY-1, GL_UNSIGNED_INT, 0);

   //Rysujemy i teksturujemy mapę
   //Rysujemy i teksturujemy mur (4 pionowe sciany)
   //Rysujemy mgłę zamiast wody lub wodę :)
}


void Map::recalculateTriangleMap(int rowStart,int rowEnd){

}

Map& Map::getInstance(){
	static Map instance;
	return instance;
}
