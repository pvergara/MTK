#include "MephComboBox.h"

#define ComboMinWidth  15
#define ComboMinHeight 15

void MephComboBox::Change(class MephItem *mephitem)
{
	this->clearScreen();
	this->setBackground(mephitem->getBackColor());
	if ((mephitem->getImagePath()!=NULL) && (strcmp(mephitem->getImagePath(),"")))
	{
	  this->setBackground((char *)mephitem->getImagePath());
	}
	else
	{
	  this->setBackground("");
	}

	this->setText(mephitem->getText());
	this->mephcomboboximp->update(MephUDecoration);
}


MephComboBox::MephComboBox(class MephApp const * mephapp):pressed(NOTPRESSED),moused(NOTMOUSED),mephfloatingwindow(NULL)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->x[1]=1;
  this->y[1]=1;
  this->width[0]=50;
  this->height[0]=ComboMinHeight;
  this->width[1]=ComboMinWidth;
  this->height[1]=ComboMinHeight;
	

	this->mephcomboboxsingleton=this->mephcomboboxsingleton->getMephComboBoxSingleton();
	this->mephcomboboximp=this->mephcomboboxsingleton->getMephComboBoxImp();
		
	this->mephcomboboximp->initValues((const class MephComboBox *) this,mephapp->getMephAppImp());
  this->mephfloatingwindow=new class MephFloatingWindow(mephapp);
}

MephComboBox::~MephComboBox()
{
  delete mephcomboboximp;
  delete mephfloatingwindow;
}

void MephComboBox::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephcomboboximp->initValues(mephwindowimp);

	this->initDrawValues(this->mephcomboboximp);
	this->setBackground(0xFFFF,0xFFFF,0xFFFF);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF,1);
	this->initTextValues(this->mephcomboboximp);
	this->initImageValues(this->mephcomboboximp);
  this->mephfloatingwindow->addTo(this->mephcomboboximp);
	this->mephfloatingwindow->resize(this->width[0]+this->width[1],105);
	this->mephfloatingwindow->catchEventChange(&(MephComboBox::Change),this);
}

const class MephComboBoxImp * MephComboBox::getMephComboBoxImp()
{
  return ((const class MephComboBoxImp *)this->mephcomboboximp);
}

void MephComboBox::deleteItem(int index)
{
	this->mephfloatingwindow->deleteItem(index);
	if (this->mephfloatingwindow->count()==0)
	{
  	this->setBackground(0xFFFF,0xFFFF,0xFFFF);
		this->setText("");
	}
	else
	{
		this->Change((class MephItem *)this->mephfloatingwindow->getItem(1));
	}
}

void MephComboBox::deleteItems()
{
	this->mephfloatingwindow->deleteItems();
  this->setBackground(0xFFFF,0xFFFF,0xFFFF);
  this->setText("");
}

int MephComboBox::count()
{
	return(this->mephfloatingwindow->count());
}

const class MephItem *MephComboBox::getItem(int index)
{
	return(this->mephfloatingwindow->getItem(index));
}

map <int,class MephItem *>MephComboBox::getItems()
{
	return(this->mephfloatingwindow->getItems());
}

void MephComboBox::addItem(char * text)
{
	/*Si es el primer item que se inserta*/
	if (this->mephfloatingwindow->getFirstItem()==0)
		this->setText(text);
	this->mephfloatingwindow->addItem(text);
}

void MephComboBox::addImageItem(char * imagepath)
{
	/*Si es el primer item que se inserta*/
	if (this->mephfloatingwindow->getFirstItem()==0)
		this->setBackground(imagepath);
	this->mephfloatingwindow->addImageItem(imagepath);
}

void MephComboBox::addItem(unsigned short red,unsigned short green,unsigned short blue)
{
	/*Si es el primer item que se inserta*/
	if (this->mephfloatingwindow->getFirstItem()==0)
		this->setBackground(red,green,blue);
	this->mephfloatingwindow->addItem(red,green,blue);
}

void MephComboBox::addDoubleItem(char * text,char * imagepath)
{
	/*Si es el primer item que se inserta*/
	if (this->mephfloatingwindow->getFirstItem()==0)
	{
		this->setText(text);
		this->setBackground(imagepath);
	}
	this->mephfloatingwindow->addDoubleItem(text,imagepath);
}

void MephComboBox::notify(char pressed)
{
	this->pressed=pressed;
}

