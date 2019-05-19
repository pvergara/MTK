#include "MephWindow.h"
#include "stdio.h"

/*MephWindow::MephWindow():title(NULL),minwidth(0),minheight(0),maxwidth(0),maxheight(0),decoration(255),decorationfunction(255)
{
  this->mephwindowsingleton=this->mephwindowsingleton->getMephWindowSingleton();
  this->mephwindowimp=this->mephwindowsingleton->getMephWindowImp();

	this->mephwindowimp->initValues((const class MephWindow *) this);
	
	this->initDrawValues(this->mephwindowimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
}*/

MephWindow::MephWindow(class MephApp const * mephapp):title(NULL),minwidth(0),minheight(0),maxwidth(0),maxheight(0),decoration(255),decorationfunction(255)
{
  this->mephwindowsingleton=this->mephwindowsingleton->getMephWindowSingleton();
  this->mephwindowimp=this->mephwindowsingleton->getMephWindowImp();

	this->mephwindowimp->initValues((const class MephWindow *) this,mephapp->getMephAppImp());
	
	this->initDrawValues(this->mephwindowimp);
  this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->setTabIndex(0);
}

MephWindow::MephWindow(const MephWindow &right)
{
}


MephWindow::~MephWindow()
{
  delete this->title;
  delete this->mephwindowimp;
}


const MephWindow & MephWindow::operator=(const MephWindow &right)
{
}


int MephWindow::operator==(const MephWindow &right) const
{
}

int MephWindow::operator!=(const MephWindow &right) const
{
}


void MephWindow::show()
{
  this->visible=1;
	this->mephwindowimp->update(MephUVisible);
}

void MephWindow::hide()
{
  this->visible=0;
	mephwindowimp->update(MephUVisible);
}
void MephWindow::move(int x,int y)
{
  this->x[0]=x;
  this->y[0]=y;

	this->mephwindowimp->update(MephUCoord);
}

void MephWindow::resize(int width,int height)
{
  if (width < this->minwidth)
		this->width[0]=this->minwidth;
	else
		if ((width >this->maxwidth) && (this->maxwidth>0))
      this->width[0]=this->maxwidth;
		else
		  this->width[0]=width;
  

  if (height < this->minheight)
	  this->height[0]=this->minheight;
	else
		if ((height >this->maxheight) && (this->maxheight>0))
      this->height[0]=this->maxheight;
		else
	    this->height[0]=height;
			
	this->mephwindowimp->update(MephUSize);
}

void MephWindow::moveResize(int x,int y,unsigned int width,unsigned int height)
{
  this->x[0]=x;
  this->y[0]=y;

  if (width < this->minwidth)
		this->width[0]=this->minwidth;
	else
		if ((width >this->maxwidth) && (this->maxwidth>0))
      this->width[0]=this->maxwidth;
		else
		  this->width[0]=width;
  

  if (height < this->minheight)
	  this->height[0]=this->minheight;
	else
		if ((height >this->maxheight) && (this->maxheight>0))
      this->height[0]=this->maxheight;
		else
	    this->height[0]=height;
		
	
	mephwindowimp->update(MephUSize | MephUCoord);
}

void MephWindow::notify(int x,int y,unsigned int width, unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
}

char MephWindow::setTabIndex(MephTabIndex tabindex)
{
	if (this->mephwindowimp->setTabIndex(tabindex))
	{
		this->tabindex=tabindex;
		return(1);
	}
	return(0);
}

void MephWindow::end(void)
{
	if (this->mephwindowimp!=NULL)
		this->mephwindowimp->end();
}


int MephWindow::getMinWidth()
{
  return (this->minwidth);
}

int MephWindow::getMinHeight()
{
  return (this->minheight);
}

int MephWindow::getMaxWidth()
{
  return (this->maxwidth);
}

int MephWindow::getMaxHeight()
{
  return (this->maxheight);
}

unsigned char MephWindow::getDecoration()
{
  return (this->decoration);
}

unsigned char MephWindow::getDecorationFunction()
{
  return (this->decorationfunction);
}

void MephWindow::setDecoration(unsigned char decoration)
{
  this->decoration=decoration;
  mephwindowimp->update(MephUDecoration);
}

void MephWindow::setDecorationFunction(unsigned char decorationfunction)
{
	this->decorationfunction=decorationfunction;
	mephwindowimp->update(MephUDecorationFunction);
}

char const * MephWindow::getTitle()
{	
  return (this->title);
}

void MephWindow::setTitle(const char * title)
{
  if (this->title!=NULL)
		  delete [] MephWindow::title;
	
	this->title=new char [strlen(title)+1];
	strcpy(this->title,title);
	mephwindowimp->update(MephUTitle);
}

const class MephWindowImp * MephWindow::getMephWindowImp()
{
  return (this->mephwindowimp);
}

void MephWindow::notify(char visible)
{
	this->visible=visible;
}

/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephWindow::catchEventMouseDown (void (*eventmousedown)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephwindowimp->catchEventMouseDown(eventmousedown));
}

void (*MephWindow::catchEventMouseUp (void (*eventmouseup)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephwindowimp->catchEventMouseUp(eventmouseup));
}

void (*MephWindow::catchEventMouseOver (void (*eventmouseover)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephwindowimp->catchEventMouseOver(eventmouseover));
}

void (*MephWindow::catchEventPaint (void (*eventpaint)(class MephWindow * mephwindow,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephwindowimp->catchEventPaint(eventpaint));
}

void (*MephWindow::catchEventConfigure (void (*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height))) (void)
{
	return(this->mephwindowimp->catchEventConfigure(eventconfigure));
}

void (*MephWindow::catchEventConfigure (void (MephMenu::*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height),class MephMenu *mephmenu)) (void)
{
	return(this->mephwindowimp->catchEventConfigure(eventconfigure,mephmenu));
}

void (*MephWindow::catchEventKeyDown (void (*eventkeydown)(class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephwindowimp->catchEventKeyDown(eventkeydown));
}

void (*MephWindow::catchEventKeyUp   (void (*eventkeyup)  (class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephwindowimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephWindow::undoEventMouseDown()
{
	this->mephwindowimp->undoEventMouseDown();
}

void MephWindow::undoEventMouseUp()
{
	this->mephwindowimp->undoEventMouseUp();
}

void MephWindow::undoEventMouseOver()
{
	this->mephwindowimp->undoEventMouseOver();
}

void MephWindow::undoEventPaint()
{
	this->mephwindowimp->undoEventPaint();
}

void MephWindow::undoEventConfigure()
{
	this->mephwindowimp->undoEventConfigure();
}


void MephWindow::undoEventKeyDown()
{
	this->mephwindowimp->undoEventKeyDown();
}

void MephWindow::undoEventKeyUp()
{
	this->mephwindowimp->undoEventKeyUp();
}
/**************************************************************************/