#ifndef MephCommandButtonSingleton_h
#define MephCommandButtonSingleton_h 1

#if defined (linux)
  #include "MephCommandButtonImp_X11.h"
#endif

class MephCommandButtonSingleton
{
  public:
		class MephCommandButtonImp * getMephCommandButtonImp();
		static MephCommandButtonSingleton * getMephCommandButtonSingleton();
	
	private:
	  static MephCommandButtonSingleton * mephcommandbuttonsingleton;
	friend class MephCommandButton;
	
};

inline MephCommandButtonSingleton * MephCommandButtonSingleton::getMephCommandButtonSingleton()
{
  if (mephcommandbuttonsingleton==0)
		mephcommandbuttonsingleton=new MephCommandButtonSingleton;
	
	return (mephcommandbuttonsingleton);
}

inline class MephCommandButtonImp * MephCommandButtonSingleton::getMephCommandButtonImp()
{
  #if defined(linux)
	  return(new class MephCommandButtonImp_X11);
	#endif
}

#endif