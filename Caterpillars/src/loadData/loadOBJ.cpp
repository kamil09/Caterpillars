#include "loadOBJ.hpp"

/*
 * Blender:
 * OBJ + triangulate faces + write materials + include UVs + inpude Nurmals
 *
 */
bool loadObj::load(char * path,std::vector<GLfloat> *vertices, std::vector<GLuint> *indices){
   FILE * file = fopen(path, "r");
   if( file == NULL ){
      printf("Impossible to open the file !\n");
      return false;
   }
   std::vector<double> tex;
   std::vector<double> ver;
   std::vector<double> nor;
   std::vector<int> uvIndices;
   std::vector<double> normalIndices;
   int verNum=0;
   int texNum=0;
   int norNum=0;
   while( 1 ){
      char lineHeader[128];
      int res = fscanf(file, "%s", lineHeader);
      if (res == EOF) break;

      if ( strcmp( lineHeader, "v" ) == 0 ){
         double tmp [3];
         fscanf(file, " %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2] );
         ver.push_back(tmp[0]);
         ver.push_back(tmp[1]);
         ver.push_back(tmp[2]);
         verNum++;
      }
      else if ( strcmp( lineHeader, "vt" ) == 0 ){
         double tmp [2];
         fscanf(file, " %lf %lf\n", &tmp[0], &tmp[1] );
         tex.push_back(tmp[0]);
         tex.push_back(tmp[1]);
         texNum++;
      }
      else if ( strcmp( lineHeader, "vn" ) == 0 ){
         double tmp [3];
         fscanf(file, " %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2] );
         nor.push_back(tmp[0]);
         nor.push_back(tmp[1]);
         nor.push_back(tmp[2]);
         norNum++;
      }
      else if ( strcmp( lineHeader, "f" ) == 0 ){
         unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

         int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
         if (matches != 9){
              printf("File can't be read by our simple parser : ( Try exporting with other options\n");
              return false;
         }
         indices->push_back(vertexIndex[0]);
         indices->push_back(vertexIndex[1]);
         indices->push_back(vertexIndex[2]);
         uvIndices.push_back(uvIndex[0]);
         uvIndices.push_back(uvIndex[1]);
         uvIndices.push_back(uvIndex[2]);
         normalIndices.push_back(normalIndex[0]);
         normalIndices.push_back(normalIndex[1]);
         normalIndices.push_back(normalIndex[2]);
      }
   }
   // for( unsigned int i=0; i<indices->size(); i++ ){
   //    unsigned int vertexIndex = (*indices)[i];
   //    unsigned int texIndex = uvIndices[i];
   //    unsigned int normalIndex = normalIndices[i];
   //
   //    vertices->push_back(ver[vertexIndex*3-3]);
   //    vertices->push_back(ver[vertexIndex*3-2]);
   //    vertices->push_back(ver[vertexIndex*3-1]);
   //    vertices->push_back(tex[texIndex*2-2]);
   //    vertices->push_back(tex[texIndex*2-1]);
   //    vertices->push_back(nor[normalIndex*3-3]);
   //    vertices->push_back(nor[normalIndex*3-2]);
   //    vertices->push_back(nor[normalIndex*3-1]);
   //
   // }
   vertices->resize(verNum*8+8);
   for( unsigned int i=0; i<indices->size(); i++ ){
      int vertexIndex = (*indices)[i];
      (*indices)[i]--;
      int texIndex = uvIndices[i];
      int normalIndex = normalIndices[i];
      int index = (vertexIndex-1)*8;

      (*vertices)[index] = ver[vertexIndex*3-3];
      (*vertices)[index+1] = ver[vertexIndex*3-2];
      (*vertices)[index+2] = ver[vertexIndex*3-1];
      (*vertices)[index+3] = tex[texIndex*2-2];
      (*vertices)[index+4] = tex[texIndex*2-1];
      (*vertices)[index+5] = nor[normalIndex*3-3];
      (*vertices)[index+6] = nor[normalIndex*3-2];
      (*vertices)[index+7] = nor[normalIndex*3-1];
   }
   return true;
}
