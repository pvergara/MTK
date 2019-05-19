#include "MephRadioButton.h"

map <int,MephRadioButton *> MephRadioButton::objects;

MephRadioButton::MephRadioButton(class MephApp const * mephapp):mephradiobuttonimp(NULL),state(0),group(0)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=1;
  this->y[0]=1;
  this->width[0]=50;
  this->height[0]=20;
	
	this->mephradiobuttonsingleton=this->mephradiobuttonsingleton->getMephRadioButtonSingleton();
	this->mephradiobuttonimp=this->mephradiobuttonsingleton->getMephRadioButtonImp();
		
	this->mephradiobuttonimp->initValues((const class MephRadioButton *) this,mephapp->getMephAppImp());
}

MephRadioButton::~MephRadioButton()
{
  delete mephradiobuttonimp;
}

void MephRadioButton::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephradiobuttonimp->initValues(mephwindowimp);

	this->initDrawValues(this->mephradiobuttonimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->initTextValues(this->mephradiobuttonimp);
}

const class MephRadioButtonImp * MephRadioButton::getMephRadioButtonImp()
{
  return ((const class MephRadioButtonImp *)this->mephradiobuttonimp);
}

/*void MephRadioButton::check(void)
{
}*/

/*void MephRadioButton::setGroup(int group)
{
  this->group=group;
  if (!unchecks[group])
  {
    unchecks[group]=&MephRadioButton::uncheck;
    this->state=1;
  }
	else
    this->state=0;
  this->mephradiobuttonimp->update(MephUPressed);
}*/

void MephRadioButton::uncheck(void)
{
  if (this->mephradiobuttonimp!=NULL)
  {
    this->state=0;
    this->mephradiobuttonimp->update(MephUPressed);
  }
}

int MephRadioButton::getGroup(void)
{
  return(this->group);
}

char MephRadioButton::getState(void)
{
  if (this->mephradiobuttonimp!=NULL)
    return(this->state);
}

/*NO HACE FALTA EL NOTIFY PUES SIEMPRE QUE SE PULSE EL BOTÓN IIIIZZQQQUIIIIEEERRRRDDOOOO SOBRE EL RADIOBUTTON SERµ PARA HACER
UN CHECK*/
/*void MephRadioButton::notify(char state)
{
	this->state=state;
  this->mephradiobuttonimp->update(MephUPressed);
}*/

void MephRadioButton::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephradiobuttonimp->update(MephUCoord);
	
}

void MephRadioButton::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephradiobuttonimp->update(MephUSize);
}

void MephRadioButton::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephradiobuttonimp->update(MephUSize|MephUCoord);
}

void MephRadioButton::show ()
{
	this->visible=1;
  this->mephradiobuttonimp->update(MephUVisible);
}
	
void MephRadioButton::hide ()
{
	this->visible=0;
  this->mephradiobuttonimp->update(MephUVisible);
}
	
char MephRadioButton::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephradiobuttonimp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephRadioButton::catchEventMouseDown (void (*eventmousedown)(class MephRadioButton * mephradio,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephradiobuttonimp->catchEventMouseDown(eventmousedown));
}

void (*MephRadioButton::catchEventMouseUp (void (*eventmouseup)(class MephRadioButton * mephradio,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephradiobuttonimp->catchEventMouseUp(eventmouseup));
}

void (*MephRadioButton::catchEventMouseOver (void (*eventmouseover)(class MephRadioButton * mephradio,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephradiobuttonimp->catchEventMouseOver(eventmouseover));
}

void (*MephRadioButton::catchEventPaint (void (*eventpaint)(class MephRadioButton * mephradio,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephradiobuttonimp->catchEventPaint(eventpaint));
}

void (*MephRadioButton::catchEventConfigure (void (*eventconfigure)(class MephRadioButton * mephradio,int x,int y,int width,int height))) (void)
{
	return(this->mephradiobuttonimp->catchEventConfigure(eventconfigure));
}

void (*MephRadioButton::catchEventKeyDown (void (*eventkeydown)(class MephRadioButton * mephradio,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephradiobuttonimp->catchEventKeyDown(eventkeydown));
}

void (*MephRadioButton::catchEventKeyUp   (void (*eventkeyup)  (class MephRadioButton * mephradio,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephradiobuttonimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephRadioButton::undoEventMouseDown()
{
	this->mephradiobuttonimp->undoEventMouseDown();
}

void MephRadioButton::undoEventMouseUp()
{
	this->mephradiobuttonimp->undoEventMouseUp();
}

void MephRadioButton::undoEventMouseOver()
{
	this->mephradiobuttonimp->undoEventMouseOver();
}

void MephRadioButton::undoEventPaint()
{
	this->mephradiobuttonimp->undoEventPaint();
}

void MephRadioButton::undoEventConfigure()
{
	this->mephradiobuttonimp->undoEventConfigure();
}

void MephRadioButton::undoEventKeyDown()
{
	this->mephradiobuttonimp->undoEventKeyDown();
}

void MephRadioButton::undoEventKeyUp()
{
	this->mephradiobuttonimp->undoEventKeyUp();
}

/**************************************************************************/