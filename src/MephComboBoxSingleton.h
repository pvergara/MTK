#ifndef MephComboBoxSingleton_h
#define MephComboBoxSingleton_h 1

#if defined (linux)
  #include "MephComboBoxImp_X11.h"
#endif

class MephComboBoxSingleton
{
  public:
		class MephComboBoxImp * getMephComboBoxImp();
		static MephComboBoxSingleton * getMephComboBoxSingleton();
	
	private:
	  static MephComboBoxSingleton * mephcomboboxsingleton;
	friend class MephComboBox;
	
};

inline MephComboBoxSingleton * MephComboBoxSingleton::getMephComboBoxSingleton()
{
  if (mephcomboboxsingleton==0)
		mephcomboboxsingleton=new MephComboBoxSingleton;
	
	return (mephcomboboxsingleton);
}

inline class MephComboBoxImp * MephComboBoxSingleton::getMephComboBoxImp()
{
  #if defined(linux)
	  return(new class MephComboBoxImp_X11);
	#endif
}

#endif