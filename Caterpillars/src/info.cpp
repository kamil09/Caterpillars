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
    // this->addText("",10.0f,this->font->rozmiar+10.0f,1.0f,'v');
    // this->addText("",10.0f,2*this->font->rozmiar+10.0f,1.0f,'r');
}



void Info::initFps(){
    this->lastTime = glfwGetTime();
    this->nbFrames = 0;
    this->addText("",10.0f,10.0f,1.0f,'f');
    // this->fpsIndex = this->texty.size()-1;
    // std::cout << this->fpsIndex << std::endl;
}

void Info::fps(){
    double currentTime = glfwGetTime();
    this->nbFrames++;
    if(currentTime - this->lastTime >= 1.0){
        std::string czas = std::to_string(1000.0f/double(this->nbFrames)) + " ms/frame";
        // std::cout << 1000.0f/double(this->nbFrames) << "ms/frame" << std::endl;
        this->texty['f']->text = czas;
        this->nbFrames = 0;
        this->lastTime += 1.0;
    }
}

void Info::draw(){
    this->freeIndex = 0;
    if(this->showFps){
        this->fps();
    }
    // if(this->showUsage){
    //     this->usage();
    // }
    std::map<char,Text*>::iterator it;
    for(it = this->texty.begin(); it!=this->texty.end();++it){
    // for(auto const &it : this->texty){
        // it.second->draw(this->font);
        Text *temp = it->second;
        temp->draw(this->font);
        // std::cout << it.first << std::endl;
        // std::cout << it->first << std::endl;
    }
}

unsigned int Info::addText(std::string newText,float newX,float newY,float newSkala,char index){
    Text *temp = new Text(newText,newX,newY,newSkala);
    // this->texty.push_back(temp);
    // this->texty['f'] = temp;
    this->texty.insert(std::pair<char,Text*>(index,temp));
    return this->texty.size()-1;
}

void Text::draw(Font *font){
    font->print(this->text,this->x,this->y, this->skala,glm::vec3(1.0f,1.0f,1.0f));
}

void Info::usage(){
    sysinfo(&this->meminfo);
    this->virtualMemory();
    // this->freeIndex++;
    this->physicalMemory();
    // this->freeIndex++;
}

int Info::extractNumber(char* line){
    int length = strlen(line);
    char* p = line;
    while (*p < '0' || *p > '9'){
        p++;
    }
    line[length-3] = '\0';
    length = atoi(p);
    return length;
}

int Info::getValue(const char *fileDir, const char *text){
    FILE *file = fopen(fileDir,"r");
    int result = -1;
    char line[128];
    // std::cout << "Text length = " << strlen(text) << std::endl;
    while(fgets(line,128,file)!=NULL){
        if(strncmp(line,text,strlen(text))==0){
            result = extractNumber(line);
            break;
        }
    }
    fclose(file);
    // std::cout << "result: " << result << std::endl;
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
    // std::cout << std::to_string(this->meminfo.mem_unit) << std::endl;
    std::string VM = "VM: " + std::to_string(virtualProcess) + " ( " + std::to_string(virtualMemoryUsed / 1024.f) + " ) " + " / " + std::to_string(totalVirtualMemory / 1024.f);
    // std::cout << VM << std::endl;
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
