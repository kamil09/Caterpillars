#include "settings.hpp"


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
	this->rankFileName="rankFile";

	//LOAD SETTINGS FROM FILE

	if(difficulty<0) difficulty=0;
	if(difficulty>3) difficulty=3;
	if(frames<15) frames=15;
	if(frames>60) frames=60;
}

Setting::~Setting(){

}

Setting& Setting::getInstance(){
	// static Setting *instance = new Setting();
	// return *instance;
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
std::string Setting::getRankFileName(){
	return this->rankFileName;
}
