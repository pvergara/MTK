#ifndef MephWindowSingleton_h
#define MephWindowSingleton_h 1

#if defined (linux)
  #include "MephWindowImp_X11.h"
#endif

class MephWindowSingleton
{
  public:
		class MephWindowImp * getMephWindowImp();
		static MephWindowSingleton * getMephWindowSingleton();
	
	private:
	  static MephWindowSingleton * mephwindowsingleton;
	  friend class MephWindow;
	
};

inline class MephWindowSingleton * MephWindowSingleton::getMephWindowSingleton()
{
  if (mephwindowsingleton==0)
		mephwindowsingleton=new class MephWindowSingleton;
	
	return (mephwindowsingleton);
}

inline class MephWindowImp * MephWindowSingleton::getMephWindowImp()
{
  #if defined(linux)
	  return(new class MephWindowImp_X11);
	#endif
}

#endif