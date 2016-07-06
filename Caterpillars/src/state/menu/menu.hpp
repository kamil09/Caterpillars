#ifndef MENU
#define MENU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "button.hpp"
#include "../sprite.hpp"
#include "../../errorGL.hpp"
#include "../state.hpp"
#include <string.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../errorGL.hpp"

// typedef void (*functionArray)();
typedef std::function<void(State *,GLFWwindow*,GLFWcursor*)> functionArray;

class Menu : public State{
public:
    Menu(GLFWwindow *window,GLFWcursor *cur);
//    std::vector<GLchar*> listaTekstur;
    std::vector<std::string> listaTekstur;
    std::vector<glm::vec4> listaWspolrzednych;
    std::vector<glm::vec3> listaPrzesuniec;
    int check;
    int currentButton;
    std::vector<functionArray> callBackArray;
    std::vector<Button*> listaButtonow;
    std::vector<Sprite*> listaSpritowFG;
    std::vector<Sprite*> listaSpritowBG;
    Button *background;
    int buttonCount;
    void createBackgroud(GLchar *fileName);
    virtual void draw() override;
    void run() override;
    virtual void pressESC() override;
    virtual void releaseLMB() override;
    float* readPixel(GLFWwindow *window);
    virtual void createButtons();
    void checkCursor();
    int checkButtons();
    virtual void loadCallBacks(){}
    virtual void loadTextureFiles(){}
    virtual void loadCoordinates(){}
    virtual void loadTranslates(){}
    virtual void loadSprites(){}
};

#endif
