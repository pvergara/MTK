#ifndef MephListBoxSingleton_h
#define MephListBoxSingleton_h 1

#if defined (linux)
  #include "MephListBoxImp_X11.h"
#endif

class MephListBoxSingleton
{
  public:
		class MephListBoxImp * getMephListBoxImp();
		static MephListBoxSingleton * getMephListBoxSingleton();
	
	private:
	  static MephListBoxSingleton * mephlistboxsingleton;
	friend class MephListBox;
	
};

inline MephListBoxSingleton * MephListBoxSingleton::getMephListBoxSingleton()
{
  if (mephlistboxsingleton==0)
		mephlistboxsingleton=new MephListBoxSingleton;
	
	return (mephlistboxsingleton);
}

inline class MephListBoxImp * MephListBoxSingleton::getMephListBoxImp()
{
  #if defined(linux)
	  return(new class MephListBoxImp_X11);
	#endif
}

#endif