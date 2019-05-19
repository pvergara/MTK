#include "MephCheckButton.h"

MephCheckButton::MephCheckButton(class MephApp const * mephapp):mephcheckbuttonimp(NULL),state(0),states(2)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->width[0]=50;
  this->height[0]=20;
	this->tabindex=0;

	this->mephcheckbuttonsingleton=this->mephcheckbuttonsingleton->getMephCheckButtonSingleton();
	this->mephcheckbuttonimp=this->mephcheckbuttonsingleton->getMephCheckButtonImp();
		
	this->mephcheckbuttonimp->initValues((const class MephCheckButton *) this,mephapp->getMephAppImp());
}

MephCheckButton::~MephCheckButton()
{
  delete mephcheckbuttonimp;
}

void MephCheckButton::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephcheckbuttonimp->initValues(mephwindowimp);

	this->initDrawValues(this->mephcheckbuttonimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->initTextValues(this->mephcheckbuttonimp);
}

const class MephCheckButtonImp * MephCheckButton::getMephCheckButtonImp()
{
  return ((const class MephCheckButtonImp *)this->mephcheckbuttonimp);
}

void MephCheckButton::check(void)
{
  if (this->mephcheckbuttonimp!=NULL)
  {
    this->state=1;
    this->mephcheckbuttonimp->update(MephUPressed);
  }
}

void MephCheckButton::uncheck(void)
{
  if (this->mephcheckbuttonimp!=NULL)
  {
    this->state=0;
    this->mephcheckbuttonimp->update(MephUPressed);
  }
}

void MephCheckButton::check2(void)
{
  if (this->mephcheckbuttonimp!=NULL)
  {
    this->state=2;
    this->mephcheckbuttonimp->update(MephUPressed);
  }
}

void MephCheckButton::setTwoStates(void)
{
  if (this->mephcheckbuttonimp!=NULL)
    this->states=2;
}

void MephCheckButton::setThreeStates(void)
{
  if (this->mephcheckbuttonimp!=NULL)
    this->states=3;
}

char MephCheckButton::getState(void)
{
  if (this->mephcheckbuttonimp!=NULL)
    return(this->state);
}

char MephCheckButton::getStates(void)
{
  if (this->mephcheckbuttonimp!=NULL)
    return(this->states);
}

void MephCheckButton::notify(char state)
{
	this->state=state;
  this->mephcheckbuttonimp->update(MephUPressed);
}

void MephCheckButton::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephcheckbuttonimp->update(MephUCoord);
	
}

void MephCheckButton::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephcheckbuttonimp->update(MephUSize);
}

void MephCheckButton::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephcheckbuttonimp->update(MephUSize|MephUCoord);
}

void MephCheckButton::show ()
{
	this->visible=1;
  this->mephcheckbuttonimp->update(MephUVisible);
}
	
void MephCheckButton::hide ()
{
	this->visible=0;
  this->mephcheckbuttonimp->update(MephUVisible);
}
	
char MephCheckButton::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephcheckbuttonimp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephCheckButton::catchEventMouseDown (void (*eventmousedown)(class MephCheckButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcheckbuttonimp->catchEventMouseDown(eventmousedown));
}

void (*MephCheckButton::catchEventMouseUp (void (*eventmouseup)(class MephCheckButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcheckbuttonimp->catchEventMouseUp(eventmouseup));
}

void (*MephCheckButton::catchEventMouseOver (void (*eventmouseover)(class MephCheckButton * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephcheckbuttonimp->catchEventMouseOver(eventmouseover));
}

void (*MephCheckButton::catchEventPaint (void (*eventpaint)(class MephCheckButton * mephwindow,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephcheckbuttonimp->catchEventPaint(eventpaint));
}

void (*MephCheckButton::catchEventConfigure (void (*eventconfigure)(class MephCheckButton * mephwindow,int x,int y,int width,int height))) (void)
{
	return(this->mephcheckbuttonimp->catchEventConfigure(eventconfigure));
}

void (*MephCheckButton::catchEventKeyDown (void (*eventkeydown)(class MephCheckButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcheckbuttonimp->catchEventKeyDown(eventkeydown));
}

void (*MephCheckButton::catchEventKeyUp   (void (*eventkeyup)  (class MephCheckButton * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephcheckbuttonimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephCheckButton::undoEventMouseDown()
{
	this->mephcheckbuttonimp->undoEventMouseDown();
}

void MephCheckButton::undoEventMouseUp()
{
	this->mephcheckbuttonimp->undoEventMouseUp();
}

void MephCheckButton::undoEventMouseOver()
{
	this->mephcheckbuttonimp->undoEventMouseOver();
}

void MephCheckButton::undoEventPaint()
{
	this->mephcheckbuttonimp->undoEventPaint();
}

void MephCheckButton::undoEventConfigure()
{
	this->mephcheckbuttonimp->undoEventConfigure();
}

void MephCheckButton::undoEventKeyDown()
{
	this->mephcheckbuttonimp->undoEventKeyDown();
}

void MephCheckButton::undoEventKeyUp()
{
	this->mephcheckbuttonimp->undoEventKeyUp();
}

/**************************************************************************/