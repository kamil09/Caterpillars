#include "settings.hpp"

void makeConfFile(Setting *th){
	FILE *out;
	out=fopen("../settings","w");
	if(out){
		fprintf(out,"#USTAWIENIA\n#EKRAN\n");
		fprintf(out,"width:%d\n",th->getWidth());
		fprintf(out,"height:%d\n",th->getHeight());
		fprintf(out,"fullWindow:%d\n",th->getFullWindow());
		fprintf(out,"#IF ON width and height are not used;\n");
		fprintf(out,"fullResolution:%d\n",th->getFullResolution());
		fprintf(out,"#ranking\n");
		fprintf(out,"theBestFile:%s\n",th->getRankFileName() );
		fprintf(out,"#USTAWIENIA GRY\n");
		fprintf(out,"#0- początkujący ; 1-normalny ; 2-zaawansowany; 3-matematyk\n");
		fprintf(out,"difficulty:%d\n",th->getDifficulty());
		fprintf(out,"frames:%d\n",th->getFrames());
		fprintf(out,"music:%d\n",th->getMusic());
		fprintf(out,"voice:%d",th->getSounds());
	}
}
void Setting::loadFromFile(FILE *in){
	char buffer[60], name[20], value[20];
   int i=0,j=0;
   while(fgets(buffer, sizeof(buffer), in)){
	 	for(i=0;i<20;i++){
            name[i]=0;
            value[i]=0;
    	}
	 	if(buffer[0]!='#' || buffer[0]!='\n'){

			for(i=0;i<20;i++){
	      	if(buffer[i]!=':') name[i]=buffer[i];
	      	else break;
	    	}
	    	i++;

	    	for(j=-1;i<40;i++){
	      	j++;
	      	if(buffer[i]!=0) value[j]=buffer[i];
	      	else break;
	    	}

			if(!strcmp(name,"width")) this->width = atoi(value);
		   if(!strcmp(name,"height")) this->height = atoi(value);
		   if(!strcmp(name,"fullWindow")) this->fullWindow = atoi(value)==0?false:true;
		   if(!strcmp(name,"fullResolution")) this->fullResolution = atoi(value)==0?false:true;
		   if(!strcmp(name,"theBestFile")) this->rankFileName = value;
			if(!strcmp(name,"difficulty")) this->difficulty = atoi(value);
			if(!strcmp(name,"frames")) this->frames = atoi(value);
			if(!strcmp(name,"music")) this->music = atoi(value)==0?false:true;
			if(!strcmp(name,"voice")) this->sounds = atoi(value)==0?false:true;
		}
  }
}

Setting::Setting(){
	//std::cout << "stworzono singleton" << std::endl;
	this->width=800;
	this->height=600;
	this->fullResolution=true;
	this->fullWindow=true;
	this->music=true;
	this->sounds=true;
	this->difficulty=1;
	this->frames=30;
	this->rankFileName=(char*)"rankFile";

	//LOAD SETTINGS FROM FILE
	this->load();

	if(difficulty<0) difficulty=0;
	if(difficulty>3) difficulty=3;
	if(frames<15) frames=15;
	if(frames>60) frames=60;
}

void Setting::load(){
	FILE *in;
	in=fopen("../settings","r");
	if(!in){
	 	makeConfFile(this);
	 }
	else{
		this->loadFromFile(in);
		fclose(in);
	}
}

Setting::~Setting(){

}

Setting& Setting::getInstance(){
	static Setting instance;
	return instance;
}

int Setting::getHeight(){
	return this->height;
}
bool Setting::getFullWindow(){
	return this->fullWindow;
}
bool Setting::getFullResolution(){
	return this->fullResolution;
}
int Setting::getWidth(){
	return this->width;
}
bool Setting::getMusic(){
	return this->music;
}
bool Setting::getSounds(){
	return this->sounds;
}
int Setting::getDifficulty(){
	return this->difficulty;
}
int Setting::getFrames(){
	return this->frames;
}
char* Setting::getRankFileName(){
	return this->rankFileName;
}
