#ifndef MephCommandButton_h
#define MephCommandButton_h 1

#include "MephButton.h"
#include "MephCommandButtonImp.h"
#include "MephCommandButtonSingleton.h"

#define NOTPRESSED 0
#define PRESSED    1

#define NOTMOUSED 0
#define MOUSED    1

class MephCommandButton: public MephButton
{
  public:
//	  MephCommandButton();
	  MephCommandButton(class MephApp const * mephapp);
	  ~MephCommandButton();
	
    /*YAAA LOOO SEEE FRAANN... QUE PARA ESTAS COSAS ESTµN LOS CONSTRUCTOR...PERO...CREO
	  QUE TENGO MIS MOTIVOS PARA HACERLOS ASÍ, AUNQUE NO TE PREOCUPES... YA DISCUTIREMOS ESTO*/
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephCommandButtonImp * getMephCommandButtonImp();
	
	  void notify(char pressed);

	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();
	
	  char getPressed();
	  void setPressed(char pressed);
	
	  char getMoused();
	  void setMoused(char moused);
		char setTabIndex(MephTabIndex tabindex);

		/*como diría alguien que yo me s‚...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephCommandButton * mephwindow,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephCommandButton * mephwindow,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephCommandButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephCommandButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		/**************************************************************************/

		/*******************************BORRADO DE LOS EVENTOS*********************/
		void undoEventMouseDown();
		void undoEventMouseUp();
		void undoEventMouseOver();

		void undoEventPaint();

    void undoEventConfigure();
		void undoEventKeyDown();
		void undoEventKeyUp();
     /**************************************************************************/
  private:
	
	  char pressed;
	  char moused;
	  class MephCommandButtonSingleton *mephcommandbuttonsingleton;
	  class MephCommandButtonImp *mephcommandbuttonimp;	
};

#endif