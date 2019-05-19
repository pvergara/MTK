#ifndef MephFloatingWindowImp_X11_h
#define MephFloatingWindowImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephVisObj.h"
#include "MephFloatingWindowImp.h"

class MephFloatingWindowImp_X11:public MephFloatingWindowImp, public MephVisObjImp_X11
{
	public:
	  MephFloatingWindowImp_X11();
    ~MephFloatingWindowImp_X11();
    void initValues(const class MephFloatingWindow *mephfloatingwindow, class MephAppImp const *mephappimp);
    void initValues(const class MephVisObjImp * mephvisobjimp);

    void show(void);
    void show(int x,int y);

		void update(MephUpdateParam mephupdateparam);
		void recieveEvent(XEvent event);
		void destroyWindow(const class MephItemImp * mephitemipm);

	
    const Display * getDisplay();
  	Window getWindow();
		Window getWindow(int index,char *result);
		map <int,Window> getWindows();

		int getHeight();
		int getWidth();

  private:
		void grabbing(void);
		
	  class MephFloatingWindow * mephfloatingwindow;
	  class MephVisObjImp *mephvisobjimp;
};

#endif
