#ifndef MephCheckButtonImp_X11_h
#define MephCheckButtonImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephCheckButtonImp.h"
#include "MephWindowImp.h"

/*CUIDADO CON ESTA HERENCIA QUIZµS SE ACABE CREANDO UN MEPHBUTTONIMP_X11*/
class MephCheckButtonImp_X11:public MephCheckButtonImp, public MephVisObjImp_X11
{
	public:
	  MephCheckButtonImp_X11();
    ~MephCheckButtonImp_X11();
	  void initValues(const class MephCheckButton *mephcheckbutton);
    void initValues(const class MephCheckButton *mephcheckbutton, class MephAppImp const *mephappimp);
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
		void (*catchEventMouseDown (void (*eventmousedown)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	
	  class MephCheckButton * mephcheckbutton;
	  class MephWindowImp *mephwindowimp;
	
		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephCheckButton *mephcheckbutton,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephCheckButton *mephcheckbutton,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephCheckButton *mephcheckbutton,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephCheckButton *mephcheckbutton,int x,int y,int width,int height,int count);

		void (*neweventconfigure) (class MephCheckButton *mephcheckbutton,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephCheckButton *mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephCheckButton *mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif