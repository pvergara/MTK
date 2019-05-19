#ifndef MephGraphicContainerImp_X11_h
#define MephGraphicContainerImp_X11_h 1

#include "MephGraphicContainerImp.h"

class MephGraphicContainerImp_X11:public MephGraphicContainerImp
{
	public:
	  void initValues (class MephGraphicContainerImp const * mephgraphiccontainerimp, class MephVisObjImp const * mephvisobjimp);

	protected:
	  class MephGraphicContainer * mephgraphiccontainer;
	  class MephVisObjImp * mephvisobjimp;
};

#endif