#ifndef MephComboBoxImp_h
#define MephComboBoxImp_h 

#include "MephWindowImp.h"
#include "MephVisObjImp.h"

class MephComboBoxImp:public MephVisObjImp
{
  public:
    virtual void initValues(const class MephComboBox *mephcombobox){};
    virtual void initValues(const class MephComboBox *mephcombobox, class MephAppImp const *mephappimp){};
    virtual void initValues(const class MephWindowImp * mephwindowimp){};

		/*************************/
		virtual void initValues(const class MephPanelImp * mephpanelimp){};
		/*************************/

		virtual void update(MephUpdateParam mephupdateparam){};
		virtual char setTabIndex(MephTabIndex tabindex){};

		/***************************************MêTODOS DE EVENTOS**************************************/
		virtual void (*catchEventMouseDown (void (*eventmousedown)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseUp (void (*eventmouseup)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void){};
		virtual void (*catchEventMouseOver (void (*eventmouseover)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void){};
		
		virtual void (*catchEventPaint (void (*eventpaint)(class MephComboBox * mephcombobox,int x,int y,int width,int height,int count))) (void){};
				
		virtual void (*catchEventConfigure (void (*eventconfigure)(class MephComboBox * mephcombobox,int x,int y,int width,int height))) (void){};

		virtual void (*catchEventKeyDown (void (*eventkeydown)(class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
		virtual void (*catchEventKeyUp   (void (*eventkeyup)  (class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void){};
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