#ifndef MephTextBoxImp_X11_h
#define MephTextBoxImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephPanelImp_X11.h"
#include "MephTextBoxImp.h"
#include "MephWindowImp.h"

/*CUIDADO CON ESTA HERENCIA QUIZµS SE ACABE CREANDO UN MEPHBUTTONIMP_X11*/
class MephTextBoxImp_X11:public MephTextBoxImp, public MephVisObjImp_X11//,public MephPanelContainerImp_X11
{
	public:
	  MephTextBoxImp_X11();
    ~MephTextBoxImp_X11();
	  void initValues(const class MephTextBox *mephtextbox);
    void initValues(const class MephTextBox *mephtextbox, class MephAppImp const *mephappimp);
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
		void (*catchEventMouseDown (void (*eventmousedown)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephTextBox * mephtextbox,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephTextBox * mephtextbox,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
    void writeText(char *keychar,KeySym keysym,unsigned int state);	
	
	  class MephTextBox * mephtextbox;
	  class MephWindowImp *mephwindowimp;
	
		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephTextBox *mephtextbox,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephTextBox *mephtextbox,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephTextBox *mephtextbox,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephTextBox *mephtextbox,int x,int y,int width,int height,int count);

		void (*neweventconfigure) (class MephTextBox *mephtextbox,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephTextBox *mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephTextBox *mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif
