#include "MephMenu.h"

void MephMenu::Configure(class MephWindow * mephwindow,int x,int y,int width,int height)
{
	this->width[0]=width;
	this->mephmenuimp->update(MephUSize);
}

void MephMenu::MouseDown(class MephItem * mephitem,int x,int y,unsigned int mephbutton)
{
	MephItem * mi=NULL;
	int i;
	char founded=0;
	
	for(i=1;(i<=nitems) && (!founded);i++)
		if (this->items[i]==mephitem)
		{
			this->optionindex=i;
			founded=1;
		}
		
	if (this->suboptions[mephitem]!=NULL)
	{
  	if (this->selected!=NULL)
	  	mi=this->selected;
  	if (this->selected!=mephitem)
	  {
		  this->selected=mephitem;
  		if (mi!=NULL)
	  	  this->Paint(mi);
  		this->Paint(mephitem);
	  }
		this->suboptions[mephitem]->show();
		this->selected=NULL;
 	  this->Paint(mephitem);
  }
	else
	{
		if ((this->neweventchange) && (this->firstitem>0))
	  	this->neweventchange(mephitem);
	}
}
void MephMenu::Change(class MephItem *mephitem)
{
	if (this->neweventchange)
  	this->neweventchange(mephitem);
}

MephMenu::MephMenu(class MephApp const * mephapp):selected(NULL),firstitem(0),nitems(0),neweventchange(NULL),neweventchangetomephcombobox(NULL),widthitems(3),optionindex(1)
{
  this->x[0]=0;
  this->y[0]=0;
  this->width[0]=100;
  this->height[0]=30;
	
	this->mephapp=(class MephApp *)mephapp;
	
	this->mephmenusingleton=this->mephmenusingleton->getMephMenuSingleton();
	this->mephmenuimp=this->mephmenusingleton->getMephMenuImp();
		
	this->mephmenuimp->initValues((const class MephMenu *) this,mephapp->getMephAppImp());
}

MephMenu::~MephMenu()
{
  delete mephmenuimp;
}

int MephMenu::getFirstItem()
{
	return(this->firstitem);
}

void MephMenu::Paint(class MephItem *mephitem,int x,int y,int width,int height,int count)
{
	this->Paint(mephitem);
}

void MephMenu::Paint(class MephItem *mephitem)
{
	unsigned long colorindex;
	int addfunction;
	mephitem->clearScreen();
//  mephitem->setBackground();

	if ((this->selected!=NULL) && (this->selected==mephitem))
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

void MephMenu::addTo(const class MephVisObjImp * mephvisobjimp)
{
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
  this->width[0]=this->mephvisobjimp->getWidth();
  this->mephmenuimp->initValues(mephvisobjimp);

	this->initDrawValues(this->mephmenuimp);
//	this->initTextValues(this->mephmenuimp);
	this->setBackground(0xEFFF,0xEFFF,0xEFFF);
}

const class MephMenuImp * MephMenu::getMephMenuImp()
{
  return ((const class MephMenuImp *)this->mephmenuimp);
}

/*void MephMenu::move (int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
	this->mephmenuimp->update(MephUCoord);
}
void MephMenu::resize (unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;

	this->mephmenuimp->update(MephUSize);
}

void MephMenu::moveResize (int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephmenuimp->update(MephUSize|MephUCoord);
}
*/

void MephMenu::notify(int y)
{
	char founded=0;
	int i;
	if (firstitem>0)
	{
    for (i=firstitem;(i<=(this->height[0]/MENUITEMHEIGHT)) && (i<=nitems) && (!founded);i++)
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
  	}
	}
}

void MephMenu::notifyKeyUp(void)
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

void MephMenu::notifyKeyDown(void)
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
 	    if (((index-firstitem+1)*MENUITEMHEIGHT) >= (this->height[0]))
  		{
	  		this->firstitem++;
		  	this->refreshPositions();
  		}
     	this->Paint(mi);
      this->Paint(this->selected);
    }
  }
}

