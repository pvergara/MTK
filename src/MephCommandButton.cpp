#include "MephCommandButton.h"

/*MephCommandButton::MephCommandButton():pressed(NOTPRESSED),moused(NOTMOUSED)
{
  this->imagemode=(MEPHWINDOWED|MEPHSOLID);
  this->x=1;
  this->y=1;
  this->width=50;
  this->height=20;
	
	this->mephcommandbuttonsingleton=this->mephcommandbuttonsingleton->getMephCommandButtonSingleton();
	this->mephcommandbuttonimp=this->mephcommandbuttonsingleton->getMephCommandButtonImp();
		
	this->mephcommandbuttonimp->initValues((const class MephCommandButton *) this);
}*/

MephCommandButton::MephCommandButton(class MephApp const * mephapp):pressed(NOTPRESSED),moused(NOTMOUSED)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->width[0]=50;
  this->height[0]=20;
	
	this->mephcommandbuttonsingleton=this->mephcommandbuttonsingleton->getMephCommandButtonSingleton();
	this->mephcommandbuttonimp=this->mephcommandbuttonsingleton->getMephCommandButtonImp();
		
	this->mephcommandbuttonimp->initValues((const class MephCommandButton *) this,mephapp->getMephAppImp());
}

MephCommandButton::~MephCommandButton()
{
  delete mephcommandbuttonimp;
}

void MephCommandButton::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephcommandbuttonimp->initValues(mephwindowimp);

	this->initDrawValues(this->mephcommandbuttonimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->initTextValues(this->mephcommandbuttonimp);
}

const class MephCommandButtonImp * MephCommandButton::getMephCommandButtonImp()
{
  return ((const class MephCommandButtonImp *)this->mephcommandbuttonimp);
}

void MephCommandButton::notify(char pressed)
{
	this->pressed=pressed;
}

void MephCommandButton::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephcommandbuttonimp->update(MephUCoord);
	
}

void MephCommandButton::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephcommandbuttonimp->update(MephUSize);

//  this->mephpanel->resize(this->width,this->height);
//	this->mephpanel->refresh();
}

void MephCommandButton::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephcommandbuttonimp->update(MephUSize|MephUCoord);

/*	this->mephpanel->resize(this->width,this->height);
	this->mephpanel->refresh();*/
}

void MephCommandButton::show ()
{
	this->visible=1;
  this->mephcommandbuttonimp->update(MephUVisible);
	
//	this->mephpanel->refresh();
}
	
void MephCommandButton::hide ()
{
	this->visible=0;
  this->mephcommandbuttonimp->update(MephUVisible);
}
	
char MephCommandButton::getPressed()
{
	return (this->pressed);
}

void MephCommandButton::setPressed(char pressed)
{
	this->pressed=pressed;
	this->mephcommandbuttonimp->update(MephUPressed);
}

char MephCommandButton::getMoused()
{
	return (this->moused);
}

void MephCommandButton::setMoused(char moused)
{
	this->moused=moused;
	this->mephcommandbuttonimp->update(MephUMoused);
}

char MephCommandButton::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephcommandbuttonimp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephCommandButton::catchEventMouseDown (void (*eventmousedown)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcommandbuttonimp->catchEventMouseDown(eventmousedown));
}

void (*MephCommandButton::catchEventMouseUp (void (*eventmouseup)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcommandbuttonimp->catchEventMouseUp(eventmouseup));
}

void (*MephCommandButton::catchEventMouseOver (void (*eventmouseover)(class MephCommandButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcommandbuttonimp->catchEventMouseOver(eventmouseover));
}

void (*MephCommandButton::catchEventPaint (void (*eventpaint)(class MephCommandButton * mephwindow,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephcommandbuttonimp->catchEventPaint(eventpaint));
}

void (*MephCommandButton::catchEventConfigure (void (*eventconfigure)(class MephCommandButton * mephwindow,int x,int y,int width,int height))) (void)
{
	return(this->mephcommandbuttonimp->catchEventConfigure(eventconfigure));
}

void (*MephCommandButton::catchEventKeyDown (void (*eventkeydown)(class MephCommandButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcommandbuttonimp->catchEventKeyDown(eventkeydown));
}

void (*MephCommandButton::catchEventKeyUp   (void (*eventkeyup)  (class MephCommandButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcommandbuttonimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephCommandButton::undoEventMouseDown()
{
	this->mephcommandbuttonimp->undoEventMouseDown();
}

void MephCommandButton::undoEventMouseUp()
{
	this->mephcommandbuttonimp->undoEventMouseUp();
}

void MephCommandButton::undoEventMouseOver()
{
	this->mephcommandbuttonimp->undoEventMouseOver();
}

void MephCommandButton::undoEventPaint()
{
	this->mephcommandbuttonimp->undoEventPaint();
}

void MephCommandButton::undoEventConfigure()
{
	this->mephcommandbuttonimp->undoEventConfigure();
}


void MephCommandButton::undoEventKeyDown()
{
	this->mephcommandbuttonimp->undoEventKeyDown();
}

void MephCommandButton::undoEventKeyUp()
{
	this->mephcommandbuttonimp->undoEventKeyUp();
}
/**************************************************************************/