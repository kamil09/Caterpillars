#ifndef MENU
#define MENU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "button.hpp"
#include "../../errorGL.hpp"
#include "../state.hpp"
#include <string.h>
#include <functional>
#include "../../font.hpp"
#include "../../errorGL.hpp"
//#include "inputActions.hpp"

// typedef void (*functionArray)();
typedef std::function<void(GLFWwindow*,GLFWcursor*)> functionArray;

class Menu : public State{
public:
    Menu(GLFWwindow *window,GLFWcursor *cur);
    std::vector<const char*> listaTekstur;
    // const char* listaTekstur[4];
    // std::vector<functionArray> callBackArray;
    std::vector<functionArray> callBackArray;
    // std::vector<std::function > callBackArray;
    // std::vector<void (*)()> callBackArray;
    // functionArray *callBackArray;
    std::vector<Button*> listaButtonow;
    Button *background;
    int buttonCount;
    GLfloat buttonWidth;
    GLfloat buttonHeight;
    GLfloat buttonDistance;

    Font *font;


    void createBackgroud(const char*);
    void draw() override;
    void draw2();
    void run() override;
    void pressESC() override;
    void releaseLMB() override;
    float* readPixel(GLFWwindow *window);
    // void addNewButton();
    void createButtons(int count,GLfloat x,GLfloat y);
    void checkCursor();
    void checkButtons();
    virtual void loadTextureFiles(){}
};

#endif
