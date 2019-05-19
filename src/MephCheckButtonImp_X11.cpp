#include "MephCheckButtonImp_X11.h"
#include "MephCheckButton.h"
#include "MephCheckButtonImp.h"
#include "MephGraphicParam.h"
#include <stdio.h>

void CheckButton_mouseDown (void);
void CheckButton_mouseUp (void);
void CheckButton_mouseOver (void);
void CheckButton_paint (void);
void CheckButton_configure (void);
void CheckButton_keyDown (void);
void CheckButton_keyUp (void);

XEvent CheckButton_event;

MephCheckButtonImp_X11::~MephCheckButtonImp_X11()
{
	delete this->mephcheckbutton;
	delete this->mephwindowimp;
	delete this->mephappimp;
}

MephCheckButtonImp_X11::MephCheckButtonImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL)
{
}

void MephCheckButtonImp_X11::initValues(const class MephCheckButton *mephcheckbutton)
{
  this->mephcheckbutton=(class MephCheckButton *) mephcheckbutton;
}
void MephCheckButtonImp_X11::initValues(const class MephCheckButton *mephcheckbutton, class MephAppImp const *mephappimp)
{
  this->mephcheckbutton=(class MephCheckButton *) mephcheckbutton;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephCheckButtonImp_X11::initValues(const class MephWindowImp * mephwindowimp)
{
	this->mephwindowimp=(class MephWindowImp *) mephwindowimp;
  this->parent=this->mephwindowimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephcheckbutton->getX(),this->mephcheckbutton->getY(),
	    this->mephcheckbutton->getWidth(),this->mephcheckbutton->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	/**********************************AQUUI!!!!! (mas eventos)***************************/
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask|StructureNotifyMask);
  /****************************************************************************************/

	/*Es pasado al motor de eventos de mephappimp_X11*/
  this->mephappimp->contain(this);
}

void MephCheckButtonImp_X11::recieveNoMotion()
{
	printf ("LEEEREEELEE!!!!!!\n");
	fflush(stdout);
}

void MephCheckButtonImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
			i=XLookupString(&event.xkey,keychar,1,&keysym,NULL);
			if (keysym==XK_space)
			{
  			if (this->mephcheckbutton->getStates()==3)
	  		{
		  		if (this->mephcheckbutton->getState()==2)
			  		this->mephcheckbutton->notify(0);
				  else
  					this->mephcheckbutton->notify(this->mephcheckbutton->getState()+1);
	  		}
		  	else
			  {
  				if (this->mephcheckbutton->getState()==1)
	  				this->mephcheckbutton->notify(0);
		  		else
			  		this->mephcheckbutton->notify(1);
			  }
			}

			if (this->neweventkeydown==NULL)
			  CheckButton_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephcheckbutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			if (this->neweventkeyup==NULL)
			  CheckButton_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephcheckbutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			if (this->mephcheckbutton->getStates()==3)
			{
				if (this->mephcheckbutton->getState()==2)
					this->mephcheckbutton->notify(0);
				else
					this->mephcheckbutton->notify(this->mephcheckbutton->getState()+1);
			}
			else
			{
				if (this->mephcheckbutton->getState()==1)
					this->mephcheckbutton->notify(0);
				else
					this->mephcheckbutton->notify(1);
			}
			
