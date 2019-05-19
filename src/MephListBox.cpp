#include "MephListBox.h"
#include <stdio.h>

void MephListBox::Change(class MephScrollBar *mephscrollbar)
{
	this->firstitem=mephscrollbar->getScrollPosition();
	this->refreshPositions();
}

void MephListBox::Paint(class MephItem *mephitem,int x,int y,int width,int height,int count)
{
	this->Paint(mephitem);
}

void MephListBox::MouseDown(class MephItem * mephitem,int x,int y,unsigned int mephbutton)
{
	MephItem * mi=this->selected;
	if (this->selected!=mephitem)
	{
		this->selected=mephitem;
		this->Paint(mi);
		this->Paint(mephitem);
	}
	if ((this->neweventchange) && (this->firstitem>0))
		this->neweventchange(this->selected);
}

void MephListBox::KeyDown(class MephItem * mephitem,char *mephchar,int mephkeysymbol,unsigned int mephkeymask)
{
	MephItem * mi=this->selected;
	int index,i;
	char founded=0;
	
	if ((mephkeysymbol==XK_Up) || (mephkeysymbol==XK_Down))
	{
		for (i=1;i<=this->nitems;i++)
		  if (this->items[i]==this->selected)
			{
				founded=1;
				index=i;
			}

  	if (mephkeysymbol==XK_Up)
	  	if (index>1)
		  {
    		this->selected=this->items[index-1];
	    	this->Paint(mi);
		    this->Paint(this->selected);
    	  if (index==firstitem)
				{
					this->firstitem--;
					this->mephscrollbar->setScrollPosition(this->mephscrollbar->getScrollPosition()-1);
					this->refreshPositions();
				}
		  }
  	if (mephkeysymbol==XK_Down)
	  	if (index<this->nitems)
		  {
    		this->selected=this->items[index+1];
	    	this->Paint(mi);
		    this->Paint(this->selected);
    	  if (((index-firstitem+1)*LISTBOXITEMHEIGHT) >= (this->height[0]))
				{
					this->firstitem++;
					this->mephscrollbar->setScrollPosition(this->mephscrollbar->getScrollPosition()+1);
					this->refreshPositions();
				}
		  }
  	if ((this->neweventchange) && (founded))
	  	this->neweventchange(this->selected);
	}
}

void MephListBox::Paint(class MephItem *mephitem)
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

MephListBox::MephListBox(class MephApp const * mephapp):selected(NULL),firstitem(0),nitems(0),mephlistboximp(NULL),neweventchange(NULL)
{
  this->x[0]=0;
  this->y[0]=0;
  this->width[0]=100;
  this->height[0]=100;
	
	this->mephlistboxsingleton=this->mephlistboxsingleton->getMephListBoxSingleton();
	this->mephlistboximp=this->mephlistboxsingleton->getMephListBoxImp();
	this->mephapp=mephapp;
		
	this->mephlistboximp->initValues((const class MephListBox *) this,mephapp->getMephAppImp());
}

MephListBox::~MephListBox()
{
  delete mephlistboximp;
	delete mephscrollbar;
}

void MephListBox::addTo(const class MephWindowImp * mephwindowimp)
{
  this->mephlistboximp->initValues(mephwindowimp);

	this->initDrawValues(this->mephlistboximp);
	this->setBackground(0xFFFF,0xFFFF,0xFFFF);
	this->initTextValues(this->mephlistboximp);
	this->mephscrollbar=new class MephScrollBar(this->mephapp);
	this->mephscrollbar->addTo(this->mephlistboximp);
	this->mephscrollbar->show();
	this->mephscrollbar->setOrientation(VERTICAL);
	this->mephscrollbar->setMax(1);
	this->mephscrollbar->setMin(1);
	this->mephscrollbar->moveResize(this->width[0]-15,0,15,this->height[0]);
	this->mephscrollbar->catchEventChange(&(MephListBox::Change),this);
}

const class MephListBoxImp * MephListBox::getMephListBoxImp()
{
  return ((const class MephListBoxImp *)this->mephlistboximp);
}

void MephListBox::deleteItem(int index)
{
	int i;
	if (this->items[index]!=NULL)
	{
		this->mephlistboximp->destroyWindow(this->items[index]->getMephItemImp());
		for (i=index;i<this->nitems;i++)
			this->items[i]=this->items[i+1];
    if (((this->nitems-this->firstitem)*LISTBOXITEMHEIGHT) >= (this->height[0]))
     	this->mephscrollbar->setMax(this->mephscrollbar->getMax()-1);
		if (this->items.size()==0)
		{
			this->firstitem=0;
			this->selected=NULL;
		}
		this->nitems--;
		this->items.erase(--this->items.end());
		this->refreshPositions();
	}
}

