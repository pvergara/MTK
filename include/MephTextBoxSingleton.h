#ifndef MephTextBoxSingleton_h
#define MephTextBoxSingleton_h 1

#if defined (linux)
  #include "MephTextBoxImp_X11.h"
#endif

class MephTextBoxSingleton
{
  public:
		class MephTextBoxImp * getMephTextBoxImp();
		static MephTextBoxSingleton * getMephTextBoxSingleton();
	
	private:
	  static MephTextBoxSingleton * mephtextboxsingleton;
	friend class MephTextBox;
	
};

inline MephTextBoxSingleton * MephTextBoxSingleton::getMephTextBoxSingleton()
{
  if (mephtextboxsingleton==0)
		mephtextboxsingleton=new MephTextBoxSingleton;
	
	return (mephtextboxsingleton);
}

inline class MephTextBoxImp * MephTextBoxSingleton::getMephTextBoxImp()
{
  #if defined(linux)
	  return(new class MephTextBoxImp_X11);
	#endif
}

#endif