#include "info.hpp"

// Info::Info(){
//
// }

Text::Text(std::string newText,float newX,float newY,float newSkala){
    this->text = newText;
    this->x = newX;
    this->y = newY;
    this->skala = newSkala;
}

Info::Info(GLFWwindow* window){
    this->font = new Font("../src/fonts/Coalition.ttf",window,16);
    this->initFps();
}


void Info::initFps(){
    this->lastTime = glfwGetTime();
    this->nbFrames = 0;
    this->addText("123testowanie",0.0f,0.0f,1.0f);
    this->fpsIndex = this->texty.size()-1;
    // std::cout << this->fpsIndex << std::endl;
}

void Info::fps(){
    double currentTime = glfwGetTime();
    this->nbFrames++;
    if(currentTime - this->lastTime >= 1.0){
        std::string czas = std::to_string(1000.0f/double(this->nbFrames)) + " ms/frame";
        std::cout << 1000.0f/double(this->nbFrames) << "ms/frame" << std::endl;
        this->texty[this->fpsIndex]->text = czas;
        this->nbFrames = 0;
        this->lastTime += 1.0;
    }
}

void Info::draw(){
    this->fps();
    for(unsigned int i=0;i<this->texty.size();i++){
        this->texty[i]->draw(this->font);
    }
}

unsigned int Info::addText(std::string newText,float newX,float newY,float newSkala){
    Text *temp = new Text(newText,newX,newY,newSkala);
    this->texty.push_back(temp);
    return this->texty.size()-1;
}

void Text::draw(Font *font){
    font->print(this->text,this->x,this->y, this->skala,glm::vec3(1.0f,1.0f,1.0f));
}
