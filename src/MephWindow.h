#ifndef MephWindow_h
#define MephWindow_h 1

#include "MephVisObj.h"
#include "MephWindowSingleton.h"
#include "MephWindowImp.h"


/*TIENEN LOS MISMOS VALORES QUE LOS ESTµNDARES DE MOTIF PARA DECORACIÓN QUIZµS ALGUNA DE ESTAS
CONSTANTES NO SEA USADA EN OTRO SISTEMA OPERATIVO*/

#define MEPH_DECOR_ALL           (1L << 0)
#define MEPH_DECOR_BORDER        (1L << 1)
#define MEPH_DECOR_RESIZEH       (1L << 2)
#define MEPH_DECOR_TITLE         (1L << 3)
#define MEPH_DECOR_MENU          (1L << 4)
#define MEPH_DECOR_MINIMIZE      (1L << 5)
#define MEPH_DECOR_MAXIMIZE      (1L << 6)

#define MEPH_DECOR_FUNC_ALL           (1L << 0)
#define MEPH_DECOR_FUNC_BORDER        (1L << 1)
#define MEPH_DECOR_FUNC_RESIZEH       (1L << 2)
#define MEPH_DECOR_FUNC_TITLE         (1L << 3)
#define MEPH_DECOR_FUNC_MENU          (1L << 4)
#define MEPH_DECOR_FUNC_MINIMIZE      (1L << 5)
#define MEPH_DECOR_FUNC_MAXIMIZE      (1L << 6)

class MephMenu;

class MephWindow: public MephVisObj//,public MephPanelContainer
{

  public:
//      MephWindow();
      MephWindow(class MephApp const * mephapp);
      MephWindow(const MephWindow &right);
      ~MephWindow();
      const MephWindow & operator=(const MephWindow &right);
      int operator==(const MephWindow &right) const;
      int operator!=(const MephWindow &right) const;

	    void show();
	    void hide();

			void move(int x,int y);
	    void resize(int width,int height);
	    void moveResize(int x,int y,unsigned int width,unsigned int height);
	    void notify(int x,int y,unsigned int width, unsigned int height);
	
	    void notify(char visible);
	
	    void end(void);

		  char setTabIndex(MephTabIndex tabindex);

      void setDecoration(unsigned char decoration);
	    void setDecorationFunction(unsigned char decorationfunction);
	    void setTitle(const char * title);

			int getMinWidth();
			int getMinHeight();
			int getMaxWidth();
			int getMaxHeight();
			unsigned char getDecoration();
			unsigned char getDecorationFunction() ;
			char const * getTitle();

			/*como diría alguien que yo me s‚...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
			/*****************************FUNCIONES DE LOS EVENTOS*********************/
			void (*catchEventMouseDown (void (*eventmousedown)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);
			void (*catchEventMouseUp (void (*eventmouseup)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);
			void (*catchEventMouseOver (void (*eventmouseover)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void);

			void (*catchEventPaint (void (*eventpaint)(class MephWindow * mephwindow,int x,int y,int width,int height,int count))) (void);

			void (*catchEventConfigure (void (*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height))) (void);
			void (*catchEventConfigure (void (MephMenu::*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height),class MephMenu *mephmenu)) (void);

			void (*catchEventKeyDown (void (*eventkeydown)(class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
			void (*catchEventKeyUp   (void (*eventkeyup)  (class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
			const class MephWindowImp * getMephWindowImp();
	
  private:
      char *title;
	    int minwidth;
	    int minheight;
	    int maxwidth;
	    int maxheight;
	    unsigned char decoration;
			unsigned char decorationfunction;

      class MephWindowImp *mephwindowimp;
      class MephWindowSingleton *mephwindowsingleton;
};
#endif
