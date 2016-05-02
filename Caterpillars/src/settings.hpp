#ifndef settings
#define settings

#include <iostream>

class Setting {
private:
int width;
int height;
bool fullWindow;
public:
Setting();
Setting(const Setting &);
~Setting();
static Setting& getInstance();
int getWidth();
int setWidth();
int getHeight();
int setHeight();
int getFullWindow();
int setFullWindow();
};


#endif
