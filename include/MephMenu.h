#ifndef MephMenu_h
#define MephMenu_h 1

#include "MephMenuImp.h"
#include "MephMenuSingleton.h"
#include "MephVisObj.h"
#include "MephItem.h"
#include "MephFloatingWindow.h"
#include <map.h>

#define MENUITEMHEIGHT 25
#define MENUITEMWIDTH  20

class MephComboBox;

class MephMenu: public MephVisObj
{
  public:
	  MephMenu(class MephApp const * mephapp);
	  ~MephMenu();
	
	  void addTo(const class MephVisObjImp * mephvisobjimp);
	  const class MephMenuImp * getMephMenuImp();

	  void Configure(class MephWindow * mephwindow,int x,int y,int width,int height);
	  void MouseDown(class MephItem * mephitem,int x,int y,unsigned int mephbutton);
	
	  int getFirstItem();
	
/*	  void move (int x,int y);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void resize (unsigned int width,unsigned int height);*/
	  void notify(int y);
	  void notifyKeyUp(void);
	  void notifyKeyDown(void);
	  void notifyKeyLeftRight(char direction);
	  void notifyKeyEnter(void);
	  void notifyPaint(void);
	  void show ();
	  void show (int x,int y);
	  void hide ();

		void refreshPositions(void);
	  void addItem (void);
	  void addItem(char * text);
	  void addImageItem(char * imagepath);
	  void addItem(unsigned short red,unsigned short green,unsigned short blue);
	  void addDoubleItem(char * text,char * imagepath);
	  void addSubOption(char * text,char * index);
	  void addImageSubOption(char * imagepath,char * index);
	  void addSubOption(unsigned short red,unsigned short green,unsigned short blue,char * index);
	  void addDoubleSubOption(char * text,char * imagepath,char * index);
		void deleteItem(int index);
		void deleteItems();
		int count();
		const class MephItem *getItem(int index);
		map <int,class MephItem *>getItems();
	
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephMenu * mephmenu,int x,int y,int width,int height,int count))) (void);
		void (*catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void);

		void (*catchEventChange (void (MephComboBox::*eventchange)(class MephItem * mephitem),class MephComboBox * mephcombobox)) (void);

    void (*catchEventConfigure (void (*eventconfigure)(class MephMenu * mephmenu,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephMenu * mephmenu,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephMenu * mephmenu,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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
		void getIndex(char *index,int *result,char *count);
		void Change(class MephItem *mephitem);

	  map <int,class MephItem *>items;
	  map <class MephItem *,class MephFloatingWindow *>suboptions;
		void (*neweventchange) (class MephItem *mephitem);

    void (MephComboBox::*neweventchangetomephcombobox) (class MephItem *mephitem);
		class MephComboBox * mephcombobox;

    int nitems;
		int firstitem;
		int optionindex;
		MephApp * mephapp;
		MephItem * selected;
		MephVisObjImp * mephvisobjimp;
		unsigned int widthitems;
	
	  class MephMenuSingleton *mephmenusingleton;
	  class MephMenuImp *mephmenuimp;	
};

#endif