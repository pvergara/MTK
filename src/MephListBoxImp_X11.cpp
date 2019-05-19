#include "MephListBoxImp_X11.h"
#include "MephListBox.h"
#include "MephGraphicParam.h"
#include <stdio.h>

XEvent ListBox_event;

MephListBoxImp_X11::~MephListBoxImp_X11()
{
	delete this->mephlistbox;
	delete this->mephvisobjimp;
	delete this->mephappimp;
}

MephListBoxImp_X11::MephListBoxImp_X11()
{
}

void MephListBoxImp_X11::initValues(const class MephListBox *mephlistbox, class MephAppImp const *mephappimp)
{
  this->mephlistbox=(class MephListBox *) mephlistbox;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephListBoxImp_X11::initValues(const class MephVisObjImp * mephvisobjimp)
{
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
  this->parent=this->mephvisobjimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephlistbox->getX(),this->mephlistbox->getY(),
	    this->mephlistbox->getWidth(),this->mephlistbox->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
/*	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|StructureNotifyMask);
  this->mephappimp->contain(this);*/
}

/*void MephListBoxImp_X11::recieveNoMotion()
{
}

void MephListBoxImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydown!=NULL)
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephlistbox,keychar,keysym,event.xkey.state);
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
				this->neweventkeyup(this->mephlistbox,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			if (this->neweventmousedown!=NULL)
				this->neweventmousedown(this->mephlistbox,event.xbutton.x,event.xbutton.y,event.xbutton.state);

		}break;

		case ButtonRelease:
		{
			if (this->neweventmouseup!=NULL)
				this->neweventmouseup(this->mephlistbox,event.xbutton.x,event.xbutton.y,event.xbutton.state);
		}break;

		case MotionNotify:
		{
			if (this->neweventmouseover!=NULL)
				this->neweventmouseover(this->mephlistbox,event.xbutton.x,event.xbutton.y,event.xbutton.state);
		}break;

		case Expose:
		{
			if (event.xexpose.count==0)
			{
//			  this->drawButtonDecoration();
  			if (this->neweventpaint!=NULL)
			  	this->neweventpaint(this->mephlistbox,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
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
				this->neweventconfigure(this->mephlistbox,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
		}break;

		case CreateNotify:
		{
		  printf ("create\n");
			fflush(stdout);
		}break;

		case DestroyNotify:
		{
		/*QUIZµS NO HACE FALTA EN EL SENTIDO DE QUE YA DE POR SI LA VENTANA DESTRUYE TODO LO QUE LLEVA DENTRO
			//			XDestroyWindow(MephAppImpX11_getDisplay(),this->id);
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
}*/

Window MephListBoxImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephListBoxImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephListBoxImp_X11::getWindows()
{
	return (this->id);
}

int MephListBoxImp_X11::getHeight()
{
	this->mephlistbox->getHeight();
}

int MephListBoxImp_X11::getWidth()
{
	this->mephlistbox->getWidth();
}

/*void MephListBoxImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[2];
	int addfunction;


	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephlistbox->setBackground();
	if ((this->mephlistbox->getImagePath()!=NULL) || (this->mephlistbox->getImagePath()!=""))
	this->mephlistbox->showImage();
	this->mephlistbox->setTextX((this->mephlistbox->getWidth()/2)-(this->mephlistbox->getTextWidth()/2));
	this->mephlistbox->setTextY((this->mephlistbox->getHeight()/2));
	this->mephlistbox->setBold(1);
	this->mephlistbox->showText();

	mephgraphicparam[0].setLine(0,0,this->mephlistbox->getWidth()-1,0);	
	mephgraphicparam[1].setLine(0,0,0,this->mephlistbox->getHeight()-1);	


  if (this->mephlistbox->getPressed()==PRESSED)
	  this->mephlistbox->setForeColor(0xFF,0xFF,0xFF);
	else
  	this->mephlistbox->setForeColor(0xAFFF,0xAFFF,0xAFFF);

	this->mephlistbox->drawLines(mephgraphicparam,2);

  mephgraphicparam[0].setLine(this->mephlistbox->getWidth()-1,this->mephlistbox->getHeight()-1,this->mephlistbox->getWidth()-1,0);	
  mephgraphicparam[1].setLine(this->mephlistbox->getWidth()-1,this->mephlistbox->getHeight()-1,0,this->mephlistbox->getHeight()-1);

  if (this->mephlistbox->getPressed()==PRESSED)
	  this->mephlistbox->setForeColor(0xAFFF,0xAFFF,0xAFFF);
	else
	  this->mephlistbox->setForeColor(0xFF,0xFF,0xFF);

	this->mephlistbox->drawLines(mephgraphicparam,2);
	
	if (this->mephlistbox->getFocused())
	{
    mephgraphicparam[0].setRectangle(2,2,this->mephlistbox->getWidth()-5,this->mephlistbox->getHeight()-5);	
  	this->mephlistbox->drawRectangles(mephgraphicparam,1);
	}
	
  /***************************************** éLTIMAMENTE A ESTO CREO QUE LO LLAMAN ROLLOVER *******************************/
	
/*	if (this->mephlistbox->getPressed()==PRESSED)
	{
   	addfunction=this->mephlistbox->getDrawAddFunction();
    this->mephlistbox->setDrawAddFunction(MEPHFUNCTIONAND);
		this->mephlistbox->setForeColor(0xDFFF,0xDFFF,0xDFFF);
	  mephgraphicparam[0].setRectangle(1,1,this->mephlistbox->getWidth()-2,this->mephlistbox->getHeight()-2);
  	this->mephlistbox->fillRectangles(mephgraphicparam,1);
		this->mephlistbox->setDrawAddFunction(addfunction);
	}

  if (this->mephlistbox->getMoused()==MOUSED)
	{
  	addfunction=this->mephlistbox->getDrawAddFunction();
 		this->mephlistbox->setDrawAddFunction(MEPHFUNCTIONOR);
	  this->mephlistbox->setForeColor(0x1fff,0x1fff,0x1fff);
  	mephgraphicparam[0].setRectangle(1,1,this->mephlistbox->getWidth()-2,this->mephlistbox->getHeight()-2);
 		this->mephlistbox->fillRectangles(mephgraphicparam,1);
	  this->mephlistbox->setDrawAddFunction(addfunction);
  }
	
	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
	
}*/

void MephListBoxImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephlistbox->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephlistbox->getX(),mephlistbox->getY(),mephlistbox->getWidth(),
		  mephlistbox->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephlistbox->getX(),mephlistbox->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephlistbox->getWidth(),mephlistbox->getHeight());
		}
	}
	
	XFlush(disp);
}

const Display * MephListBoxImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

void MephListBoxImp_X11::destroyWindow(const class MephItemImp *mephitemimp)
{
	class MephItemImp *mii=(class MephItemImp *)mephitemimp;
	XDestroyWindow((Display *)this->mephappimp->getDisplay(),mii->getWindow());
}
