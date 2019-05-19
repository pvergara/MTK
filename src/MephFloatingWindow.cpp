#include "MephFloatingWindow.h"

MephFloatingWindow::MephFloatingWindow(class MephApp const * mephapp):selected(NULL),firstitem(0),nitems(0),neweventchange(NULL),neweventchangetomephcombobox(NULL),neweventchangetomephmenu(NULL),neweventleftrighttomephmenu(NULL)
{
  this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
  this->x[0]=0;
  this->y[0]=0;
  this->width[0]=50;
  this->height[0]=15;
	
	this->mephapp=(class MephApp *)mephapp;
	
	this->mephfloatingwindowsingleton=this->mephfloatingwindowsingleton->getMephFloatingWindowSingleton();
	this->mephfloatingwindowimp=this->mephfloatingwindowsingleton->getMephFloatingWindowImp();
		
	this->mephfloatingwindowimp->initValues((const class MephFloatingWindow *) this,mephapp->getMephAppImp());
}

MephFloatingWindow::~MephFloatingWindow()
{
  delete mephfloatingwindowimp;
}

int MephFloatingWindow::getFirstItem()
{
	return(this->firstitem);
}

void MephFloatingWindow::Paint(class MephItem *mephitem,int x,int y,int width,int height,int count)
{
	this->Paint(mephitem);
}

void MephFloatingWindow::Paint(class MephItem *mephitem)
{
	unsigned long colorindex;
	int addfunction;
	mephitem->clearScreen();
//  mephitem->setBackground();

	if (this->selected==mephitem)
	{
		colorindex=mephitem->getForeColorIndex();
		mephitem->setBackground(0,0,0xFFFF);
		mephitem->setForeColor(colorindex);
	}
	else
	{
    mephitem->setBackground();
    if ((mephitem->getImagePath()!=NULL) || (mephitem->getImagePath()!=""))
      mephitem->showImage();
	}

	mephitem->setTextX((mephitem->getWidth()/2)-(mephitem->getTextWidth()/2));
	mephitem->setTextY((mephitem->getHeight()/2));

	if (this->selected==mephitem)
	{
		colorindex=mephitem->getTextForeColorIndex();
		mephitem->setTextForeColor(0xFFFF,0xFFFF,0xFFFF);
		mephitem->showText();
		mephitem->setTextForeColor(colorindex);
	}
	else
		mephitem->showText();

}

void MephFloatingWindow::addTo(const class MephVisObjImp * mephvisobjimp)
{
  this->mephfloatingwindowimp->initValues(mephvisobjimp);


	this->initDrawValues(this->mephfloatingwindowimp);
	this->initTextValues(this->mephfloatingwindowimp);
	this->setBackground(0xFFFF,0xFFFF,0xFFFF);
}

const class MephFloatingWindowImp * MephFloatingWindow::getMephFloatingWindowImp()
{
  return ((const class MephFloatingWindowImp *)this->mephfloatingwindowimp);
}

void MephFloatingWindow::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephfloatingwindowimp->update(MephUCoord);
}

void MephFloatingWindow::notify(int y)
{
	char founded=0;
	int i;
	if (firstitem>0)
	{
    for (i=firstitem;(i<=(this->height[0]/FLOATINGWINDOWITEMHEIGHT)) && (i<=nitems) && (!founded);i++)
	  	if ((y>=this->items[i]->getY()) && (y<=this->items[i]->getY()+this->items[i]->getHeight()))
		  {
        this->selected=this->items[i];
  			founded=1;
	  	}
			
    if (founded)
	  {
		  if (this->neweventchange)
  	    this->neweventchange(this->selected);
	  	if (this->neweventchangetomephcombobox)
		  	(this->mephcombobox->*neweventchangetomephcombobox)(this->selected);
	  	if (this->neweventchangetomephmenu)
		  	(this->mephmenu->*neweventchangetomephmenu)(this->selected);
  	}
	}
}

void MephFloatingWindow::notifyKeyUp(void)
{
	MephItem * mi=this->selected;
	int index,i;
	char founded=0;
	
	if (firstitem>0)
	{
    for (i=1;i<=this->nitems;i++)
	    if (this->items[i]==this->selected)
		  {
			  founded=1;
  			index=i;
	  	}

   	if (index>1)
    {
 		  this->selected=this->items[index-1];
   	  if (index==firstitem)
	  	{
		  	this->firstitem--;
			  this->refreshPositions();
  		}
     	this->Paint(mi);
      this->Paint(this->selected);
    }
  }
}

