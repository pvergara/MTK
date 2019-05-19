#ifndef MephItem_h
#define MephItem_h 1

#include "MephItemImp.h"
#include "MephItemSingleton.h"
#include "MephVisObj.h"

class MephListBox;
class MephFloatingWindow;
class MephMenu;

class MephItem: public MephVisObj
{
  public:
	  MephItem(class MephApp const * mephapp);
	  ~MephItem();
	
	  void addTo(const class MephVisObjImp * mephvisobjimp);
	  const class MephItemImp * getMephItemImp();
	
	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();
	
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseDown (void (MephListBox::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephListBox *mephlistbox)) (void);
		void (*catchEventMouseDown (void (MephMenu::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephMenu *mephmenu)) (void);
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
	
	  class MephItemSingleton *mephitemsingleton;
	  class MephItemImp *mephitemimp;	
};

#endif