void MephMenu::notifyKeyLeftRight(char direction)
{
	if (direction==FLOATINGWINDOWITEMRIGHT)
		if (this->items[this->optionindex+1]!=NULL)
			this->MouseDown(this->items[this->optionindex+1],0,0,0);
		else
			this->MouseDown(this->items[1],0,0,0);

	if (direction==FLOATINGWINDOWITEMLEFT)
		if (this->items[this->optionindex-1]!=NULL)
			this->MouseDown(this->items[this->optionindex-1],0,0,0);
		else
			this->MouseDown(this->items[this->nitems],0,0,0);
}

void MephMenu::notifyKeyEnter(void)
{
	if (this->firstitem>0)
	{
    if (this->neweventchange)
      this->neweventchange(this->selected);
  	if (this->neweventchangetomephcombobox)
	  	(this->mephcombobox->*neweventchangetomephcombobox)(this->selected);
	}
}

void MephMenu::notifyPaint(void)
{
	int index,i;
	
	if (this->firstitem>0)
	{
	  this->firstitem=1;
	  this->selected=this->items[firstitem];
	  this->refreshPositions();
    for (i=firstitem;(i<=this->height[0]/MENUITEMHEIGHT) && (i<=nitems);i++)
    	this->Paint(this->items[i]);
	}
}

void MephMenu::show ()
{
	this->visible=1;
  this->mephmenuimp->update(MephUVisible);
}

/*void MephMenu::show (int x,int y)
{
	this->visible=1;
	this->mephmenuimp->show(x,y);
//  this->mephmenuimp->update(MephUVisible);
}*/
	
void MephMenu::hide ()
{
	this->visible=0;
  this->mephmenuimp->update(MephUVisible);
}

void MephMenu::refreshPositions(void)
{
	int i;
	for (i=1;i<=nitems;i++)
	{	
  	if (i==1)
    	this->items[i]->move(3,3);
		else
    	this->items[i]->move(this->items[i-1]->getWidth(),3);
  	this->items[i]->show();
  }
}

