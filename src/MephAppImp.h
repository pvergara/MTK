#ifndef MephAppimp_h
#define MephAppimp_h 1

#include <alloc.h>
#include <iostream.h>

#if defined(linux)
#include <X11/Xlib.h>
#endif
#include "MephGen.h"
class MephAppImp
{

  public:
      MephAppImp();
      ~MephAppImp();

      MephAppImp(const MephAppImp &right);

      const MephAppImp & operator=(const MephAppImp &right);

      int operator==(const MephAppImp &right) const;

      int operator!=(const MephAppImp &right) const;

      #if defined(linux)
       virtual int getScreen(){};
       virtual int getNscreen(){};
       virtual Display const *getDisplay() const {};
			 virtual Window getRootWindow(){};

       virtual void initValues (int argc,char *argv[],const Display *disp){}
    	 virtual char setTabIndex(Window window,MephTabIndex tabindex,char enabled){};
      #endif

      virtual int getSWidth(){}
      virtual int getSHeight(){}
			virtual void eventLoop(){}
//			virtual void contain(const class MephEventImp * mepheventimp){}
			virtual void contain(const class MephVisObjImp * mephvisobjimp){};
			virtual void contain(const class MephVisObjImp * mephvisobjimp,int index){};
			virtual void contain(const class MephVisObjImp * mephvisobjimp,const class MephVisObjImp * mephfloatingwindow){};
};
#endif
