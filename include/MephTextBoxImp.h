#ifndef MephTextBoxImp_h
#define MephTextBoxImp_h 

//#include "MephPanelContainerImp.h"
#include "MephWindowImp.h"
#include "MephVisObjImp.h"

class MephTextBoxImp:public MephVisObjImp//,public MephPanelContainerImp
{
  public:
    virtual void initValues(const class MephTextBox *mephtextbox){};
    virtual void initValues(const class MephTextBox *mephtextbox, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephWindowImp * mephwindowimp){};

		/*************************/
		virtual void initValues(const class MephPanelImp * mephpanelimp){};
		/*************************/

		virtual void update(MephUpdateParam mephupdateparam){};
		virtual char setTabIndex(MephTabIndex tabindex){};

		/***************************************MêTODOS DE EVENTOS**************************************/
		virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
		
		virtual void (*catchEventPaint (void (*eventpaint)(class MephTextBox * mephwindow,int x,int y,int width,int height,int count))) (void){};
				
		virtual void (*catchEventConfigure (void (*eventconfigure)(class MephTextBox * mephwindow,int x,int y,int width,int height))) (void){};

		virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephTextBox * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephTextBox * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
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