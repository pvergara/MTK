#include "MephScrollBar.h"

class MephListBox;

MephScrollBar::MephScrollBar(class MephApp const * mephapp):orientation(HORIZONTAL),min(0),max(0),maxinterval(10),mininterval(1)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
	this->tabindex=-1;
  this->x[0]=0;
  this->y[0]=0;
  this->width[0]=200;
  this->height[0]=15;

	this->updatePositions();
	
	this->mephscrollbarsingleton=this->mephscrollbarsingleton->getMephScrollBarSingleton();
	this->mephscrollbarimp=this->mephscrollbarsingleton->getMephScrollBarImp();
		
	this->mephscrollbarimp->initValues((const class MephScrollBar *) this,mephapp->getMephAppImp());
}

MephScrollBar::~MephScrollBar()
{
  delete mephscrollbarimp;
}

void MephScrollBar::addTo(const class MephVisObjImp * mephvisobjimp)
{
	int i;
  this->mephscrollbarimp->initValues(mephvisobjimp);

	this->initDrawValues(this->mephscrollbarimp);
	
  this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	for (i=1;i<4;i++)
	  this->setBackground(0xAFFF,0xAFFF,0xAFFF,i);

	this->initTextValues(this->mephscrollbarimp);
}

const class MephScrollBarImp * MephScrollBar::getMephScrollBarImp()
{
  return ((const class MephScrollBarImp *)this->mephscrollbarimp);
}

void MephScrollBar::notify(int interval)
{
	this->scrollposition+=interval;
}

int MephScrollBar::getMin(void)
{
	return(this->min);
}

int MephScrollBar::getMax(void)
{
	return(this->max);
}

int MephScrollBar::getMinInterval(void)
{
	return(this->mininterval);
}

int MephScrollBar::getMaxInterval(void)
{
	return(this->maxinterval);
}

long MephScrollBar::getScrollPosition(void)
{
	return(this->scrollposition);
}
 
char MephScrollBar::getOrientation(void)
{
	return(this->orientation);
}

void MephScrollBar::setMin(int min)
{
	if ((this->mephscrollbarimp) && (min<=this->max))
	{
	  this->min=min;
		this->scrollposition=min;
		this->mephscrollbarimp->update(MephUSize);
	}
}

void MephScrollBar::setMax(int max)
{
	if ((this->mephscrollbarimp) && (max>=this->min))
	{
  	this->max=max;
		this->mephscrollbarimp->update(MephUSize);
	}
}

void MephScrollBar::setMinInterval(int mininterval)
{
	this->mininterval=mininterval;
}

void MephScrollBar::setMaxInterval(int maxinterval)
{
	this->maxinterval=maxinterval;
}

void MephScrollBar::putScrollPosition(long scrollposition)
{
	this->scrollposition=scrollposition;
}
void MephScrollBar::setScrollPosition(long scrollposition)
{ 
	if (this->scrollposition<scrollposition)
	{
	  this->putScrollPosition(scrollposition);
  	this->mephscrollbarimp->update(MephUPositionDown);
	}
	if (this->scrollposition>scrollposition)
	{
	  this->putScrollPosition(scrollposition);
  	this->mephscrollbarimp->update(MephUPositionUp);
	}
}
 
void MephScrollBar::setOrientation(char orientation)
{
	unsigned int uaux;
	int iaux;
	char i;

	if (this->orientation!=orientation)
	{
  	this->orientation=orientation;
	
	  for (i=0;i<4;i++)
  	{
	    iaux=this->x[i];
		  this->x[i]=this->y[i];
  		this->y[i]=iaux;

	    uaux=this->width[i];
		  this->width[i]=this->height[i];
  		this->height[i]=uaux;
	  }
  	this->mephscrollbarimp->update(MephUOrientation);
	}
	
}

void MephScrollBar::setX(int x,int index)
{
	this->x[index]=x;
}

void MephScrollBar::setY(int y,int index)
{
	this->y[index]=y;
}

void MephScrollBar::setWidth(unsigned int width,int index)
{
	this->width[index]=width;
}

void MephScrollBar::setHeight(unsigned int height,int index)
{
	this->height[index]=height;
}
 
