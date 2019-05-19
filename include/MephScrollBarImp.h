#ifndef MephScrollBarImp_h
#define MephScrollBarImp_h

#include "MephWindowImp.h"
#include "MephVisObjImp.h"
#include "MephVisObj.h"
//#include "MephListBox.h"

class MephListBox;

class MephScrollBarImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephScrollBar *mephscrollbar, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephVisObjImp * mephvisobjimp){};

		/*************************/
		virtual void initValues(const class MephPanelImp * mephpanelimp){};
		/*************************/

		virtual void update(MephUpdateParam mephupdateparam){};
		virtual char setTabIndex(MephTabIndex tabindex){};

		/***************************************MêTODOS DE EVENTOS**************************************/
		virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void){};

		virtual void (*catchEventPaint (void (*eventpaint)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height,int count))) (void){};

		virtual void (*catchEventChange (void (*eventchange)(class MephScrollBar * mephscrollbar))) (void){};
		virtual void (*catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar),class MephListBox *mephlistbox)) (void){};

		virtual void (*catchEventConfigure (void (*eventconfigure)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height))) (void){};

		virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
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