void MephMenu::deleteItem(int index)
{
	int i;
	if (this->items[index]!=NULL)
	{
		this->mephmenuimp->destroyWindow(this->items[index]->getMephItemImp());
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

void MephMenu::deleteItems()
{
	int i,n=this->nitems;
	for (i=1;i<=n;i++)
		this->deleteItem(1);
}

int MephMenu::count()
{
	return(this->nitems);
}

const class MephItem *MephMenu::getItem(int index)
{
	if (this->items[index])
		return((const class MephItem *) this->items[index]);
	else
		return(NULL);
}

map <int,class MephItem *>MephMenu::getItems()
{
	return(this->items);
}

void MephMenu::addItem (void)
{
	class MephWindowImp *mephwindowimp=(class MephWindowImp *)this->mephvisobjimp;
	if (this->mephmenuimp!=NULL)
	{
	  this->nitems++;
		
	  this->items[nitems]=new class MephItem(this->mephapp);
		if (this->nitems==1)
		{
//			this->selected=this->items[nitems];
			this->firstitem=1;
		}
	  this->items[nitems]->addTo(this->mephmenuimp);
		
		this->items[nitems]->catchEventPaint(&(MephMenu::Paint),this);
		mephwindowimp->catchEventConfigure(&(MephMenu::Configure),this);
		this->items[nitems]->catchEventMouseDown(&(MephMenu::MouseDown),this);
	}
}

void MephMenu::addItem(char * text)
{
	this->addItem();
	this->items[nitems]->setText(text);
	this->items[nitems]->resize(this->items[nitems]->getTextWidth()+5,MENUITEMHEIGHT);
	this->refreshPositions();
}

void MephMenu::addImageItem(char * imagepath)
{
	this->addItem();
	this->items[nitems]->setBackground(imagepath);
	this->items[nitems]->resize(MENUITEMWIDTH,MENUITEMHEIGHT);
	this->refreshPositions();
}

void MephMenu::addItem(unsigned short red,unsigned short green,unsigned short blue)
{
	this->addItem();
	this->items[nitems]->setBackground(red,green,blue);
	this->items[nitems]->resize(MENUITEMWIDTH,MENUITEMHEIGHT);
	this->refreshPositions();
}

void MephMenu::addDoubleItem(char * text,char * imagepath)
{
	this->addItem();
	this->items[nitems]->setText(text);
	this->items[nitems]->setBackground(imagepath);
	this->items[nitems]->resize(this->items[nitems]->getTextWidth()+5,MENUITEMHEIGHT);
	this->refreshPositions();
}

void MephMenu::addSubOption(char * text,char * index)
{
	int *ind,i,j=0;
	char count;
	
	for (i=0;i<strlen(index);i++)
		if ((index[i+1]<'0') || (index[i+1]>'9'))
			j++;
	if (j>0)	
	{
  	ind=new int[j];
	
  	this->getIndex(index,ind,&count);
		if (this->suboptions[this->items[ind[0]]]==NULL)
		{
			this->suboptions[this->items[ind[0]]]=new class MephFloatingWindow(this->mephapp);
			this->suboptions[this->items[ind[0]]]->addTo((class MephItemImp *)this->items[ind[0]]->getMephItemImp());
  		this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),FLOATINGWINDOWITEMHEIGHT);
			this->suboptions[this->items[ind[0]]]->catchEventChange(&(MephMenu::Change),this);
			this->suboptions[this->items[ind[0]]]->catchEventLeftRight(&(MephMenu::notifyKeyLeftRight),this);
		}
		else
		{
			if (this->suboptions[this->items[ind[0]]]->getHeight()<450)
			  this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),this->suboptions[this->items[ind[0]]]->getHeight()+FLOATINGWINDOWITEMHEIGHT);
		}
		
		this->suboptions[this->items[ind[0]]]->addItem(text);
		
		class MephItem *mi=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(this->suboptions[this->items[ind[0]]]->count());
		class MephItem *aux;
		if (mi->getTextWidth()>this->suboptions[this->items[ind[0]]]->getWidth())
		{
      this->suboptions[this->items[ind[0]]]->resize(mi->getTextWidth()+20,this->suboptions[this->items[ind[0]]]->getHeight());
			for (i=1;i<=count;i++)
			{
				aux=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(i);
				aux->resize(mi->getTextWidth(),FLOATINGWINDOWITEMHEIGHT);
			}
		}
	}
}

void MephMenu::addImageSubOption(char * imagepath,char * index)
{
	int *ind,i,j=0;
	char count;
	
	for (i=0;i<strlen(index);i++)
		if ((index[i+1]<'0') || (index[i+1]>'9'))
			j++;
	if (j>0)	
	{
  	ind=new int[j];
	
  	this->getIndex(index,ind,&count);
		if (this->suboptions[this->items[ind[0]]]==NULL)
		{
			this->suboptions[this->items[ind[0]]]=new class MephFloatingWindow(this->mephapp);
			this->suboptions[this->items[ind[0]]]->addTo((class MephItemImp *)this->items[ind[0]]->getMephItemImp());
  		this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth()+20,FLOATINGWINDOWITEMHEIGHT);
			this->suboptions[this->items[ind[0]]]->catchEventChange(&(MephMenu::Change),this);
			this->suboptions[this->items[ind[0]]]->catchEventLeftRight(&(MephMenu::notifyKeyLeftRight),this);
		}
		else
		{
			if (this->suboptions[this->items[ind[0]]]->getHeight()<450)
			  this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),this->suboptions[this->items[ind[0]]]->getHeight()+FLOATINGWINDOWITEMHEIGHT);
		}
		
		this->suboptions[this->items[ind[0]]]->addImageItem(imagepath);
		
		class MephItem *mi=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(this->suboptions[this->items[ind[0]]]->count());
		class MephItem *aux;
		if (MENUITEMWIDTH>this->suboptions[this->items[ind[0]]]->getWidth())
		{
      this->suboptions[this->items[ind[0]]]->resize(MENUITEMWIDTH,this->suboptions[this->items[ind[0]]]->getHeight());
			for (i=1;i<=count;i++)
			{
				aux=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(i);
				aux->resize(MENUITEMWIDTH,FLOATINGWINDOWITEMHEIGHT);
			}
		}
	}
}

