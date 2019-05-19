#ifndef MephColorImp_X11_h
#define MephColorImp_X11_h 1

#include "MephColorImp.h"
#include "MephAppImp_X11.h"
#include <X11/Xlib.h>

class MephColorImp_X11: public MephColorImp
{
  public:
	  void initValues(class MephVisObjImp const * mephvisobjimp);
	  ~MephColorImp_X11();
	  unsigned short getRed(unsigned long colorindex);
	  unsigned short getGreen(unsigned long colorindex);
	  unsigned short getBlue(unsigned long colorindex);
	  unsigned long getColorIndex(unsigned short red,unsigned short green,unsigned short blue);
	
	private:
    Display * MephAppImpX11_getDisplay ();
	  XColor color;
	  class MephVisObjImp * mephvisobjimp;
};

#endif