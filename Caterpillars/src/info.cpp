#include "info.hpp"

Info::Info(){
    this->font = new Font("../src/fonts/Coalition.ttf", 16);
    this->initFps();
}

void Info::initFps(){
    this->lastTime = glfwGetTime();
    this->nbFrames = 0;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    //TODO: Sprawdzić czy dziala dla wielu rozdzielczosci
    this->addText("",-1366.0f/2+30,-768.0f/2+30,1.0f,'f');
}

void Info::fps(){
    double currentTime = glfwGetTime();
    this->nbFrames++;
    if(currentTime - this->lastTime >= 1.0){
        std::string czas = std::to_string(1000.0f/double(this->nbFrames)) + " ms/frame";
        this->texty['f']->text = czas;
        this->nbFrames = 0;
        this->lastTime += 1.0;
    }
}

void Info::draw(){
    glEnable(GL_BLEND);
    if(this->showFps){
        this->fps();
    }
    std::map<char,Text*>::iterator it;
    for(it = this->texty.begin(); it!=this->texty.end();++it){
        Text *temp = it->second;
        temp->draw(this->font);
    }
    glDisable(GL_BLEND);
}

unsigned int Info::addText(std::string newText,float newX,float newY,float newSkala,char index){
    Text *temp = new Text(newText,newX,newY,newSkala,glm::vec3(1.0f,1.0f,1.0f));
    this->texty.insert(std::pair<char,Text*>(index,temp));
    return this->texty.size()-1;
}


void Info::usage(){
    sysinfo(&this->meminfo);
    this->virtualMemory();
    this->physicalMemory();
}

int Info::extractNumber(char* line){
    int length = strlen(line);
    char* p = line;
    while (*p < '0' || *p > '9') p++;
    line[length-3] = '\0';
    length = atoi(p);
    return length;
}

int Info::getValue(const char *fileDir, const char *text){
    FILE *file = fopen(fileDir,"r");
    int result = -1;
    char line[128];
    while(fgets(line,128,file)!=NULL){
        if(strncmp(line,text,strlen(text))==0){
            result = extractNumber(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void Info::virtualMemory(){
    //Total Virtual Memory
    long long totalVirtualMemory = this->meminfo.totalram;
    totalVirtualMemory *= this->meminfo.mem_unit;
    totalVirtualMemory += this->meminfo.totalswap;
    //Virtual Memory currently used (All process)
    long long virtualMemoryUsed = this->meminfo.totalram;
    virtualMemoryUsed += this->meminfo.totalswap - this->meminfo.freeswap;
    virtualMemoryUsed *= this->meminfo.mem_unit;
    //Virtual Memory Currently used by processs
    int virtualProcess = this->getValue("/proc/self/status","VmSize:");
    std::string VM = "VM: " + std::to_string(virtualProcess) + " ( " + std::to_string(virtualMemoryUsed / 1024.f) + " ) " + " / " + std::to_string(totalVirtualMemory / 1024.f);
    this->texty['v']->text = VM;
}

void Info::physicalMemory(){
    long long totalPhysicalMemory = this->meminfo.totalram;
    totalPhysicalMemory *= this->meminfo.mem_unit;
    long long physicalMemoryUsed = this->meminfo.totalram - this->meminfo.freeram;
    physicalMemoryUsed *= this->meminfo.mem_unit;
    int physicalProcess = this->getValue("/proc/self/status", "VmRSS:");
    std::string RAM = "RAM: " + std::to_string(physicalProcess) + " ( " + std::to_string(physicalMemoryUsed / 1024.f) + " ) " + " / " + std::to_string(totalPhysicalMemory / 1024.f);
    this->texty['r']->text = RAM;
}
