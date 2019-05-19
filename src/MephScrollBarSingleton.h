#ifndef MephScrollBarSingleton_h
#define MephScrollBarSingleton_h 1

#if defined (linux)
  #include "MephScrollBarImp_X11.h"
#endif

class MephScrollBarSingleton
{
  public:
		class MephScrollBarImp * getMephScrollBarImp();
		static MephScrollBarSingleton * getMephScrollBarSingleton();

	private:
	  static MephScrollBarSingleton * mephscrollbarsingleton;
	friend class MephScrollBar;

};

inline MephScrollBarSingleton * MephScrollBarSingleton::getMephScrollBarSingleton()
{
  if (mephscrollbarsingleton==0)
		mephscrollbarsingleton=new MephScrollBarSingleton;

	return (mephscrollbarsingleton);
}

inline class MephScrollBarImp * MephScrollBarSingleton::getMephScrollBarImp()
{
  #if defined(linux)
	  return(new class MephScrollBarImp_X11);
	#endif
}

#endif
