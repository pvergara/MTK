#ifndef MephColorSingleton_h
#define MephColorSingleton_h 1

#if defined (linux)
  #include "MephColorImp_X11.h"
#endif

class MephColorSingleton
{
  public:
	  class MephColorImp * getMephColorImp ();
    static MephColorSingleton * getMephColorSingleton ();


  private:
    static MephColorSingleton * mephcolorsingleton;
    friend class MephColor;
};

inline MephColorSingleton *MephColorSingleton::getMephColorSingleton()
{
  if (mephcolorsingleton==0)
		mephcolorsingleton=new MephColorSingleton;
	
	return (mephcolorsingleton);
}

inline class MephColorImp *MephColorSingleton::getMephColorImp()
{
  #if defined(linux)
	  return (new class MephColorImp_X11);
	#endif
}

#endif