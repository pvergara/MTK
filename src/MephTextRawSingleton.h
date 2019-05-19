#ifndef MephTextRawSingleton_h
#define MephTextRawSingleton_h 1

#if defined (linux)
  #include "MephTextRawImp_X11.h"
#endif

class MephTextRawSingleton
{
  public:
		class MephTextRawImp * getMephTextRawImp();
		static MephTextRawSingleton * getMephTextRawSingleton();
	
	private:
	  static MephTextRawSingleton * mephtextrawsingleton;
	friend class MephTextRaw;
	
};

inline class MephTextRawSingleton * MephTextRawSingleton::getMephTextRawSingleton()
{
  if (mephtextrawsingleton==0)
		mephtextrawsingleton=new MephTextRawSingleton;
	
	return (mephtextrawsingleton);
}

inline class MephTextRawImp * MephTextRawSingleton::getMephTextRawImp()
{
  #if defined(linux)
	  return(new class MephTextRawImp_X11);
	#endif
}

#endif