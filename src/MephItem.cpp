#include "MephItem.h"

MephItem::MephItem(class MephApp const * mephapp)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=0;
  this->y[0]=0;
  this->width[0]=50;
  this->height[0]=15;
	
	this->mephitemsingleton=this->mephitemsingleton->getMephItemSingleton();
	this->mephitemimp=this->mephitemsingleton->getMephItemImp();
		
	this->mephitemimp->initValues((const class MephItem *) this,mephapp->getMephAppImp());
}

MephItem::~MephItem()
{
  delete mephitemimp;
}

void MephItem::addTo(const class MephVisObjImp * mephvisobjimp)
{
  this->mephitemimp->initValues(mephvisobjimp);

	this->initDrawValues(this->mephitemimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
	this->initTextValues(this->mephitemimp);
	this->initImageValues(this->mephitemimp);
}

const class MephItemImp * MephItem::getMephItemImp()
{
  return ((const class MephItemImp *)this->mephitemimp);
}

void MephItem::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephitemimp->update(MephUCoord);
	
}

void MephItem::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephitemimp->update(MephUSize);
}

void MephItem::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephitemimp->update(MephUSize|MephUCoord);
}

void MephItem::show ()
{
	this->visible=1;
  this->mephitemimp->update(MephUVisible);
}
	
void MephItem::hide ()
{
	this->visible=0;
  this->mephitemimp->update(MephUVisible);
}
	
/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephItem::catchEventMouseDown (void (*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephitemimp->catchEventMouseDown(eventmousedown));
}

void (*MephItem::catchEventMouseDown (void (MephListBox::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephListBox *mephlistbox)) (void)
{
	return(this->mephitemimp->catchEventMouseDown(eventmousedown,mephlistbox));
}

void (*MephItem::catchEventMouseDown (void (MephMenu::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephMenu *mephmenu)) (void)
{
	return(this->mephitemimp->catchEventMouseDown(eventmousedown,mephmenu));
}

void (*MephItem::catchEventMouseUp (void (*eventmouseup)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephitemimp->catchEventMouseUp(eventmouseup));
}

void (*MephItem::catchEventMouseOver (void (*eventmouseover)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	return(this->mephitemimp->catchEventMouseOver(eventmouseover));
}

void (*MephItem::catchEventPaint (void (*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count))) (void)
{
	return(this->mephitemimp->catchEventPaint(eventpaint));
}

void (*MephItem::catchEventPaint (void (MephListBox::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephListBox *mephlistbox)) (void)
{
	return(this->mephitemimp->catchEventPaint(eventpaint,mephlistbox));
}

void (*MephItem::catchEventPaint (void (MephFloatingWindow::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephFloatingWindow *mephfloatingwindow)) (void)
{
	return(this->mephitemimp->catchEventPaint(eventpaint,mephfloatingwindow));
}

void (*MephItem::catchEventPaint (void (MephMenu::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephMenu *mephmenu)) (void)
{
	return(this->mephitemimp->catchEventPaint(eventpaint,mephmenu));
}

void (*MephItem::catchEventConfigure (void (*eventconfigure)(class MephItem * mephitem,int x,int y,int width,int height))) (void)
{
	return(this->mephitemimp->catchEventConfigure(eventconfigure));
}

void (*MephItem::catchEventKeyDown (void (*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephitemimp->catchEventKeyDown(eventkeydown));
}

void (*MephItem::catchEventKeyDown (void (MephListBox::*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask),class MephListBox *mephlistbox)) (void)
{
	return(this->mephitemimp->catchEventKeyDown(eventkeydown,mephlistbox));
}

void (*MephItem::catchEventKeyUp   (void (*eventkeyup)  (class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	return(this->mephitemimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephItem::undoEventMouseDown()
{
	this->mephitemimp->undoEventMouseDown();
}

void MephItem::undoEventMouseUp()
{
	this->mephitemimp->undoEventMouseUp();
}

void MephItem::undoEventMouseOver()
{
	this->mephitemimp->undoEventMouseOver();
}

void MephItem::undoEventPaint()
{
	this->mephitemimp->undoEventPaint();
}

void MephItem::undoEventConfigure()
{
	this->mephitemimp->undoEventConfigure();
}


void MephItem::undoEventKeyDown()
{
	this->mephitemimp->undoEventKeyDown();
}

void MephItem::undoEventKeyUp()
{
	this->mephitemimp->undoEventKeyUp();
}
/**************************************************************************/