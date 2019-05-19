#ifndef MephFloatingWindow_h
#define MephFloatingWindow_h 1

#include "MephFloatingWindowImp.h"
#include "MephFloatingWindowSingleton.h"
#include "MephVisObj.h"
#include "MephItem.h"
#include <map.h>

#define FLOATINGWINDOWITEMHEIGHT 15
#define FLOATINGWINDOWITEMLEFT    0
#define FLOATINGWINDOWITEMRIGHT   1

class MephComboBox;
class MephMenu;

class MephFloatingWindow: public MephVisObj
{
  public:
	  MephFloatingWindow(class MephApp const * mephapp);
	  ~MephFloatingWindow();
	
	  void addTo(const class MephVisObjImp * mephvisobjimp);
	  const class MephFloatingWindowImp * getMephFloatingWindowImp();

	  int getFirstItem();
	
	  void move (int x,int y);
	  /*CUANDO SE PRODUCE EL GRAB DEL FLOATING AVISARµ DE LA COORDENADA X DEEENNNNTRROO DE DICHO FLOATING PARA QUE MEPHFLOATINGWINDOW
	  SEPA A QUê ITEM TIENE QUE "ACCEDER"*/
	  void notify(int y);
	  void notifyKeyUp(void);
	  void notifyKeyDown(void);
	  void notifyKeyRight(void);
	  void notifyKeyLeft (void);
	  void notifyKeyEnter(void);
	  void notifyPaint(void);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void resize (unsigned int width,unsigned int height);
	  void show ();
	  void show (int x,int y);
	  void hide ();

		void refreshPositions(void);
	  void addItem (void);
	  void addItem(char * text);
	  void addImageItem(char * imagepath);
	  void addItem(unsigned short red,unsigned short green,unsigned short blue);
	  void addDoubleItem(char * text,char * imagepath);
		void deleteItem(int index);
		void deleteItems();
		int count();
		const class MephItem *getItem(int index);
		map <int,class MephItem *>getItems();
	
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephFloatingWindow * mephfloatingwindow,int x,int y,int width,int height,int count))) (void);

		void (*catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void);
		void (*catchEventChange (void (MephComboBox::*eventchange)(class MephItem * mephitem),class MephComboBox * mephcombobox)) (void);
		void (*catchEventChange (void (MephMenu::*eventchange)(class MephItem * mephitem),class MephMenu * mephmenu)) (void);
    /*HAY QUE ADMITIR QUE ESTE EVENTO ES UN POCO UN PARCHE PARA QUE EL MENÈ SEPA CUANDO SE VA A LA IZQ O A LA DER*/
    void (*catchEventLeftRight (void (MephMenu::*eventchange)(char direction),class MephMenu * mephmenu)) (void);

    void (*catchEventConfigure (void (*eventconfigure)(class MephFloatingWindow * mephfloatingwindow,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephFloatingWindow * mephfloatingwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephFloatingWindow * mephfloatingwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
    void Paint(class MephItem *mephitem,int x,int y,int width,int height,int count);
    void Paint(class MephItem *mephitem);

	  map <int,class MephItem *>items;
		void (*neweventchange) (class MephItem *mephitem);
    void (MephComboBox::*neweventchangetomephcombobox) (class MephItem *mephitem);
    void (MephMenu::*neweventchangetomephmenu) (class MephItem *mephitem);
    void (MephMenu::*neweventleftrighttomephmenu) (char direction);
		class MephComboBox * mephcombobox;
		class MephMenu * mephmenu;

    int nitems;
		int firstitem;
		MephApp * mephapp;
		MephItem * selected;
	
	  class MephFloatingWindowSingleton *mephfloatingwindowsingleton;
	  class MephFloatingWindowImp *mephfloatingwindowimp;	
};

#endif