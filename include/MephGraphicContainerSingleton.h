#ifndef MephGraphicContainerSingleton_h
#define MephGraphicContainerSingleton_h 1

#if defined (linux)
  #include "MephGraphicContainerImp_X11.h"
#endif

class MephGraphicContainerSingleton
{
  public:
		class MephGraphicContainerImp * getMephGraphicContainerImp();
		static MephGraphicContainerSingleton * getMephGraphicContainerSingleton();
	
	private:
	  static MephGraphicContainerSingleton * mephgraphiccontainersingleton;
	friend class MephGraphicContainer;
	
};

inline class MephGraphicContainerSingleton * MephGraphicContainerSingleton::getMephGraphicContainerSingleton()
{
  if (mephgraphiccontainersingleton==0)
		mephgraphiccontainersingleton=new MephGraphicContainerSingleton;
	
	return (mephgraphiccontainersingleton);
}

inline class MephGraphicContainerImp * MephGraphicContainerSingleton::getMephGraphicContainerImp()
{
  #if defined(linux)
	  return(new class MephGraphicContainerImp_X11);
	#endif
}

#endif