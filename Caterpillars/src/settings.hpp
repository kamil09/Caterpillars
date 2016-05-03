#ifndef settings
#define settings

#include <iostream>

class Setting {
   private:
      int width;
      int height;
      bool fullWindow;
      bool fullResolution;
   public:
      Setting();
      Setting(const Setting &);
      ~Setting();
      static Setting& getInstance();
      int getWidth();
      void setWidth(int w);
      int getHeight();
      void setHeight(int h);
      bool getFullWindow();
      void setFullWindow(bool r);
      bool getFullResolution();
      void setFullResolution(bool r);
};


#endif
