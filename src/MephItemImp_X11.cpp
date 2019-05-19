#include "MephItemImp_X11.h"
#include "MephItem.h"
#include "MephGraphicParam.h"
#include "MephListBox.h"
#include <stdio.h>

XEvent Item_event;

MephItemImp_X11::~MephItemImp_X11()
{
	delete this->mephitem;
	delete this->mephvisobjimp;
	delete this->mephappimp;
}

MephItemImp_X11::MephItemImp_X11():neweventmousedown(NULL),neweventmousedowntomephlistbox(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpainttomephlistbox(NULL),neweventpainttomephfloatingwindow(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeydowntomephlistbox(NULL),neweventkeyup(NULL),mephlistbox(NULL),mephfloatingwindow(NULL),neweventpainttomephmenu(NULL),neweventpaint(NULL),neweventmousedowntomephmenu(NULL)
{
}

void MephItemImp_X11::initValues(const class MephItem *mephitem, class MephAppImp const *mephappimp)
{
  this->mephitem=(class MephItem *) mephitem;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephItemImp_X11::initValues(const class MephVisObjImp * mephvisobjimp)
{
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
  this->parent=this->mephvisobjimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephitem->getX(),this->mephitem->getY(),
	    this->mephitem->getWidth(),this->mephitem->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|StructureNotifyMask);
  this->mephappimp->contain(this);
	/*ESTO ES NECESARIO PARA QUE SE PUEDAN RECIBIR EVENTOS DE TECLADO*/
	this->mephappimp->setTabIndex(this->id[0],0,1);
}

void MephItemImp_X11::recieveNoMotion()
{
}

void MephItemImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydowntomephlistbox!=NULL)
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				(this->mephlistbox->*neweventkeydowntomephlistbox)(this->mephitem,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			if (this->neweventkeyup!=NULL)
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephitem,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			if (this->neweventmousedowntomephlistbox!=NULL)
				(this->mephlistbox->*neweventmousedowntomephlistbox)(this->mephitem,event.xbutton.x,event.xbutton.y,event.xbutton.button);
			if (this->neweventmousedowntomephmenu!=NULL)
				(this->mephmenu->*neweventmousedowntomephmenu)(this->mephitem,event.xbutton.x,event.xbutton.y,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
			if (this->neweventmouseup!=NULL)
				this->neweventmouseup(this->mephitem,event.xbutton.x,event.xbutton.y,event.xbutton.button);
		}break;

		case MotionNotify:
		{
			if (this->neweventmouseover!=NULL)
				this->neweventmouseover(this->mephitem,event.xbutton.x,event.xbutton.y,event.xbutton.state);
		}break;

		case Expose:
		{
			if (event.xexpose.count==0)
			{
//			  this->drawButtonDecoration();
  			if (this->neweventpaint!=NULL)
				{
			  	this->neweventpaint(this->mephitem,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
				}
  			if (this->neweventpainttomephlistbox!=NULL)
				{
			  	(this->mephlistbox->*neweventpainttomephlistbox)(this->mephitem,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
				}
  			if (this->neweventpainttomephfloatingwindow!=NULL)
				{
			  	(this->mephfloatingwindow->*neweventpainttomephfloatingwindow)(this->mephitem,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
				}
  			if (this->neweventpainttomephmenu!=NULL)
				{
			  	(this->mephmenu->*neweventpainttomephmenu)(this->mephitem,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
				}
			}
		}break;

		case FocusIn:
		{
//		  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
//		  this->drawButtonDecoration();
		  printf ("focusout\n");
			fflush(stdout);
		}break;

		case PropertyNotify:
		{
		  printf ("property\n");
			fflush(stdout);
		}break;

		case CirculateNotify:
		{
		  printf ("circulate\n");
			fflush(stdout);
		}break;

		case ConfigureNotify:
		{
			if (this->neweventconfigure!=NULL)
				this->neweventconfigure(this->mephitem,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
		}break;

		case CreateNotify:
		{
		  printf ("create\n");
			fflush(stdout);
		}break;

		case DestroyNotify:
		{
		/*QUIZµS NO HACE FALTA EN EL SENTIDO DE QUE YA DE POR SI LA VENTANA DESTRUYE TODO LO QUE LLEVA DENTRO*/
			XDestroyWindow((Display *) this->mephappimp->getDisplay(),this->id[0]);
		  printf ("destroy\n");
			fflush(stdout);
		}break;

		case GravityNotify:
		{
		  printf ("gravity\n");
			fflush(stdout);
		}break;

		case MapNotify:
		{
		  printf ("mapnotify\n");
			fflush(stdout);
		}break;

		case UnmapNotify:
		{
		  printf ("Unmap\n");
			fflush(stdout);
		}break;

		case ClientMessage:
		{
		  printf ("ClientMessage\n");
			fflush(stdout);
		}
	};
}

Window MephItemImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephItemImp_X11::getWindow(int index,char *result)
{
	if (this->id[index])
	{
		result[0]=1;
	  return (this->id[index]);
	}
	else
	{
		result[0]=0;
		return(0);
	}
}

map <int,Window> MephItemImp_X11::getWindows()
{
	return (this->id);
}

int MephItemImp_X11::getHeight()
{
	this->mephitem->getHeight();
}

int MephItemImp_X11::getWidth()
{
	this->mephitem->getWidth();
}

void MephItemImp_X11::drawButtonDecoration()
{
/*	this->mephitem->clearScreen();
  this->mephitem->setBackground();
	if ((this->mephitem->getImagePath()!=NULL) || (this->mephitem->getImagePath()!=""))
	this->mephitem->showImage();
	this->mephitem->setTextX((this->mephitem->getWidth()/2)-(this->mephitem->getTextWidth()/2));
	this->mephitem->setTextY((this->mephitem->getHeight()/2));
	this->mephitem->showText();*/
}

void MephItemImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephitem->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephitem->getX(),mephitem->getY(),mephitem->getWidth(),
		  mephitem->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephitem->getX(),mephitem->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephitem->getWidth(),mephitem->getHeight());
		}
	}
	
	XFlush(disp);
}

const Display * MephItemImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

/***************************************MTODOS DE EVENTOS**************************************/
void (*MephItemImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (NULL);
}

void (*MephItemImp_X11::catchEventMouseDown (void (MephListBox::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephListBox *mephlistbox)) (void)
{
	this->neweventmousedowntomephlistbox=eventmousedown;
	this->mephlistbox=mephlistbox;
	return (NULL);
}

void (*MephItemImp_X11::catchEventMouseDown (void (MephMenu::*eventmousedown)(class MephItem * mephitem,int x,int y,unsigned int mephbutton),class MephMenu *mephmenu)) (void)
{
	this->neweventmousedowntomephmenu=eventmousedown;
	this->mephmenu=mephmenu;
	return (NULL);
}
	
void (*MephItemImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (NULL);
}

void (*MephItemImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephItem * mephitem,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (NULL);
}

void (*MephItemImp_X11::catchEventPaint (void (*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (NULL);
}

void (*MephItemImp_X11::catchEventPaint (void (MephListBox::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephListBox *mephlistbox)) (void)
{
	this->neweventpainttomephlistbox=eventpaint;
	this->mephlistbox=mephlistbox;
	return (NULL);
}

void (*MephItemImp_X11::catchEventPaint (void (MephFloatingWindow::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephFloatingWindow *mephfloatingwindow)) (void)
{
	this->neweventpainttomephfloatingwindow=eventpaint;
	this->mephfloatingwindow=mephfloatingwindow;
	return (NULL);
}

void (*MephItemImp_X11::catchEventPaint (void (MephMenu::*eventpaint)(class MephItem * mephitem,int x,int y,int width,int height,int count),class MephMenu *mephmenu)) (void)
{
	this->neweventpainttomephmenu=eventpaint;
	this->mephmenu=mephmenu;
	return (NULL);
}

void (*MephItemImp_X11::catchEventConfigure (void (*eventconfigure)(class MephItem * mephitem,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (NULL);
}

void (*MephItemImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (NULL);
}

void (*MephItemImp_X11::catchEventKeyDown (void (MephListBox::*eventkeydown)(class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask),class MephListBox *mephlistbox)) (void)
{
	this->neweventkeydowntomephlistbox=eventkeydown;
	this->mephlistbox=mephlistbox;
	return (NULL);
}

void (*MephItemImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephItem * mephitem,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (NULL);
}

/***********************************************************************************************/

void MephItemImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephItemImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephItemImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephItemImp_X11::undoEventPaint(void)
{
	this->neweventpainttomephlistbox=NULL;
}

void MephItemImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephItemImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephItemImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
