#ifndef MephTextRawImp_X11_h
#define MephTextRawImp_X11_h 1

#include "MephTextRawImp.h"
#include <X11/Xlib.h>

class MephTextRawImp_X11:public MephTextRawImp
{
  public:
	  void initValues (const class MephTextRaw *mephtextraw,const class MephVisObjImp *mephvisobjimp);
		void show();
  	char loadFont();

		void setText();
			
		void setBackColor();
		void setForeColor();
		char refreshFont();

	private:
		char setFont(char *fontname);
			
		class MephTextRaw *mephtextraw;
		class MephVisObjImp *mephvisobjimp;
		GC gc;
		XFontStruct *xfontstruct;
	  XChar2b *xchar2b;
};

#endif