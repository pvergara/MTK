#ifndef MephItemImp_X11_h
#define MephItemImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephVisObj.h"
#include "MephItemImp.h"

class MephListBox;
class MephFloatingWindow;
class MephMenu;

class MephItemImp_X11:public MephItemImp, public MephVisObjImp_X11
{
	public:
	  MephItemImp_X11();
    ~MephItemImp_X11();
    void initValues(const class MephItem *mephitem, class MephAppImp const *mephappimp);
    void initValues(const class MephVisObjImp * mephvisobjimp);

		void update(MephUpdateParam mephupdateparam);

	
    void recieveEvent(XEvent event);
	  void recieveNoMotion();
    const Display * getDisplay();
  	Window getWindow();
		Window getWindow(int index,char *result);
		map <int,Window> getWindows();

		int getHeight();
		int getWidth();

		/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseDown (void (MephListBox::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephListBox *mephlistbox)) (void);
		void (*catchEventMouseDown (void (MephMenu::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephmenu),class MephMenu *mephmenu)) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count))) (void);
		void (*catchEventPaint (void (MephListBox::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephListBox *mephlistbox)) (void);
		void (*catchEventPaint (void (MephFloatingWindow::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephFloatingWindow *mephfloatingwindow)) (void);
		void (*catchEventPaint (void (MephMenu::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephMenu *mephmenu)) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephItem * mephitem,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyDown (void (MephListBox::*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask),class MephListBox *mephlistbox)) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		/***********************************************************************************************/

		/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
    void undoEventMouseDown (void);
    void undoEventMouseUp (void);
    void undoEventMouseOver (void);

    void undoEventPaint (void);

		void undoEventConfigure (void);

	  void undoEventKeyDown (void);
	  void undoEventKeyUp (void);
	  /***********************************************************************************************/
		

  private:
	  void drawButtonDecoration();
	
	
	  class MephItem * mephitem;
	  class MephVisObjImp *mephvisobjimp;
    class MephListBox *mephlistbox;
    class MephFloatingWindow *mephfloatingwindow;
    class MephMenu *mephmenu;
 
		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephItem *mephitem,int x,int y,unsigned int mephbutton);
		void (MephListBox::*neweventmousedowntomephlistbox) (class MephItem *mephitem,int x,int y,unsigned int mephbutton);
		void (MephMenu::*neweventmousedowntomephmenu) (class MephItem *mephitem,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephItem *mephitem,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephItem *mephitem,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephItem *mephitem,int x,int y,int width,int height,int count);
		void (MephListBox::*neweventpainttomephlistbox) (class MephItem *mephitem,int x,int y,int width,int height,int count);
		void (MephFloatingWindow::*neweventpainttomephfloatingwindow) (class MephItem *mephitem,int x,int y,int width,int height,int count);
		void (MephMenu::*neweventpainttomephmenu) (class MephItem *mephitem,int x,int y,int width,int height,int count);

		void (*neweventconfigure) (class MephItem *mephitem,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephItem *mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (MephListBox::*neweventkeydowntomephlistbox) (class MephItem *mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephItem *mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif
