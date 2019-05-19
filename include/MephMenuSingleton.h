#ifndef MephMenuSingleton_h
#define MephMenuSingleton_h 1

#if defined (linux)
  #include "MephMenuImp_X11.h"
#endif

class MephMenuSingleton
{
  public:
		class MephMenuImp * getMephMenuImp();
		static MephMenuSingleton * getMephMenuSingleton();
	
	private:
	  static MephMenuSingleton * mephmenusingleton;
	friend class MephMenu;
	
};

inline MephMenuSingleton * MephMenuSingleton::getMephMenuSingleton()
{
  if (mephmenusingleton==0)
		mephmenusingleton=new MephMenuSingleton;
	
	return (mephmenusingleton);
}

inline class MephMenuImp * MephMenuSingleton::getMephMenuImp()
{
  #if defined(linux)
	  return(new class MephMenuImp_X11);
	#endif
}

#endif