#ifndef MephPanelSingleton_h
#define MephPanelSingleton_h 1

#if defined (linux)
  #include "MephPanelImp_X11.h"
#endif

class MephPanelSingleton
{
  public:
		class MephPanelImp * getMephPanelImp();
		static MephPanelSingleton * getMephPanelSingleton();
	
	private:
	  static MephPanelSingleton * mephpanelsingleton;
	friend class MephPanel;
	
};

inline class MephPanelSingleton * MephPanelSingleton::getMephPanelSingleton()
{
  if (mephpanelsingleton==0)
		mephpanelsingleton=new MephPanelSingleton;
	
	return (mephpanelsingleton);
}

inline class MephPanelImp * MephPanelSingleton::getMephPanelImp()
{
  #if defined(linux)
	  return(new class MephPanelImp_X11);
	#endif
}

#endif