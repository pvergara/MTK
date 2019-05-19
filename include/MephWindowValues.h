#ifndef MephWindowValues_h
#define MephWindowValues_h 1

#include <X11/Xlib.h>

class MephWindowValues
{
  private:
	
	Display const * disp;
	Window id;
	int width;
	int height;
	
	public:
	
  MephWindowValues(Display const * const disp,Window const id);
  MephWindowValues(Display const * const disp,Window const id,int width,int height);
	
  int getWidth();
	int getHeight();
	
	void setWidth(int width);
	void setHeight(int height);
	
	Display * getDisplay();
	Window getWindow();
};

#endif
