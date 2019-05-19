#ifndef MephMenuImp_X11_h
#define MephMenuImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephVisObj.h"
#include "MephMenuImp.h"

class MephMenuImp_X11:public MephMenuImp, public MephVisObjImp_X11
{
	public:
	  MephMenuImp_X11();
    ~MephMenuImp_X11();
    void initValues(const class MephMenu *mephmenu, class MephAppImp const *mephappimp);
    void initValues(const class MephVisObjImp * mephvisobjimp);

/*    void show(void);
    void show(int x,int y);*/

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
		void drawDecoration(void);
		
	  class MephMenu * mephmenu;
	  class MephVisObjImp *mephvisobjimp;
};

#endif
