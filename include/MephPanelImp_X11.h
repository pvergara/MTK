#ifndef MephPanelImp_X11_h
#define MephPanelImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephPanelImp.h"
#include <X11/Xlib.h>

class MephPanelImp_X11: public MephPanelImp, public MephVisObjImp_X11
{
	public:
	  MephPanelImp_X11();
	  ~MephPanelImp_X11();
	
    void initValues(const class MephPanel *mephpanel,const class MephVisObjImp * mephvisobjimp);
	  void initValues(class MephAppImp const *mephappimp);
	  /*ESTE YA NO SIRVE
    void initValues(const class MephPanel *mephpanel,const class MephPanelImp * mephpanelimp);
	  /******************/
		void changeAddFunction(int addfunction);
	  GC getGC();
  	Pixmap getId();
		Pixmap getId(int index,char *result);
		map <int,Pixmap> getIds();
    const Display * getDisplay();
	
	  int getWidth();
	  int getHeight();
	
    void copyBackPixmap();
    void backPixmapToMe();
	  void refresh();
    void refresh(int x,int y,unsigned int width,unsigned int height);

    void setBackground();	
	  void resize();

	private:
	
	  Drawable aux;
	  GC gc;
	
	  class MephPanel *mephpanel;
//		class MephAppImp const *mephappimp;
    /*ESTE YA NO SIRVE
    class MephPanelImp *mephpanelimp;
	  /******************/
	  class MephVisObjImp *mephvisobjimp;
};

#endif