#ifndef MephGraphicContainer_h
#define MephGraphicContainer_h 1

#include "MephGraphicContainerImp.h"
#include "MephGraphicContainerSingleton.h"
#include "MephVisObj.h"

class MephGraphicContainer
{
	public:
	
		MephGraphicContainer();
		~MephGraphicContainer();

	private:
	  class MephGraphicImp *mephgraphicimp;
	  class MephGraphicSingleton *mephgraphicsingleton;
	
};

#endif