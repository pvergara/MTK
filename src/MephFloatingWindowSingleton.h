#ifndef MephFloatingWindowSingleton_h
#define MephFloatingWindowSingleton_h 1

#if defined (linux)
  #include "MephFloatingWindowImp_X11.h"
#endif

class MephFloatingWindowSingleton
{
  public:
		class MephFloatingWindowImp * getMephFloatingWindowImp();
		static MephFloatingWindowSingleton * getMephFloatingWindowSingleton();
	
	private:
	  static MephFloatingWindowSingleton * mephfloatingwindowsingleton;
	friend class MephFloatingWindow;
	
};

inline MephFloatingWindowSingleton * MephFloatingWindowSingleton::getMephFloatingWindowSingleton()
{
  if (mephfloatingwindowsingleton==0)
		mephfloatingwindowsingleton=new MephFloatingWindowSingleton;
	
	return (mephfloatingwindowsingleton);
}

inline class MephFloatingWindowImp * MephFloatingWindowSingleton::getMephFloatingWindowImp()
{
  #if defined(linux)
	  return(new class MephFloatingWindowImp_X11);
	#endif
}

#endif