#ifndef MephRadioButtonImp_X11_h
#define MephRadioButtonImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephRadioButtonImp.h"
#include "MephWindowImp.h"

/*CUIDADO CON ESTA HERENCIA QUIZµS SE ACABE CREANDO UN MEPHBUTTONIMP_X11*/
class MephRadioButtonImp_X11:public MephRadioButtonImp, public MephVisObjImp_X11
{
	public:
	  MephRadioButtonImp_X11();
    ~MephRadioButtonImp_X11();
	  void initValues(const class MephRadioButton *mephradiobutton);
    void initValues(const class MephRadioButton *mephradiobutton, class MephAppImp const *mephappimp);
    void initValues(const class MephWindowImp * mephwindowimp);

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
		void (*catchEventMouseDown (void (*eventmousedown)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	
	  class MephRadioButton * mephradiobutton;
	  class MephWindowImp *mephwindowimp;
	
		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephRadioButton *mephradiobutton,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephRadioButton *mephradiobutton,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephRadioButton *mephradiobutton,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephRadioButton *mephradiobutton,int x,int y,int width,int height,int count);

		void (*neweventconfigure) (class MephRadioButton *mephradiobutton,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephRadioButton *mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephRadioButton *mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif