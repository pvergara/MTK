#ifndef MephItemSingleton_h
#define MephItemSingleton_h 1

#if defined (linux)
  #include "MephItemImp_X11.h"
#endif

class MephItemSingleton
{
  public:
		class MephItemImp * getMephItemImp();
		static MephItemSingleton * getMephItemSingleton();
	
	private:
	  static MephItemSingleton * mephitemsingleton;
	friend class MephItem;
	
};

inline MephItemSingleton * MephItemSingleton::getMephItemSingleton()
{
  if (mephitemsingleton==0)
		mephitemsingleton=new MephItemSingleton;
	
	return (mephitemsingleton);
}

inline class MephItemImp * MephItemSingleton::getMephItemImp()
{
  #if defined(linux)
	  return(new class MephItemImp_X11);
	#endif
}

#endif