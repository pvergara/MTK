#ifndef MephWindowImp_X11_h
#define MephWindowImp_X11_h 1

#include "MephVisObjImp_X11.h"
#include "MephWindowImp.h"
#include "MephPanelImp_X11.h"
#include <stdio.h>
//#include "MephGen.h"

/*NECESARIAS PARA ACTUAR SOBRE LA DECORACI”N DE LAS VENTANAS*/

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)

class MephMenu;

class MephWindowImp_X11 : public MephWindowImp, public MephVisObjImp_X11//,public MephPanelContainerImp_X11
{

  public:
      MephWindowImp_X11();
      MephWindowImp_X11(const MephWindowImp_X11 &right);
      ~MephWindowImp_X11();
      const MephWindowImp_X11 & operator=(const MephWindowImp_X11 &right);
      int operator==(const MephWindowImp_X11 &right) const;
      int operator!=(const MephWindowImp_X11 &right) const;
	
	
	    void initValues(const class MephWindow *mephwindow);
      void initValues(const class MephWindow *mephwindow,class MephAppImp const *mephappimp);
	
	    void update (MephUpdateParam mephupdateparam);
	    void recieveEvent(XEvent event);
	    void recieveNoMotion();

      const Display * getDisplay();
			Window getWindow();
			Window getWindow(int index,char *result);
			map <int,Window> getWindows();
			int getWidth();
			int getHeight();
  		char setTabIndex(MephTabIndex tabindex);
			void end(void);
	
	    const class MephWindowImp *getMephWindowImp();
	
			/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
			void (*catchEventMouseDown (void (*eventmousedown)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);
			void (*catchEventMouseUp (void (*eventmouseup)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);
			void (*catchEventMouseOver (void (*eventmouseover)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);

			void (*catchEventPaint (void (*eventpaint)(class MephWindow * mephwindow,int x,int y,int width,int height,int count))) (void);

			void (*catchEventConfigure (void (*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height))) (void);
			void (*catchEventConfigure (void (MephMenu::*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height),class MephMenu *mephmenu)) (void);

			void (*catchEventKeyDown (void (*eventkeydown)(class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
			void (*catchEventKeyUp   (void (*eventkeyup)  (class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
			/***********************************************************************************************/

			/***************************************MêTODOS DE EVENTOS NUEVOS*******************************/
      void undoEventMouseDown (void);
      void undoEventMouseUp (void);
      void undoEventMouseOver (void);

			void undoEventPaint (void);

			void undoEventConfigure (void);

			void undoEventKeyDown (void);
			void undoEventKeyUp (void);
			/***********************************************************************************************/

  private:
	    class MephWindow *mephwindow;
			class MephMenu *mephmenu;
			
			/*ATRIBUTOS DE EVENTOS NUEVOS*/
			void (*neweventmousedown) (class MephWindow *mephwindow,int x,int y,unsigned int mephbutton);
			void (*neweventmouseup) (class MephWindow *mephwindow,int x,int y,unsigned int mephbutton);
			void (*neweventmouseover) (class MephWindow *mephwindow,int x,int y,unsigned int mephbutton);

			void (*neweventpaint) (class MephWindow *mephwindow,int x,int y,int width,int height,int count);

			void (*neweventconfigure) (class MephWindow *mephwindow,int x,int y,int width,int height);
			void (MephMenu::*neweventconfiguretomephmenu) (class MephWindow *mephwindow,int x,int y,int width,int height);

			void (*neweventkeydown) (class MephWindow *mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
			void (*neweventkeyup)   (class MephWindow *mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask);
};

#endif
