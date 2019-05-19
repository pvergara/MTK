#ifndef MephVisObjImp_h
#define MephVisObjImp_h 1

#if defined (linux)
  #include <X11/Xlib.h>
#endif

#include "MephGen.h"
#include <map.h>

typedef map <int,Window> mapWindow;
typedef map <int,Pixmap> mapId;

class MephVisObjImp
{
  public:
			
		virtual int getWidth(){};
		virtual int getHeight(){};
		
		#if defined (linux)
			virtual GC getGC(){};
			virtual const Display *getDisplay(){};
			virtual Pixmap getId(){return(0);};
			virtual Window getWindow(){return(0);};
			virtual Pixmap getId(int index,char *result){return(0);};
			virtual Window getWindow(int index,char *result){return(0);};
			virtual mapWindow getIds(){};
			virtual mapId getWindows(){};
		  virtual void recieveEvent(XEvent xevent){};		
		  virtual void recieveNoMotion(){};		
		#endif
};

#endif