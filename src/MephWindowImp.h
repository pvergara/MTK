#ifndef MephWindowImp_h
#define MephWindowImp_h 1

#include "MephGen.h"
//#include "MephPanelContainerImp.h"
#include "MephVisObjImp.h"

class MephMenu;

class MephWindowImp:public MephVisObjImp//,public MephPanelContainerImp
{

  public:
      MephWindowImp();
      MephWindowImp(const MephWindowImp &right);
      ~MephWindowImp();
      const MephWindowImp & operator=(const MephWindowImp &right);
      int operator==(const MephWindowImp &right) const;
      int operator!=(const MephWindowImp &right) const;

      virtual void initValues(const class MephWindow *mephwindow){};
      virtual void initValues(const class MephWindow *mephwindow,class MephAppImp const *mephappimp){};

			virtual void update (MephUpdateParam mephupdateparam){};
  		virtual char setTabIndex(MephTabIndex tabindex){};
			virtual void end(void){};
			/***************************************MêTODOS DE EVENTOS**************************************/
			virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
			virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
			virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void){};
			
			virtual void (*catchEventPaint (void (*eventpaint)(class MephWindow * mephwindow,int x,int y,int width,int height,int count))) (void){};
				
			virtual void (*catchEventConfigure (void (*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height))) (void){};
			virtual void (*catchEventConfigure (void (MephMenu::*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height),class MephMenu *mephmenu)) (void){};

			virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
			virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
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
