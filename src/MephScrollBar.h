#ifndef MephScrollBar_h
#define MephScrollBar_h 1

#include "MephVisObj.h"
#include "MephScrollBarImp.h"
#include "MephScrollBarSingleton.h"
#include "MephVisObj.h"

#define HORIZONTAL    0
#define VERTICAL      1

class MephListBox;

class MephScrollBar: public MephVisObj
{
  public:
	  MephScrollBar(class MephApp const * mephapp);
	  ~MephScrollBar();

	  void addTo(const class MephVisObjImp * mephvisobjimp);
	  const class MephScrollBarImp * getMephScrollBarImp();

	  void notify(int interval);

	  int getMin(void);
		int getMax(void);
		int getMinInterval(void);
		int getMaxInterval(void);
		long getScrollPosition(void);
		char getOrientation(void);
 
	  void setMin(int min);
		void setMax(int max);
		void setMinInterval(int mininterval);
		void setMaxInterval(int maxinterval);
		void putScrollPosition(long scrollposition);
		void setScrollPosition(long scrollposition);
		void setOrientation(char orientation);
		
		void setX(int x,int index);
		void setY(int y,int index);
		void setWidth(unsigned int width,int index);
		void setHeight(unsigned int height,int index);
 
	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();

		char setTabIndex(MephTabIndex tabindex);

		/*como diría alguien que yo me s‚...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height,int count))) (void);

//		void (*catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar))) (void);
		void (*catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar),class MephListBox * mephlistbox)) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
	
	  void updatePositions(void);

	  int min;
		int max;
		int mininterval;
		int maxinterval;
		long scrollposition;
		char orientation;

    class MephScrollBarSingleton *mephscrollbarsingleton;
	  class MephScrollBarImp *mephscrollbarimp;	
};

#endif
