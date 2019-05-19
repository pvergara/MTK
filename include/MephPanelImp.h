#ifndef MephPanelImp_h
#define MephPanelImp_h 1

//#include "MephWindowImp.h"
#include "MephVisObjImp.h"


class MephPanelImp:public MephVisObjImp
{
  public:
//	  MephPanelImp();
	
	  virtual void initValues(const class MephPanel *mephpanel,const class MephVisObjImp * mephvisobjimp){};
	  virtual void initValues(class MephAppImp const *mephappimp){};
    /*ESTE YA NO SIRVE
		virtual void initValues(const class MephPanel *mephpanel,const class MephPanelImp * mephpanelimp){};
		/******************/
		virtual void changeAddFunction(int addfunction){};
			
//		virtual int getWidth(){};
//		virtual int getHeight(){};
	  virtual void refresh(){};
		virtual void resize(){};
		virtual void setBackground(){};
    virtual void refresh(int x,int y,unsigned int width,unsigned int height){};
    virtual void copyBackPixmap(){};
    virtual void backPixmapToMe(){};
		
/*		#if defined (linux)
			virtual GC getGC(){};
			virtual const Display *getDisplay(){};
			virtual Drawable getId(){};
		#endif*/
};

#endif