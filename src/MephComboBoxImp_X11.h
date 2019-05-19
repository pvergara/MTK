#ifndef MephComboBoxImp_X11_h
#define MephComboBoxImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephPanelImp_X11.h"
#include "MephComboBoxImp.h"
#include "MephWindowImp.h"

/*CUIDADO CON ESTA HERENCIA QUIZµS SE ACABE CREANDO UN MEPHBUTTONIMP_X11*/
class MephComboBoxImp_X11:public MephComboBoxImp, public MephVisObjImp_X11//,public MephPanelContainerImp_X11
{
	public:
	  MephComboBoxImp_X11();
    ~MephComboBoxImp_X11();
	  void initValues(const class MephComboBox *mephcombobox);
    void initValues(const class MephComboBox *mephcombobox, class MephAppImp const *mephappimp);
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
		void (*catchEventMouseDown (void (*eventmousedown)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephComboBox * mephcombobox,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephComboBox * mephcombobox,int x,int y,int width,int height))) (void);

    void (*catchEventKeyDown (void (*eventkeydown)(class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	
	
	  class MephComboBox * mephcombobox;
	  class MephWindowImp *mephwindowimp;
	
		/*ATRIBUTOS DE EVENTOS NUEVOS*/
		void (*neweventmousedown) (class MephComboBox *mephcombobox,int x,int y,unsigned int mephbutton);
		void (*neweventmouseup) (class MephComboBox *mephcombobox,int x,int y,unsigned int mephbutton);
		void (*neweventmouseover) (class MephComboBox *mephcombobox,int x,int y,unsigned int mephbutton);

		void (*neweventpaint) (class MephComboBox *mephcombobox,int x,int y,int width,int height,int count);

		void (*neweventconfigure) (class MephComboBox *mephcombobox,int x,int y,int width,int height);

		void (*neweventkeydown) (class MephComboBox *mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
		void (*neweventkeyup)   (class MephComboBox *mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif
