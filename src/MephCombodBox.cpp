#include "MephComboBox.h"

#define ComboMinWidth  15
#define ComboMinHeight 15

MephComboBox::MephComboBox(class MephApp const * mephapp):pressed(NOTPRESSED),moused(NOTMOUSED),mephfloatingwindow(NULL)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->width[0]=50;
  this->height[0]=20;
  this->width[1]=ComboMinWidth;
  this->height[1]=ComboMinHeight;
	

	this->mephcomboboxsingleton=this->mephcomboboxsingleton->getMephComboBoxSingleton();
	this->mephcomboboximp=this->mephcomboboxsingleton->getMephComboBoxImp();
		
	this->mephcomboboximp->initValues((const class MephComboBox *) this,mephapp->getMephAppImp());
  this->mephfloatingwindow=new class MephFloatingWindow(mephapp);
  this->mephfloatingwindow->addTo(this->mephfloatingwindowimp);
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
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->initTextValues(this->mephcomboboximp);
}

const class MephComboBoxImp * MephComboBox::getMephComboBoxImp()
{
  return ((const class MephComboBoxImp *)this->mephcomboboximp);
}

void MephComboBox::notify(char pressed)
{
	this->pressed=pressed;
}

void MephComboBox::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephcomboboximp->update(MephUCoord);
	
}

void MephComboBox::resize (unsigned int width,unsigned int height)
{
  if (width<30)
  {
    width[0]=ComboMinWidth;
    width[1]=ComboMinWidth;
  }

  if (height<15)
  {
    height[0]=ComboMinHeight;
    height[1]=ComboMinHeight;
  }
    
	this->width[0]=width-ComboMinHeight;
	this->height[0]=height;

	this->mephcomboboximp->update(MephUSize);

}

void MephComboBox::moveResize (int x,int y,unsigned int width,unsigned int height)
{
  if (width<30)
  {
    width[0]=ComboMinWidth;
    width[1]=ComboMinWidth;
  }

  if (height<15)
  {
    height[0]=ComboMinHeight;
    height[1]=ComboMinHeight;
  }

	this->x[0]=x;
	this->y[0]=y;

	this->width[0]=width;
	this->height[0]=height;
	
	this->mephcomboboximp->update(MephUSize|MephUCoord);

/*	this->mephpanel->resize(this->width,this->height);
	this->mephpanel->refresh();*/
}

void MephComboBox::show ()
{
	this->visible=1;
  this->mephcomboboximp->update(MephUVisible);
	
//	this->mephpanel->refresh();
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