void MephScrollBar::updatePositions(void)
{
  this->x[1]=0;
  this->y[1]=0;
  if (this->orientation==HORIZONTAL)
	{
    this->width[1]=15;
    this->height[1]=this->height[0];
	}
  else
	{
    this->width[1]=this->width[0];
    this->height[1]=15;
	}

  if (this->orientation==HORIZONTAL)
	{
    this->x[2]=this->width[0]-15;
    this->y[2]=0;
    this->width[2]=15;
    this->height[2]=this->height[0];
	}
	else
	{
    this->x[2]=0;
    this->y[2]=this->height[0]-15;
    this->width[2]=this->width[0];
    this->height[2]=15;
	}

  if (this->orientation==HORIZONTAL)
	{
    this->x[3]=this->width[1];
    this->y[3]=0;
    this->width[3]=15;
    this->height[3]=this->height[0];
	}
  else
	{
    this->x[3]=0;
    this->y[3]=this->height[1];
    this->width[3]=this->width[0];
    this->height[3]=15;
	}
}

void MephScrollBar::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->updatePositions();
	this->mephscrollbarimp->update(MephUCoord|MephUOrientation);
}

void MephScrollBar::resize (unsigned int width,unsigned int height)
{
  if (this->orientation==HORIZONTAL)
	  this->width[0]=width;
	else
	  this->height[0]=height;
	
	this->updatePositions();
	
	this->mephscrollbarimp->update(MephUSize|MephUOrientation);
}

void MephScrollBar::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
  if (this->orientation==HORIZONTAL)
  	this->width[0]=width;
  else
	  this->height[0]=height;
	this->updatePositions();
	
	this->mephscrollbarimp->update(MephUSize|MephUCoord|MephUOrientation);

}

void MephScrollBar::show ()
{
	this->visible=1;
  this->mephscrollbarimp->update(MephUVisible);
}
	
void MephScrollBar::hide ()
{
	this->visible=0;
  this->mephscrollbarimp->update(MephUVisible);
}
	
char MephScrollBar::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephscrollbarimp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephScrollBar::catchEventMouseDown (void (*eventmousedown)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephscrollbarimp->catchEventMouseDown(eventmousedown));
}

void (*MephScrollBar::catchEventMouseUp (void (*eventmouseup)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephscrollbarimp->catchEventMouseUp(eventmouseup));
}

void (*MephScrollBar::catchEventMouseOver (void (*eventmouseover)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephscrollbarimp->catchEventMouseOver(eventmouseover));
}

void (*MephScrollBar::catchEventPaint (void (*eventpaint)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephscrollbarimp->catchEventPaint(eventpaint));
}

void (*MephScrollBar::catchEventChange (void (*eventchange)(class MephScrollBar * mephscrollbar))) (void)
{
	return(this->mephscrollbarimp->catchEventChange(eventchange));
}

void (*MephScrollBar::catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar),class MephListBox * mephlistbox)) (void)
{
	return(this->mephscrollbarimp->catchEventChange(eventchange,mephlistbox));
}

void (*MephScrollBar::catchEventConfigure (void (*eventconfigure)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height))) (void)
{
	return(this->mephscrollbarimp->catchEventConfigure(eventconfigure));
}

void (*MephScrollBar::catchEventKeyDown (void (*eventkeydown)(class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephscrollbarimp->catchEventKeyDown(eventkeydown));
}

void (*MephScrollBar::catchEventKeyUp   (void (*eventkeyup)  (class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephscrollbarimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephScrollBar::undoEventMouseDown()
{
	this->mephscrollbarimp->undoEventMouseDown();
}

void MephScrollBar::undoEventMouseUp()
{
	this->mephscrollbarimp->undoEventMouseUp();
}

void MephScrollBar::undoEventMouseOver()
{
	this->mephscrollbarimp->undoEventMouseOver();
}

void MephScrollBar::undoEventPaint()
{
	this->mephscrollbarimp->undoEventPaint();
}

void MephScrollBar::undoEventConfigure()
{
	this->mephscrollbarimp->undoEventConfigure();
}


void MephScrollBar::undoEventKeyDown()
{
	this->mephscrollbarimp->undoEventKeyDown();
}

void MephScrollBar::undoEventKeyUp()
{
	this->mephscrollbarimp->undoEventKeyUp();
}
/**************************************************************************/