void MephFloatingWindow::notifyKeyDown(void)
{
	MephItem * mi=this->selected;
	int index,i;
	char founded=0;
	
	if (firstitem>0)
	{
    for (i=1;i<=this->nitems;i++)
	    if (this->items[i]==this->selected)
		  {
  			founded=1;
	  		index=i;
		  }

 	  if (index<this->nitems)
    {
 	  	this->selected=this->items[index+1];
 	    if (((index-firstitem+1)*FLOATINGWINDOWITEMHEIGHT) >= (this->height[0]))
  		{
	  		this->firstitem++;
		  	this->refreshPositions();
  		}
     	this->Paint(mi);
      this->Paint(this->selected);
    }
  }
}

void MephFloatingWindow::notifyKeyRight(void)
{
	if (this->neweventleftrighttomephmenu!=NULL)
	  (this->mephmenu->*neweventleftrighttomephmenu)(FLOATINGWINDOWITEMRIGHT);
}

void MephFloatingWindow::notifyKeyLeft (void)
{
	if (this->neweventleftrighttomephmenu!=NULL)
	  (this->mephmenu->*neweventleftrighttomephmenu)(FLOATINGWINDOWITEMLEFT);
}

void MephFloatingWindow::notifyKeyEnter(void)
{
	if (this->firstitem>0)
	{
    if (this->neweventchange)
      this->neweventchange(this->selected);
  	if (this->neweventchangetomephcombobox)
	  	(this->mephcombobox->*neweventchangetomephcombobox)(this->selected);
  	if (this->neweventchangetomephmenu)
	  	(this->mephmenu->*neweventchangetomephmenu)(this->selected);
	}
}

void MephFloatingWindow::notifyPaint(void)
{
	int index,i;
	
	if (this->firstitem>0)
	{
	  this->firstitem=1;
	  this->selected=this->items[firstitem];
	  this->refreshPositions();
    for (i=firstitem;(i<=this->height[0]/FLOATINGWINDOWITEMHEIGHT) && (i<=nitems);i++)
    	this->Paint(this->items[i]);
	}
}

void MephFloatingWindow::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephfloatingwindowimp->update(MephUSize);
}

void MephFloatingWindow::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephfloatingwindowimp->update(MephUSize|MephUCoord);
}

void MephFloatingWindow::show ()
{
	this->visible=1;
	this->mephfloatingwindowimp->show();
//  this->mephfloatingwindowimp->update(MephUVisible);
}

void MephFloatingWindow::show (int x,int y)
{
	this->visible=1;
	this->mephfloatingwindowimp->show(x,y);
//  this->mephfloatingwindowimp->update(MephUVisible);
}
	
void MephFloatingWindow::hide ()
{
	this->visible=0;
//  this->mephfloatingwindowimp->update(MephUVisible);
}

void MephFloatingWindow::refreshPositions(void)
{
	int i;
  /*CUANDO AÑADIMOS UN NUEVO ELEMENTO A UN LISTBOX DICHO ELEMENTO TIENE QUE SABER DONDE "COLOCARSE" PARA ELLO TENEMOS QUE
	SABER SI SE PUEDE AÑADIR A LA ZONA VISIBLE O NO*/
	for (i=1;i<=nitems;i++)
	{
  	this->items[i]->move(0,((i)-(firstitem))*FLOATINGWINDOWITEMHEIGHT);
	  if ( (((i)-firstitem)*FLOATINGWINDOWITEMHEIGHT) < (this->height[0]))
  	  this->items[i]->show();
  }
}

void MephFloatingWindow::deleteItem(int index)
{
	int i;
	if (this->items[index]!=NULL)
	{
		this->mephfloatingwindowimp->destroyWindow(this->items[index]->getMephItemImp());
		for (i=index;i<this->nitems;i++)
			this->items[i]=this->items[i+1];
		this->nitems--;
		this->items.erase(--this->items.end());
		if (this->items.size()==0)
		{
			this->firstitem=0;
			this->selected=NULL;
		}
	}
}

void MephFloatingWindow::deleteItems()
{
	int i,n=this->nitems;
	for (i=1;i<=n;i++)
		this->deleteItem(1);
}

int MephFloatingWindow::count()
{
	return(this->nitems);
}

const class MephItem *MephFloatingWindow::getItem(int index)
{
	if (this->items[index])
		return((const class MephItem *) this->items[index]);
	else
		return(NULL);
}

map <int,class MephItem *>MephFloatingWindow::getItems()
{
	return(this->items);
}

