#ifndef MephDrawSingleton_h
#define MephDrawSingleton_h 1

#if defined (linux)
  #include "MephDrawImp_X11.h"
#endif

class MephDrawSingleton
{
  public:
		class MephDrawImp * getMephDrawImp();
		static MephDrawSingleton * getMephDrawSingleton();
	
	private:
	  static MephDrawSingleton * mephdrawsingleton;
	friend class MephDraw;
	
};

inline class MephDrawSingleton * MephDrawSingleton::getMephDrawSingleton()
{
  if (mephdrawsingleton==0)
		mephdrawsingleton=new MephDrawSingleton;
	
	return (mephdrawsingleton);
}

inline class MephDrawImp * MephDrawSingleton::getMephDrawImp()
{
  #if defined(linux)
	  return(new class MephDrawImp_X11);
	#endif
}

#endif