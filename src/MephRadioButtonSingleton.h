#ifndef MephRadioButtonSingleton_h
#define MephRadioButtonSingleton_h 1
#if defined (linux)
  #include "MephRadioButtonImp_X11.h"
#endif
class MephRadioButtonSingleton
{
  public:
		class MephRadioButtonImp * getMephRadioButtonImp();
		static MephRadioButtonSingleton * getMephRadioButtonSingleton();
  private:
	  static MephRadioButtonSingleton * mephradiobuttonsingleton;
	friend class MephRadioButton;
	
};

inline MephRadioButtonSingleton * MephRadioButtonSingleton::getMephRadioButtonSingleton()
{
  if (mephradiobuttonsingleton==0)
		mephradiobuttonsingleton=new MephRadioButtonSingleton;
	
	return (mephradiobuttonsingleton);
}

inline class MephRadioButtonImp * MephRadioButtonSingleton::getMephRadioButtonImp()
{
  #if defined(linux)
	  return(new class MephRadioButtonImp_X11);
	#endif
}

#endif