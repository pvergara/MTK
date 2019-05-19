#include "MephTextBox.h"

/*MephTextBox::MephTextBox():pressed(NOTPRESSED),moused(NOTMOUSED)
{
  this->imagemode=(MEPHWINDOWED|MEPHSOLID);
  this->x=1;
  this->y=1;
  this->width=50;
  this->height=20;
	
	this->mephtextboxsingleton=this->mephtextboxsingleton->getMephTextBoxSingleton();
	this->mephtextboximp=this->mephtextboxsingleton->getMephTextBoxImp();
		
	this->mephtextboximp->initValues((const class MephTextBox *) this);
}*/

MephTextBox::MephTextBox(class MephApp const * mephapp):pressed(NOTPRESSED),moused(NOTMOUSED)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->width[0]=50;
  this->height[0]=20;
	
	this->mephtextboxsingleton=this->mephtextboxsingleton->getMephTextBoxSingleton();
	this->mephtextboximp=this->mephtextboxsingleton->getMephTextBoxImp();
		
	this->mephtextboximp->initValues((const class MephTextBox *) this,mephapp->getMephAppImp());
}

MephTextBox::~MephTextBox()
{
  delete mephtextboximp;
}

void MephTextBox::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephtextboximp->initValues(mephwindowimp);

	this->initDrawValues(this->mephtextboximp);
	this->setBackground(0xFFFF,0xFFFF,0xFFFF);
	this->initTextValues(this->mephtextboximp);
	this->setTextY(8);
	this->setTextX(3);
}

const class MephTextBoxImp * MephTextBox::getMephTextBoxImp()
{
  return ((const class MephTextBoxImp *)this->mephtextboximp);
}

void MephTextBox::notify(char pressed)
{
	this->pressed=pressed;
}

void MephTextBox::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephtextboximp->update(MephUCoord);
	
}

void MephTextBox::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephtextboximp->update(MephUSize);

//  this->mephpanel->resize(this->width,this->height);
//	this->mephpanel->refresh();
}

void MephTextBox::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephtextboximp->update(MephUSize|MephUCoord);

/*	this->mephpanel->resize(this->width,this->height);
	this->mephpanel->refresh();*/
}

void MephTextBox::show ()
{
	this->visible=1;
  this->mephtextboximp->update(MephUVisible);
	
//	this->mephpanel->refresh();
}
	
void MephTextBox::hide ()
{
	this->visible=0;
  this->mephtextboximp->update(MephUVisible);
}
	
char MephTextBox::getPressed()
{
	return (this->pressed);
}

void MephTextBox::setPressed(char pressed)
{
	this->pressed=pressed;
	this->mephtextboximp->update(MephUPressed);
}

char MephTextBox::getMoused()
{
	return (this->moused);
}

void MephTextBox::setMoused(char moused)
{
	this->moused=moused;
	this->mephtextboximp->update(MephUMoused);
}

char MephTextBox::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephtextboximp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephTextBox::catchEventMouseDown (void (*eventmousedown)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephtextboximp->catchEventMouseDown(eventmousedown));
}

void (*MephTextBox::catchEventMouseUp (void (*eventmouseup)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephtextboximp->catchEventMouseUp(eventmouseup));
}

void (*MephTextBox::catchEventMouseOver (void (*eventmouseover)(class MephTextBox * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephtextboximp->catchEventMouseOver(eventmouseover));
}

void (*MephTextBox::catchEventPaint (void (*eventpaint)(class MephTextBox * mephwindow,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephtextboximp->catchEventPaint(eventpaint));
}

void (*MephTextBox::catchEventConfigure (void (*eventconfigure)(class MephTextBox * mephwindow,int x,int y,int width,int height))) (void)
{
	return(this->mephtextboximp->catchEventConfigure(eventconfigure));
}

void (*MephTextBox::catchEventKeyDown (void (*eventkeydown)(class MephTextBox * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephtextboximp->catchEventKeyDown(eventkeydown));
}

void (*MephTextBox::catchEventKeyUp   (void (*eventkeyup)  (class MephTextBox * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephtextboximp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephTextBox::undoEventMouseDown()
{
	this->mephtextboximp->undoEventMouseDown();
}

void MephTextBox::undoEventMouseUp()
{
	this->mephtextboximp->undoEventMouseUp();
}

void MephTextBox::undoEventMouseOver()
{
	this->mephtextboximp->undoEventMouseOver();
}

void MephTextBox::undoEventPaint()
{
	this->mephtextboximp->undoEventPaint();
}

void MephTextBox::undoEventConfigure()
{
	this->mephtextboximp->undoEventConfigure();
}


void MephTextBox::undoEventKeyDown()
{
	this->mephtextboximp->undoEventKeyDown();
}

void MephTextBox::undoEventKeyUp()
{
	this->mephtextboximp->undoEventKeyUp();
}
/**************************************************************************/