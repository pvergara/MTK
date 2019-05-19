#ifndef MephCheckButton_h
#define MephCheckButton_h 1

#include "MephVisObj.h"
#include "MephCheckButtonImp.h"
#include "MephCheckButtonSingleton.h"

class MephCheckButton: public MephVisObj
{
  public:
	  MephCheckButton(class MephApp const * mephapp);
	  ~MephCheckButton();

          void check(void);
          void uncheck(void);
          void check2(void);
          void setTwoStates(void);
          void setThreeStates(void);
          char getState(void);
          char getStates(void);
	
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephCheckButtonImp * getMephCheckButtonImp();
	
	  void notify(char state);

	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();
	
		char setTabIndex(MephTabIndex tabindex);

		/*como diría alguien que yo me sé...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	  char state;
	  char states;
	  class MephCheckButtonImp *mephcheckbuttonimp;	
	  class MephCheckButtonSingleton *mephcheckbuttonsingleton;
};

#endif