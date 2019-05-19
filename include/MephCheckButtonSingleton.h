#ifndef MephCheckButtonSingleton_h
#define MephCheckButtonSingleton_h 1
#if defined (linux)
  #include "MephCheckButtonImp_X11.h"
#endif
class MephCheckButtonSingleton
{
  public:
		class MephCheckButtonImp * getMephCheckButtonImp();
		static MephCheckButtonSingleton * getMephCheckButtonSingleton();
  private:
	  static MephCheckButtonSingleton * mephcheckbuttonsingleton;
	friend class MephCheckButton;
	
};

inline MephCheckButtonSingleton * MephCheckButtonSingleton::getMephCheckButtonSingleton()
{
  if (mephcheckbuttonsingleton==0)
		mephcheckbuttonsingleton=new MephCheckButtonSingleton;
	
	return (mephcheckbuttonsingleton);
}

inline class MephCheckButtonImp * MephCheckButtonSingleton::getMephCheckButtonImp()
{
  #if defined(linux)
	  return(new class MephCheckButtonImp_X11);
	#endif
}

#endif