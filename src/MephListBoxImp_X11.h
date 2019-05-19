#ifndef MephListBoxImp_X11_h
#define MephListBoxImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephListBoxImp.h"

class MephListBoxImp_X11:public MephListBoxImp, public MephVisObjImp_X11
{
	public:
	  MephListBoxImp_X11();
    ~MephListBoxImp_X11();
    void initValues(const class MephListBox *mephlistbox, class MephAppImp const *mephappimp);
    void initValues(const class MephVisObjImp * mephvisobjimp);
		void destroyWindow(const class MephItemImp * mephitemimp);

		void update(MephUpdateParam mephupdateparam);

	
    const Display * getDisplay();
  	Window getWindow();
		Window getWindow(int index,char *result);
		map <int,Window> getWindows();

		int getHeight();
		int getWidth();

  private:
//	  void drawButtonDecoration();
	
	  class MephListBox * mephlistbox;
	  class MephVisObjImp *mephvisobjimp;
};

#endif
