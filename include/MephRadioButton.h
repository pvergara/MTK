#ifndef MephRadioButton_h
#define MephRadioButton_h 1

#include "MephVisObj.h"
#include "MephRadioButtonImp.h"
#include "MephRadioButtonSingleton.h"

class MephRadioButton: public MephVisObj
{
  public:
	  MephRadioButton(class MephApp const * mephapp);
	  ~MephRadioButton();

    void check(void)
    {
      if (this->mephradiobuttonimp!=NULL)
      {  
    		if (!MephRadioButton::objects[MephRadioButton::group])
    			MephRadioButton::objects[MephRadioButton::group]=this;
    	  else
    			MephRadioButton::objects[MephRadioButton::group]->uncheck();
   			MephRadioButton::objects[MephRadioButton::group]=this;
		    MephRadioButton::state=1;
        MephRadioButton::mephradiobuttonimp->update(MephUPressed);
      }
    }

    void uncheck(void);
    char getState(void);

	  int getGroup(void);
	  void setGroup(int group)
    {
      MephRadioButton::group=group;
      if (!MephRadioButton::objects[MephRadioButton::group])
      {
  			MephRadioButton::objects[group]=this;
        MephRadioButton::state=1;
      }
    	else
        MephRadioButton::state=0;
      MephRadioButton::mephradiobuttonimp->update(MephUPressed);
    }
	
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephRadioButtonImp * getMephRadioButtonImp();
	
	  void notify(char state);

	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();
	
		char setTabIndex(MephTabIndex tabindex);

		/*como diría alguien que yo me sé...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	  int  group;
	  static map <int,MephRadioButton *> objects;
	  class MephRadioButtonImp *mephradiobuttonimp;	
	  class MephRadioButtonSingleton *mephradiobuttonsingleton;
};

#endif