void MephMenu::addSubOption(unsigned short red,unsigned short green,unsigned short blue,char * index)
{
	int *ind,i,j=0;
	char count;
	
	for (i=0;i<strlen(index);i++)
		if ((index[i+1]<'0') || (index[i+1]>'9'))
			j++;
	if (j>0)	
	{
  	ind=new int[j];
	
  	this->getIndex(index,ind,&count);
		if (this->suboptions[this->items[ind[0]]]==NULL)
		{
			this->suboptions[this->items[ind[0]]]=new class MephFloatingWindow(this->mephapp);
			this->suboptions[this->items[ind[0]]]->addTo((class MephItemImp *)this->items[ind[0]]->getMephItemImp());
  		this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth()+20,FLOATINGWINDOWITEMHEIGHT);
			this->suboptions[this->items[ind[0]]]->catchEventChange(&(MephMenu::Change),this);
			this->suboptions[this->items[ind[0]]]->catchEventLeftRight(&(MephMenu::notifyKeyLeftRight),this);
		}
		else
		{
			if (this->suboptions[this->items[ind[0]]]->getHeight()<450)
			  this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),this->suboptions[this->items[ind[0]]]->getHeight()+FLOATINGWINDOWITEMHEIGHT);
		}
		
		this->suboptions[this->items[ind[0]]]->addItem(red,green,blue);
		
		class MephItem *mi=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(this->suboptions[this->items[ind[0]]]->count());
		class MephItem *aux;
		if (MENUITEMWIDTH>this->suboptions[this->items[ind[0]]]->getWidth())
		{
      this->suboptions[this->items[ind[0]]]->resize(MENUITEMWIDTH,this->suboptions[this->items[ind[0]]]->getHeight());
			for (i=1;i<=count;i++)
			{
				aux=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(i);
				aux->resize(MENUITEMWIDTH,FLOATINGWINDOWITEMHEIGHT);
			}
		}
	}
}

void MephMenu::addDoubleSubOption(char * text,char * imagepath,char * index)
{
	int *ind,i,j=0;
	char count;
	
	for (i=0;i<strlen(index);i++)
		if ((index[i+1]<'0') || (index[i+1]>'9'))
			j++;
	if (j>0)	
	{
  	ind=new int[j];
	
  	this->getIndex(index,ind,&count);
		if (this->suboptions[this->items[ind[0]]]==NULL)
		{
			this->suboptions[this->items[ind[0]]]=new class MephFloatingWindow(this->mephapp);
			this->suboptions[this->items[ind[0]]]->addTo((class MephItemImp *)this->items[ind[0]]->getMephItemImp());
  		this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),FLOATINGWINDOWITEMHEIGHT);
			this->suboptions[this->items[ind[0]]]->catchEventChange(&(MephMenu::Change),this);
			this->suboptions[this->items[ind[0]]]->catchEventLeftRight(&(MephMenu::notifyKeyLeftRight),this);
		}
		else
		{
			if (this->suboptions[this->items[ind[0]]]->getHeight()<450)
			  this->suboptions[this->items[ind[0]]]->resize(this->suboptions[this->items[ind[0]]]->getWidth(),this->suboptions[this->items[ind[0]]]->getHeight()+FLOATINGWINDOWITEMHEIGHT);
		}
		
		this->suboptions[this->items[ind[0]]]->addDoubleItem(text,imagepath);
		
		class MephItem *mi=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(this->suboptions[this->items[ind[0]]]->count());
		class MephItem *aux;
		if (mi->getTextWidth()>this->suboptions[this->items[ind[0]]]->getWidth())
		{
      this->suboptions[this->items[ind[0]]]->resize(mi->getTextWidth()+20,this->suboptions[this->items[ind[0]]]->getHeight());
			for (i=1;i<=count;i++)
			{
				aux=(class MephItem *)this->suboptions[this->items[ind[0]]]->getItem(i);
				aux->resize(mi->getTextWidth(),FLOATINGWINDOWITEMHEIGHT);
			}
		}
	}
}

