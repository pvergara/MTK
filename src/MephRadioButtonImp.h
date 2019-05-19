#ifndef MephRadioButtonImp_h
#define MephRadioButtonImp_h 1

#include "MephWindowImp.h"
#include "MephVisObjImp.h"

class MephRadioButtonImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephRadioButton *mephradiobutton){};
    virtual void initValues(const class MephRadioButton *mephradiobutton, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephWindowImp * mephwindowimp){};

    virtual void drawButtonDecoration(){};

		virtual void update(MephUpdateParam mephupdateparam){};
		virtual char setTabIndex(MephTabIndex tabindex){};

		/***************************************MêTODOS DE EVENTOS**************************************/
		virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void){};
		
		virtual void (*catchEventPaint (void (*eventpaint)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height,int count))) (void){};
				
		virtual void (*catchEventConfigure (void (*eventconfigure)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height))) (void){};

		virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
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