void MephComboBox::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->x[1]=this->x[0]+this->width[0];
	this->y[1]=this->y[0];
	this->mephcomboboximp->update(MephUCoord);	
	this->mephfloatingwindow->move(this->x[0],this->height[0]);
}

void MephComboBox::resize (unsigned int width,unsigned int height)
{
  if (width<30)
  {
    this->width[0]=ComboMinWidth;
    this->width[1]=ComboMinWidth;
  }

  if (height<15)
  {
    this->height[0]=ComboMinHeight;
    this->height[1]=ComboMinHeight;
  }
    
	this->width[0]=width-ComboMinHeight;
	this->height[0]=height;

	this->mephcomboboximp->update(MephUSize);
	this->mephfloatingwindow->resize(this->width[0]+this->width[1],105);
}

void MephComboBox::moveResize (int x,int y,unsigned int width,unsigned int height)
{
  if (width<30)
  {
    this->width[0]=ComboMinWidth;
    this->width[1]=ComboMinWidth;
  }

  if (height<15)
  {
    this->height[0]=ComboMinHeight;
    this->height[1]=ComboMinHeight;
  }

	this->x[0]=x;
	this->y[0]=y;

	this->width[0]=width;
	this->height[0]=height;
	this->x[1]=this->x[0]+this->width[0];
	this->y[1]=this->y[0];
	
	this->mephcomboboximp->update(MephUSize|MephUCoord);
	this->mephfloatingwindow->moveResize(this->x[0],this->height[0],this->width[0]+this->width[1],105);

/*	this->mephpanel->resize(this->width,this->height);
	this->mephpanel->refresh();*/
}

void MephComboBox::show ()
{
	this->visible=1;
  this->mephcomboboximp->update(MephUVisible);
	
//	this->mephpanel->refresh();
}
	
void MephComboBox::showFloatingWindow ()
{
	this->mephfloatingwindow->show();
}

void MephComboBox::hide ()
{
	this->visible=0;
  this->mephcomboboximp->update(MephUVisible);
}
	
char MephComboBox::getPressed()
{
	return (this->pressed);
}

void MephComboBox::setPressed(char pressed)
{
	this->pressed=pressed;
	this->mephcomboboximp->update(MephUPressed);
}

char MephComboBox::getMoused()
{
	return (this->moused);
}

void MephComboBox::setMoused(char moused)
{
	this->moused=moused;
	this->mephcomboboximp->update(MephUMoused);
}

char MephComboBox::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephcomboboximp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephComboBox::catchEventMouseDown (void (*eventmousedown)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcomboboximp->catchEventMouseDown(eventmousedown));
}

void (*MephComboBox::catchEventMouseUp (void (*eventmouseup)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcomboboximp->catchEventMouseUp(eventmouseup));
}

void (*MephComboBox::catchEventMouseOver (void (*eventmouseover)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcomboboximp->catchEventMouseOver(eventmouseover));
}

void (*MephComboBox::catchEventPaint (void (*eventpaint)(class MephComboBox * mephcombobox,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephcomboboximp->catchEventPaint(eventpaint));
}

void (*MephComboBox::catchEventConfigure (void (*eventconfigure)(class MephComboBox * mephcombobox,int x,int y,int width,int height))) (void)
{
	return(this->mephcomboboximp->catchEventConfigure(eventconfigure));
}

void (*MephComboBox::catchEventKeyDown (void (*eventkeydown)(class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcomboboximp->catchEventKeyDown(eventkeydown));
}

void (*MephComboBox::catchEventKeyUp   (void (*eventkeyup)  (class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcomboboximp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephComboBox::undoEventMouseDown()
{
	this->mephcomboboximp->undoEventMouseDown();
}

void MephComboBox::undoEventMouseUp()
{
	this->mephcomboboximp->undoEventMouseUp();
}

void MephComboBox::undoEventMouseOver()
{
	this->mephcomboboximp->undoEventMouseOver();
}

void MephComboBox::undoEventPaint()
{
	this->mephcomboboximp->undoEventPaint();
}

void MephComboBox::undoEventConfigure()
{
	this->mephcomboboximp->undoEventConfigure();
}


void MephComboBox::undoEventKeyDown()
{
	this->mephcomboboximp->undoEventKeyDown();
}

void MephComboBox::undoEventKeyUp()
{
	this->mephcomboboximp->undoEventKeyUp();
}
/**************************************************************************/