void MephMenu::getIndex(char *index,int *result,char *count)
{
	int i,j=0,k=0;
	char *aux=new char [strlen(index)+1];
	
	for (i=0;i<strlen(index);i++)
		if ((index[i+1]<'0') || (index[i+1]>'9'))
			j++;
	if (j>0)	
	{
		
	  j=0;
	  k=0;
	  for (i=0;i<strlen(index);i++,j++)
  	{
	  	aux[j]=index[i];
  		if ((index[i+1]<'0') || (index[i+1]>'9'))
	  	{
		  	aux[j+1]='\x0';
			  result[k]=atoi(aux);
  			j=0;
	  		k++;
		  }
		}
    count[0]=k;
	}
  else
    count[0]=0;			
}
/*****************************FUNCIONES DE LOS EVENTOS*********************/
void (*MephMenu::catchEventMouseDown (void (*eventmousedown)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephmenuimp->catchEventMouseDown(eventmousedown));
}

void (*MephMenu::catchEventMouseUp (void (*eventmouseup)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephmenuimp->catchEventMouseUp(eventmouseup));
}

void (*MephMenu::catchEventMouseOver (void (*eventmouseover)(class MephMenu * mephmenu,int x,int y,unsigned int mephbutton))) (void)
{
//	return(this->mephmenuimp->catchEventMouseOver(eventmouseover));
}

void (*MephMenu::catchEventPaint (void (*eventpaint)(class MephMenu * mephmenu,int x,int y,int width,int height,int count))) (void)
{
//	return(this->mephmenuimp->catchEventPaint(eventpaint));
}

void (*MephMenu::catchEventChange (void (*eventchange)(class MephItem * mephitem))) (void)
{
  this->neweventchange=eventchange;
}

void (*MephMenu::catchEventChange (void (MephComboBox::*eventchange)(class MephItem * mephitem),class MephComboBox * mephcombobox)) (void)
{
  this->mephcombobox=mephcombobox;
  this->neweventchangetomephcombobox=eventchange;
}

void (*MephMenu::catchEventConfigure (void (*eventconfigure)(class MephMenu * mephmenu,int x,int y,int width,int height))) (void)
{
//	return(this->mephmenuimp->catchEventConfigure(eventconfigure));
}

void (*MephMenu::catchEventKeyDown (void (*eventkeydown)(class MephMenu * mephmenu,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
//	return(this->mephmenuimp->catchEventKeyDown(eventkeydown));
}

void (*MephMenu::catchEventKeyUp   (void (*eventkeyup)  (class MephMenu * mephmenu,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
//	return(this->mephmenuimp->catchEventKeyUp(eventkeyup));
}
/**************************************************************************/

/*****************************BORRADO DE LOS EVENTOS***********************/
void MephMenu::undoEventMouseDown()
{
//	this->mephmenuimp->undoEventMouseDown();
}

void MephMenu::undoEventMouseUp()
{
//	this->mephmenuimp->undoEventMouseUp();
}

void MephMenu::undoEventMouseOver()
{
//	this->mephmenuimp->undoEventMouseOver();
}

void MephMenu::undoEventPaint()
{
//	this->mephmenuimp->undoEventPaint();
}

void MephMenu::undoEventConfigure()
{
//	this->mephmenuimp->undoEventConfigure();
}


void MephMenu::undoEventKeyDown()
{
//	this->mephmenuimp->undoEventKeyDown();
}

void MephMenu::undoEventKeyUp()
{
//	this->mephmenuimp->undoEventKeyUp();
}
/**************************************************************************/