void MephListBox::deleteItems()
{
	int i,n=this->nitems;
	for (i=1;i<=n;i++)
		this->deleteItem(1);
}

int MephListBox::count()
{
	return(this->nitems);
}

const class MephItem *MephListBox::getItem(int index)
{
	if (this->items[index])
		return((const class MephItem *) this->items[index]);
	else
		return(NULL);
}

map <int,class MephItem *>MephListBox::getItems()
{
	return(this->items);
}


const class MephItem *MephListBox::getSelected()
{
	return(this->selected);
}

void MephListBox::refreshPositions(void)
{
	int i;
  /*CUANDO AÑADIMOS UN NUEVO ELEMENTO A UN LISTBOX DICHO ELEMENTO TIENE QUE SABER DONDE "COLOCARSE" PARA ELLO TENEMOS QUE
	SABER SI SE PUEDE AÑADIR A LA ZONA VISIBLE O NO*/
	for (i=1;i<=nitems;i++)
	{
  	this->items[i]->move(0,((i)-(firstitem))*LISTBOXITEMHEIGHT);
	  if ( (((i)-firstitem)*LISTBOXITEMHEIGHT) < (this->height[0]))
  	  this->items[i]->show();
  }
}

void MephListBox::addItem (void)
{
	if (this->mephlistboximp!=NULL)
	{
	  this->nitems++;
		
	  this->items[nitems]=new class MephItem(this->mephapp);
		if (this->nitems==1)
		{
			this->selected=this->items[nitems];
			this->firstitem=1;
		}
	  this->items[nitems]->addTo(this->mephlistboximp);
		this->items[nitems]->resize(this->width[0]-this->mephscrollbar->getWidth(),LISTBOXITEMHEIGHT);
		this->refreshPositions();
    if (((this->nitems-this->firstitem)*LISTBOXITEMHEIGHT) >= (this->height[0]))
     	this->mephscrollbar->setMax(this->mephscrollbar->getMax()+1);
		
		this->items[nitems]->catchEventPaint(&(MephListBox::Paint),this);
		this->items[nitems]->catchEventMouseDown(&(MephListBox::MouseDown),this);
		this->items[nitems]->catchEventKeyDown(&(MephListBox::KeyDown),this);
	}
}

void MephListBox::addItem(char * text)
{
	this->addItem();
	this->items[nitems]->setText(text);
}

void MephListBox::addImageItem(char * imagepath)
{
	this->addItem();
	this->items[nitems]->setBackground(imagepath);
}

void MephListBox::addItem(unsigned short red,unsigned short green,unsigned short blue)
{
	this->addItem();
	this->items[nitems]->setBackground(red,green,blue);
}

void MephListBox::addDoubleItem(char * text,char * imagepath)
{
	this->addItem();
	this->items[nitems]->setText(text);
	this->items[nitems]->setBackground(imagepath);
}
	
void MephListBox::setItemText(char * text,int index,char * result)
{
}

void MephListBox::setItemImage(char * imagepath,int index,char * result)
{
}
	
char MephListBox::removeItem(int index)
{
}

void MephListBox::clearItems()
{
}

class MephItem * MephListBox::getItem(void) const
{
//	return (this->items[selected]);
}

void MephListBox::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephlistboximp->update(MephUCoord);
	
}

void MephListBox::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;
	this->mephscrollbar->moveResize(this->width[0]-15,0,15,this->height[0]);

	this->mephlistboximp->update(MephUSize);
}

void MephListBox::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	this->mephscrollbar->moveResize(this->width[0]-15,0,15,this->height[0]);
	
	this->mephlistboximp->update(MephUSize|MephUCoord);
}

void MephListBox::show ()
{
	int i;
	this->visible=1;
	
	for (i=1;i<nitems+1;i++)
	  this->items[i]->show();
  this->mephlistboximp->update(MephUVisible);
}
	
void MephListBox::hide ()
{
	this->visible=0;
  this->mephlistboximp->update(MephUVisible);
}
	
void (*MephListBox::catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void)
{
  this->neweventchange=eventchange;
}
