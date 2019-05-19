#ifndef MephScrollBarImp_X11_h
#define MephScrollBarImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephPanelImp_X11.h"
#include "MephScrollBarImp.h"
#include "MephWindowImp.h"
#include "MephVisObj.h"

class MephListBox;

class MephScrollBarImp_X11:public MephScrollBarImp, public MephVisObjImp_X11
{
	public:
	  MephScrollBarImp_X11();
    ~MephScrollBarImp_X11();
    void initValues(const class MephScrollBar *mephscrollbar, class MephAppImp const *mephappimp);
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
		char setTabIndex(MephTabIndex tabindex);

		/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height,int count))) (void);

//		void (*catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar))) (void);
		void (*catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar),class MephListBox * mephlistbox)) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		/***********************************************************************************************/

		/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
    void undoEventMouseDown (void);
    void undoEventMouseUp (void);
    void undoEventMouseOver (void);

    void undoEventPaint (void);
    void undoEventChange (void);

		void undoEventConfigure (void);

	  void undoEventKeyDown (void);
	  void undoEventKeyUp (void);
	  /***********************************************************************************************/


  private:
	  void drawDecoration();
    void scroll(XEvent event);
	
	  class MephScrollBar * mephscrollbar;
	  class MephVisObjImp *mephvisobjimp;
		class MephListBox *mephlistbox;

		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephScrollBar *mephscrollbar,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephScrollBar *mephscrollbar,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephScrollBar *mephscrollbar,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephScrollBar *mephscrollbar,int x,int y,int width,int height,int count);
		void (*neweventchange) (class MephScrollBar *mephscrollbar);
		void (MephListBox::*neweventchangetomephlistbox) (class MephScrollBar *mephscrollbar);

		void (*neweventconfigure) (class MephScrollBar *mephscrollbar,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephScrollBar *mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephScrollBar *mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif
