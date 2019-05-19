#ifndef MephComboBox_h
#define MephComboBox_h 1

#include "MephFloatingWindow.h"
#include "MephComboBoxImp.h"
#include "MephComboBoxSingleton.h"
#include "MephItem.h"
#include "MephVisObj.h"

#define NOTPRESSED 0
#define PRESSED    1

#define NOTMOUSED 0
#define MOUSED    1

class MephComboBox:public MephVisObj
{
  public:
//	  MephComboBox();
	  MephComboBox(class MephApp const * mephapp);
	  ~MephComboBox();
	
    /*YAAA LOOO SEEE FRAANN... QUE PARA ESTAS COSAS ESTµN LOS CONSTRUCTOR...PERO...CREO
	  QUE TENGO MIS MOTIVOS PARA HACERLOS ASÍ, AUNQUE NO TE PREOCUPES... YA DISCUTIREMOS ESTO*/
	  void addTo(const class MephWindowImp * mephwindowimp);
	  const class MephComboBoxImp * getMephComboBoxImp();

	  void addItem(char * text);
	  void addImageItem(char * imagepath);
	  void addItem(unsigned short red,unsigned short green,unsigned short blue);
	  void addDoubleItem(char * text,char * imagepath);
	  void deleteItem(int index);
	  void deleteItems();
	  int count();
		const class MephItem *getItem(int index);
		map <int,class MephItem *>getItems();	
	
	  void notify(char pressed);

	  void move (int x,int y);
	  void resize (unsigned int width,unsigned int height);
	  void moveResize (int x,int y,unsigned int width,unsigned int height);
	  void show ();
	  void showFloatingWindow ();	
	  void hide ();
	
	  char getPressed();
	  void setPressed(char pressed);
	
	  char getMoused();
	  void setMoused(char moused);
		char setTabIndex(MephTabIndex tabindex);

		/*como diría alguien que yo me s‚...AGARRENSE LOS MACHOS!!!!...viene la/s:*/
		/*****************************FUNCIONES DE LOS EVENTOS*********************/
		void (*catchEventMouseDown (void (*eventmousedown)(class MephComboBox * combobox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseUp (void (*eventmouseup)(class MephComboBox * combobox,int x,int y,unsigned int mephbutton))) (void);
		void (*catchEventMouseOver (void (*eventmouseover)(class MephComboBox * combobox,int x,int y,unsigned int mephbutton))) (void);

		void (*catchEventPaint (void (*eventpaint)(class MephComboBox * combobox,int x,int y,int width,int height,int count))) (void);

		void (*catchEventConfigure (void (*eventconfigure)(class MephComboBox * combobox,int x,int y,int width,int height))) (void);

		void (*catchEventKeyDown (void (*eventkeydown)(class MephComboBox * combobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
		void (*catchEventKeyUp   (void (*eventkeyup)  (class MephComboBox * combobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void);
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

    void Change(class MephItem *mephitem);

	  char pressed;
	  char moused;
	  class MephFloatingWindow *mephfloatingwindow;
	  class MephComboBoxSingleton *mephcomboboxsingleton;
	  class MephComboBoxImp *mephcomboboximp;	
};

#endif
