#ifndef MephListBox_h
#define MephListBox_h 1

#include "MephItem.h"
#include "MephScrollBar.h"
#include "MephListBoxImp.h"
#include "MephListBoxSingleton.h"
#include "MephVisObj.h"
#include <map.h>

#define LISTBOXITEMHEIGHT 15

class MephListBox: public MephVisObj
{
  public:
	  MephListBox(class MephApp const * mephapp);
	  ~MephListBox();
	
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephListBoxImp * getMephListBoxImp();
	
		void Change(class MephScrollBar *mephscrollbar);
    void Paint(class MephItem *mephitem,int x,int y,int width,int height,int count);
	  void MouseDown(class MephItem * mephitem,int x,int y,unsigned int mephbutton);
	  void KeyDown(class MephItem * mephitem,char *mephchar,int mephkeysymbol,unsigned int mephkeymask);
    void Paint(class MephItem *mephitem);
	  void addItem (void);
	  void addItem(char * text);
	  void addImageItem(char * imagepath);
	  void addItem(unsigned short red,unsigned short green,unsigned short blue);
	  void addDoubleItem(char * text,char * imagepath);

	  void deleteItem(int index);
	  void deleteItems();
		
		const class MephItem *getItem(int index);
		map <int,class MephItem *>getItems();
		const class MephItem *getSelected();
		
		int count();
	
	  void setItemText(char * text,int index,char * result);
	  void setItemImage(char * imagepath,int index,char * result);
	
	  class MephItem * getItem(void) const;
	
	  char removeItem(int index);
	  void clearItems();
	
	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void hide ();

		void (*catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void);


  private:
	  void refreshPositions(void);
	  map <int,class MephItem *> items;
		class MephScrollBar *mephscrollbar;
		class MephItem * selected;
		int firstitem;
		int nitems;

		void (*neweventchange) (class MephItem *mephitem);

    class MephApp const * mephapp;
    class MephListBoxSingleton *mephlistboxsingleton;
	  class MephListBoxImp *mephlistboximp;	
};

#endif