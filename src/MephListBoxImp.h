#ifndef MephListBoxImp_h
#define MephListBoxImp_h 

#include "MephVisObjImp.h"

class MephListBoxImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephListBox *mephlistbox, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephVisObjImp * mephvisobjimp){};

		virtual void destroyWindow(const class MephItemImp * mephitemimp){};
		virtual void update(MephUpdateParam mephupdateparam){};
};

#endif