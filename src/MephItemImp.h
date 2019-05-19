#ifndef MephItemImp_h
#define MephItemImp_h 

#include "MephVisObjImp.h"
#include "MephVisObj.h"

class MephListBox;
class MephFloatingWindow;
class MephMenu;

class MephItemImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephItem *mephitem, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephVisObjImp * mephvisobjimp){};

		virtual void update(MephUpdateParam mephupdateparam){};

		/***************************************MêTODOS DE EVENTOS**************************************/
		virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseDown (void (MephListBox::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephListBox *mephlistbox)) (void){};
		virtual void (*catchEventMouseDown (void (MephMenu::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephMenu *mephmenu)) (void){};
		virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void){};
		
		virtual void (*catchEventPaint (void (*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count))) (void){};
		virtual void (*catchEventPaint (void (MephListBox::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephListBox *mephlistbox)) (void){};
		virtual void (*catchEventPaint (void (MephFloatingWindow::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephFloatingWindow *mephfloatingwindow)) (void){};
		virtual void (*catchEventPaint (void (MephMenu::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephMenu *mephmenu)) (void){};
 				
		virtual void (*catchEventConfigure (void (*eventconfigure)(class MephItem * mephitem,int x,int y,int width,int height))) (void){};

		virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		virtual void (*catchEventKeyDown (void (MephListBox::*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask),class MephListBox *mephlistbox)) (void){};
		virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		/***********************************************************************************************/
		/*****************************************BORRADO DE EVENTOS**************************************/
     virtual void undoEventMouseDown (void){};
     virtual void undoEventMouseUp (void){};
     virtual void undoEventMouseOver (void){};

		virtual void undoEventPaint (void){};

		virtual void undoEventConfigure (void){};

		virtual void undoEventKeyDown (void){};
		virtual void undoEventKeyUp (void){};
		/*************************************************************************************************/
};

#endif