void MephFloatingWindow::addItem (void)
{
	if (this->mephfloatingwindowimp!=NULL)
	{
	  this->nitems++;
		
	  this->items[nitems]=new class MephItem(this->mephapp);
		if (this->nitems==1)
		{
			this->selected=this->items[nitems];
			this->firstitem=1;
		}
	  this->items[nitems]->addTo(this->mephfloatingwindowimp);
		this->items[nitems]->resize(this->width[0],FLOATINGWINDOWITEMHEIGHT);
		this->refreshPositions();
		
		this->items[nitems]->catchEventPaint(&(MephFloatingWindow::Paint),this);
/*		this->items[nitems]->catchEventMouseDown(&(MephListBox::MouseDown),this);
		this->items[nitems]->catchEventKeyDown(&(MephListBox::KeyDown),this);*/
	}
}

void MephFloatingWindow::addItem(char * text)
{
	this->addItem();
	this->items[nitems]->setText(text);
}

void MephFloatingWindow::addImageItem(char * imagepath)
{
	this->addItem();
	this->items[nitems]->setBackground(imagepath);
}

void MephFloatingWindow::addItem(unsigned short red,unsigned short green,unsigned short blue)
{
	this->addItem();
	this->items[nitems]->setBackground(red,green,blue);
}

void MephFloatingWindow::addDoubleItem(char * text,char * imagepath)
{
	this->addItem();
	this->items[nitems]->setText(text);
	this->items[nitems]->setBackground(imagepath);
}


/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephFloatingWindow::catchEventMouseDown (void (*eventmousedown)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventMouseDown(eventmousedown));
}

void (*MephFloatingWindow::catchEventMouseUp (void (*eventmouseup)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventMouseUp(eventmouseup));
}

void (*MephFloatingWindow::catchEventMouseOver (void (*eventmouseover)(class MephFloatingWindow * mephfloatingwindow,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventMouseOver(eventmouseover));
}

void (*MephFloatingWindow::catchEventPaint (void (*eventpaint)(class MephFloatingWindow * mephfloatingwindow,int x,int y,int width,int height,int count))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventPaint(eventpaint));
}

void (*MephFloatingWindow::catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void)
{
  this->neweventchange=eventchange;
}

void (*MephFloatingWindow::catchEventChange (void (MephComboBox::*eventchange)(class MephItem * mephitem),class MephComboBox * mephcombobox)) (void)
{
  this->mephcombobox=mephcombobox;
  this->neweventchangetomephcombobox=eventchange;
}

void (*MephFloatingWindow::catchEventChange (void (MephMenu::*eventchange)(class MephItem * mephitem),class MephMenu * mephmenu)) (void)
{
  this->mephmenu=mephmenu;
  this->neweventchangetomephmenu=eventchange;
}

void (*MephFloatingWindow::catchEventLeftRight (void (MephMenu::*eventleftright)(char direction),class MephMenu * mephmenu)) (void)
{
  this->mephmenu=mephmenu;
  this->neweventleftrighttomephmenu=eventleftright;
}

void (*MephFloatingWindow::catchEventConfigure (void (*eventconfigure)(class MephFloatingWindow * mephfloatingwindow,int x,int y,int width,int height))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventConfigure(eventconfigure));
}

void (*MephFloatingWindow::catchEventKeyDown (void (*eventkeydown)(class MephFloatingWindow * mephfloatingwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventKeyDown(eventkeydown));
}

void (*MephFloatingWindow::catchEventKeyUp   (void (*eventkeyup)  (class MephFloatingWindow * mephfloatingwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
//	return(this->mephfloatingwindowimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephFloatingWindow::undoEventMouseDown()
{
//	this->mephfloatingwindowimp->undoEventMouseDown();
}

void MephFloatingWindow::undoEventMouseUp()
{
//	this->mephfloatingwindowimp->undoEventMouseUp();
}

void MephFloatingWindow::undoEventMouseOver()
{
//	this->mephfloatingwindowimp->undoEventMouseOver();
}

void MephFloatingWindow::undoEventPaint()
{
//	this->mephfloatingwindowimp->undoEventPaint();
}

void MephFloatingWindow::undoEventConfigure()
{
//	this->mephfloatingwindowimp->undoEventConfigure();
}


void MephFloatingWindow::undoEventKeyDown()
{
//	this->mephfloatingwindowimp->undoEventKeyDown();
}

void MephFloatingWindow::undoEventKeyUp()
{
//	this->mephfloatingwindowimp->undoEventKeyUp();
}
/**************************************************************************/