/*			this->mephcheckbutton->notify(PRESSED);
			this->mephcheckbutton->setMoused(MOUSED);*/
			if (this->neweventmousedown==NULL)
			  CheckButton_mouseDown();
		  else
				this->neweventmousedown(this->mephcheckbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
//			this->mephcheckbutton->notify(NOTPRESSED);
			/*ESTE IF MARCA UNA DIFERENCIA MUY IMPORTANTE ENTRE LO QUE ES UN CLICK DE UN BOT”N
			Y UN RELEASE DEL MISMO BOT”N. UN CLICK SIEMPRE SE PRODUCIRµ DENTRO DE LOS LÕMITES
			DEL BOT”N MIENTRAS QUE UN RELEASE NO TIENE PORQUE*/
/*			if ((event.xbutton.x>=this->mephcheckbutton->getWidth()) ||(event.xbutton.y>=this->mephcheckbutton->getHeight()))
  			this->mephcheckbutton->setMoused(NOTMOUSED);
			else
	  		this->mephcheckbutton->setMoused(MOUSED);*/

			if (this->neweventmouseup==NULL)
			  CheckButton_mouseUp();
		  else
				this->neweventmouseup(this->mephcheckbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
	//		if (this->mephcheckbutton->getMoused()==NOTMOUSED)
			{
//   		  this->mephcheckbutton->setMoused(MOUSED);
			}
//      if (this->mephcheckbutton->getPressed()==NOTPRESSED)
			{
/*  			if ((event.xmotion.state==Button1Mask) || (event.xmotion.state==Button2Mask) || (event.xmotion.state==Button3Mask) || (event.xmotion.state==Button4Mask) || (event.xmotion.state==Button5Mask) )
 		      this->mephcheckbutton->setMoused(PRESSED);*/
			}
			if (this->neweventmouseover==NULL)
			  CheckButton_mouseOver();
		  else
				this->neweventmouseover(this->mephcheckbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
		}break;

		case EnterNotify:
		{
		  printf ("enternotify\n");
		  fflush(stdout);
		}break;

		case LeaveNotify:
		{
		  printf ("leavenotify\n");
			fflush(stdout);
		}break;

		case Expose:
		{
			if (event.xexpose.count==0)
			{
				if (this->mephcheckbutton->getDecorated())
		  	  this->drawButtonDecoration();
  			if (this->neweventpaint==NULL)
	  		  CheckButton_paint();
		    else
			  	this->neweventpaint(this->mephcheckbutton,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephcheckbutton->setFocused(FOCUSED);
			if (this->mephcheckbutton->getDecorated())
  		  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephcheckbutton->setFocused(NOTFOCUSED);
 			if (this->mephcheckbutton->getDecorated())
	  	  this->drawButtonDecoration();
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
			if (this->neweventconfigure==NULL)
			  CheckButton_configure();
		  else
				this->neweventconfigure(this->mephcheckbutton,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
			/*AQUÕ TIENE QUE EXISTIR UN NOTIFY PARA QUE SE ALMACENEN LOS CAMBIOS PRODUCIDOS EN "X","Y","WIDTH" y "HEIGHT" AUNQUE PARTIMOS
			DE LA BASE QUE UN BOT”N RARA VEZ SE MODIFICA SI NO SE LE DICE ANTES (OSEA, UNA VENTANA SE PUEDE MODIFICAR PORQUE EL GESTOR
			DE VENTANAS ESPECIFICA QUE TIENE QUE MOVERSE O CAMBIAR SU TAMA—O PERO UN BOT”N... CREO QUE NO)*/
		}break;

		case CreateNotify:
		{
		  printf ("create\n");
			fflush(stdout);
		}break;

		case DestroyNotify:
		{
		/*QUIZµS NO HACE FALTA EN EL SENTIDO DE QUE YA DE POR SI LA VENTANA DESTRUYE TODO LO QUE LLEVA DENTRO*/
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

		case ReparentNotify:
		{
		  printf ("reparent\n");
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


Window MephCheckButtonImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephCheckButtonImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephCheckButtonImp_X11::getWindows()
{
	return (this->id);
}

int MephCheckButtonImp_X11::getHeight()
{
	this->mephcheckbutton->getHeight();
}

int MephCheckButtonImp_X11::getWidth()
{
	this->mephcheckbutton->getWidth();
}

void MephCheckButtonImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[3];
	unsigned long colorindex;
	int addfunction;


	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephcheckbutton->setBackground();
	if ((this->mephcheckbutton->getImagePath()!=NULL) && (strcmp(mephcheckbutton->getImagePath(),"")))
  	this->mephcheckbutton->showImage();
	this->mephcheckbutton->setTextX(25);
	this->mephcheckbutton->setTextY(7);
	this->mephcheckbutton->showText();

	this->mephcheckbutton->setForeColor(0x7000,0x7000,0x7000);
	mephgraphicparam[0].setLine(1,1,15,1);	
	mephgraphicparam[1].setLine(1,2,1,15);	
	this->mephcheckbutton->drawLines(mephgraphicparam,2);
	this->mephcheckbutton->setForeColor(0x3000,0x3000,0x3000);
	mephgraphicparam[0].setLine(2,2,14,2);	
	mephgraphicparam[1].setLine(2,2,2,14);	
	this->mephcheckbutton->drawLines(mephgraphicparam,2);
	
	this->mephcheckbutton->setForeColor(0xD000,0xD000,0xD000);
	mephgraphicparam[0].setLine(15,2,15,15);	
	mephgraphicparam[1].setLine(15,15,2,15);	
	this->mephcheckbutton->drawLines(mephgraphicparam,2);
	this->mephcheckbutton->setForeColor(0x7000,0x7000,0x7000);
	mephgraphicparam[0].setLine(14,3,14,14);	
	mephgraphicparam[1].setLine(14,14,3,14);	
	this->mephcheckbutton->drawLines(mephgraphicparam,2);
	
  this->mephcheckbutton->setForeColor(0xFFFF,0xFFFF,0xFFFF);
	mephgraphicparam[0].setRectangle(3,3,11,11);
 	this->mephcheckbutton->fillRectangles(mephgraphicparam,1);
	
	if (this->mephcheckbutton->getFocused())
	{
    this->mephcheckbutton->setForeColor(0,0,0);
	  mephgraphicparam[0].setRectangle(17,1,this->mephcheckbutton->getWidth()-20,this->mephcheckbutton->getHeight()-3);
 	  this->mephcheckbutton->drawRectangles(mephgraphicparam,1);
	}
	
  if (this->mephcheckbutton->getState()>0)
	{
    if (this->mephcheckbutton->getState()==2)
		{
  	  addfunction=this->mephcheckbutton->getDrawAddFunction();
 	  	this->mephcheckbutton->setDrawAddFunction(MEPHFUNCTIONAND);
      this->mephcheckbutton->setForeColor(0xBFFF,0xBFFF,0xBFFF);
			mephgraphicparam[0].setRectangle(3,3,11,11);
    	this->mephcheckbutton->fillRectangles(mephgraphicparam,1);
  	  this->mephcheckbutton->setDrawAddFunction(addfunction);
		}
  	this->mephcheckbutton->setForeColor(0,0,0);
  	mephgraphicparam[0].setLine(5,5,11,11);	
  	mephgraphicparam[1].setLine(6,5,10,11);	
  	mephgraphicparam[2].setLine(5,6,11,10);	
  	this->mephcheckbutton->drawLines(mephgraphicparam,3);
	  mephgraphicparam[0].setLine(11,5,5,11);	
	  mephgraphicparam[1].setLine(10,5,6,11);	
	  mephgraphicparam[2].setLine(11,6,5,10);	
  	this->mephcheckbutton->drawLines(mephgraphicparam,3);
	}

	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
}

void MephCheckButtonImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephcheckbutton->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephcheckbutton->getX(),mephcheckbutton->getY(),mephcheckbutton->getWidth(),
		  mephcheckbutton->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephcheckbutton->getX(),mephcheckbutton->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephcheckbutton->getWidth(),mephcheckbutton->getHeight());
		}
	}
	
	if ((mephupdateparam & MephUPressed) || (mephupdateparam & MephUMoused))
		if (this->mephcheckbutton->getDecorated())
  		this->drawButtonDecoration();
	
	XFlush(disp);
}

const Display * MephCheckButtonImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephCheckButtonImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephcheckbutton->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephCheckButtonImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (CheckButton_mouseDown);
}

void (*MephCheckButtonImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (CheckButton_mouseUp);
}

void (*MephCheckButtonImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephCheckButton * mephcheckbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (CheckButton_mouseOver);
}

void (*MephCheckButtonImp_X11::catchEventPaint (void (*eventpaint)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (CheckButton_paint);
}

void (*MephCheckButtonImp_X11::catchEventConfigure (void (*eventconfigure)(class MephCheckButton * mephcheckbutton,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (CheckButton_configure);
}

void (*MephCheckButtonImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (CheckButton_keyDown);
}

void (*MephCheckButtonImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephCheckButton * mephcheckbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (CheckButton_keyUp);
}

/***********************************************************************************************/

void MephCheckButtonImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephCheckButtonImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephCheckButtonImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephCheckButtonImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephCheckButtonImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephCheckButtonImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephCheckButtonImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void CheckButton_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void CheckButton_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void CheckButton_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void CheckButton_paint (void)
{
	if (!CheckButton_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void CheckButton_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void CheckButton_keyDown (void)
{
  printf ("Mousekeypress \n");
	fflush(stdout);
}

void CheckButton_keyUp (void)
{
  printf ("Mousekeyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/