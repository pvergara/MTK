#ifndef MephTextBox_h
#define MephTextBox_h 1

#include "MephButton.h"
#include "MephTextBoxImp.h"
#include "MephTextBoxSingleton.h"

#define NOTPRESSED 0
#define PRESSED    1

#define NOTMOUSED 0
#define MOUSED    1

class MephTextBox: public MephButton
{
  public:
//	  MephTextBox();
	  MephTextBox(class MephApp const * mephapp);
	  ~MephTextBox();
	
    /*YAAA LOOO SEEE FRAANN... QUE PARA ESTAS COSAS ESTµN LOS CONSTRUCTOR...PERO...CREO
	  QUE TENGO MIS MOTIVOS PARA HACERLOS ASÍ, AUNQUE NO TE PREOCUPES... YA DISCUTIREMOS ESTO*/
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephTextBoxImp * getMephTextBoxImp();
	
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
		void (*catchEventMouseDown (void (*eventmousedown)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephTextBox * mephtextbox,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephTextBox * mephtextbox,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	  class MephTextBoxSingleton *mephtextboxsingleton;
	  class MephTextBoxImp *mephtextboximp;	
};

#endif