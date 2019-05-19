#ifndef MephFloatingWindowImp_h
#define MephFloatingWindowImp_h 

#include "MephVisObjImp.h"
#include "MephVisObj.h"

class MephFloatingWindowImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephFloatingWindow *mephfloatingwindow, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephVisObjImp * mephvisobjimp){};
    virtual void show(void){};
    virtual void show(int x,int y){};
		virtual void destroyWindow(const class MephItemImp * mephitemipm){};

		virtual void update(MephUpdateParam mephupdateparam){};
};

#endif