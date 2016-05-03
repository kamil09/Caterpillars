#include "settings.hpp"


Setting::Setting(){
	std::cout << "stworzono singleton" << std::endl;
	this->width=800;
	this->height=600;
	this->fullResolution=true;
	this->fullWindow=true;
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
