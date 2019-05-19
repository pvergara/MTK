#include "MephCommandButtonImp_X11.h"
#include "MephCommandButton.h"
#include "MephGraphicParam.h"
#include <stdio.h>

void CommandButton_mouseDown (void);
void CommandButton_mouseUp (void);
void CommandButton_mouseOver (void);
void CommandButton_paint (void);
void CommandButton_configure (void);
void CommandButton_keyDown (void);
void CommandButton_keyUp (void);

XEvent CommandButton_event;

MephCommandButtonImp_X11::~MephCommandButtonImp_X11()
{
	delete this->mephcommandbutton;
	delete this->mephwindowimp;
	delete this->mephappimp;
}

MephCommandButtonImp_X11::MephCommandButtonImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL)
{
}

void MephCommandButtonImp_X11::initValues(const class MephCommandButton *mephcommandbutton)
{
  this->mephcommandbutton=(class MephCommandButton *) mephcommandbutton;
}
void MephCommandButtonImp_X11::initValues(const class MephCommandButton *mephcommandbutton, class MephAppImp const *mephappimp)
{
  this->mephcommandbutton=(class MephCommandButton *) mephcommandbutton;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephCommandButtonImp_X11::initValues(const class MephWindowImp * mephwindowimp)
{
	this->mephwindowimp=(class MephWindowImp *) mephwindowimp;
  this->parent=this->mephwindowimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephcommandbutton->getX(),this->mephcommandbutton->getY(),
	    this->mephcommandbutton->getWidth(),this->mephcommandbutton->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	/**********************************AQUUI!!!!! (mas eventos)***************************/
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask|StructureNotifyMask);
  /****************************************************************************************/

  this->mephappimp->contain(this);
}

void MephCommandButtonImp_X11::recieveNoMotion()
{
	this->mephcommandbutton->setMoused(NOTMOUSED);
//	this->mephcommandbutton->setMoused(NOTPRESSED);
	printf ("LEEEREEELEE!!!!!!\n");
	fflush(stdout);
}

void MephCommandButtonImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydown==NULL)
			  CommandButton_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephcommandbutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			i=XLookupString(&event.xkey,keychar,1,&keysym,NULL);
			if (keysym==XK_space)
  			this->mephcommandbutton->notify(NOTPRESSED);
			if (this->neweventkeyup==NULL)
			  CommandButton_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephcommandbutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			this->mephcommandbutton->notify(PRESSED);
			this->mephcommandbutton->setMoused(MOUSED);
			if (this->neweventmousedown==NULL)
			  CommandButton_mouseDown();
		  else
				this->neweventmousedown(this->mephcommandbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
			this->mephcommandbutton->notify(NOTPRESSED);
			/*ESTE IF MARCA UNA DIFERENCIA MUY IMPORTANTE ENTRE LO QUE ES UN CLICK DE UN BOT”N
			Y UN RELEASE DEL MISMO BOT”N. UN CLICK SIEMPRE SE PRODUCIRµ DENTRO DE LOS LÕMITES
			DEL BOT”N MIENTRAS QUE UN RELEASE NO TIENE PORQUE*/
			if ((event.xbutton.x>=this->mephcommandbutton->getWidth()) ||(event.xbutton.y>=this->mephcommandbutton->getHeight()))
  			this->mephcommandbutton->setMoused(NOTMOUSED);
			else
	  		this->mephcommandbutton->setMoused(MOUSED);

			if (this->neweventmouseup==NULL)
			  CommandButton_mouseUp();
		  else
				this->neweventmouseup(this->mephcommandbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
			if (this->mephcommandbutton->getMoused()==NOTMOUSED)
			{
   		  this->mephcommandbutton->setMoused(MOUSED);
			}
      if (this->mephcommandbutton->getPressed()==NOTPRESSED)
			{
  			if ((event.xmotion.state==Button1Mask) || (event.xmotion.state==Button2Mask) || (event.xmotion.state==Button3Mask) || (event.xmotion.state==Button4Mask) || (event.xmotion.state==Button5Mask) )
 		      this->mephcommandbutton->setMoused(PRESSED);
			}
			if (this->neweventmouseover==NULL)
			  CommandButton_mouseOver();
		  else
				this->neweventmouseover(this->mephcommandbutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
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
				if (this->mephcommandbutton->getDecorated())
  			  this->drawButtonDecoration();
  			if (this->neweventpaint==NULL)
	  		  CommandButton_paint();
		    else
			  	this->neweventpaint(this->mephcommandbutton,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephcommandbutton->setFocused(FOCUSED);
			if (this->mephcommandbutton->getDecorated())
  		  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephcommandbutton->setFocused(NOTFOCUSED);
 			if (this->mephcommandbutton->getDecorated())
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
			  CommandButton_configure();
		  else
				this->neweventconfigure(this->mephcommandbutton,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
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

Window MephCommandButtonImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephCommandButtonImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephCommandButtonImp_X11::getWindows()
{
	return (this->id);
}

int MephCommandButtonImp_X11::getHeight()
{
	this->mephcommandbutton->getHeight();
}

int MephCommandButtonImp_X11::getWidth()
{
	this->mephcommandbutton->getWidth();
}

void MephCommandButtonImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[2];
	int addfunction;


	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephcommandbutton->setBackground();
	if ((this->mephcommandbutton->getImagePath()!=NULL) && (strcmp(mephcommandbutton->getImagePath(),"")))
	this->mephcommandbutton->showImage();
	this->mephcommandbutton->setTextX((this->mephcommandbutton->getWidth()/2)-(this->mephcommandbutton->getTextWidth()/2));
	this->mephcommandbutton->setTextY((this->mephcommandbutton->getHeight()/2));
	this->mephcommandbutton->setBold(1);
	this->mephcommandbutton->showText();

	mephgraphicparam[0].setLine(0,0,this->mephcommandbutton->getWidth()-1,0);	
	mephgraphicparam[1].setLine(0,0,0,this->mephcommandbutton->getHeight()-1);	


  if (this->mephcommandbutton->getPressed()==PRESSED)
	  this->mephcommandbutton->setForeColor(0xFF,0xFF,0xFF);
	else
  	this->mephcommandbutton->setForeColor(0xAFFF,0xAFFF,0xAFFF);

	this->mephcommandbutton->drawLines(mephgraphicparam,2);

  mephgraphicparam[0].setLine(this->mephcommandbutton->getWidth()-1,this->mephcommandbutton->getHeight()-1,this->mephcommandbutton->getWidth()-1,0);	
  mephgraphicparam[1].setLine(this->mephcommandbutton->getWidth()-1,this->mephcommandbutton->getHeight()-1,0,this->mephcommandbutton->getHeight()-1);

  if (this->mephcommandbutton->getPressed()==PRESSED)
	  this->mephcommandbutton->setForeColor(0xAFFF,0xAFFF,0xAFFF);
	else
	  this->mephcommandbutton->setForeColor(0xFF,0xFF,0xFF);

	this->mephcommandbutton->drawLines(mephgraphicparam,2);
	
	if (this->mephcommandbutton->getFocused())
	{
    mephgraphicparam[0].setRectangle(2,2,this->mephcommandbutton->getWidth()-5,this->mephcommandbutton->getHeight()-5);	
  	this->mephcommandbutton->drawRectangles(mephgraphicparam,1);
	}
	
  /***************************************** ÈLTIMAMENTE A ESTO CREO QUE LO LLAMAN ROLLBACK *******************************/
	
	if (this->mephcommandbutton->getPressed()==PRESSED)
	{
   	addfunction=this->mephcommandbutton->getDrawAddFunction();
    this->mephcommandbutton->setDrawAddFunction(MEPHFUNCTIONAND);
		this->mephcommandbutton->setForeColor(0xDFFF,0xDFFF,0xDFFF);
	  mephgraphicparam[0].setRectangle(1,1,this->mephcommandbutton->getWidth()-2,this->mephcommandbutton->getHeight()-2);
  	this->mephcommandbutton->fillRectangles(mephgraphicparam,1);
		this->mephcommandbutton->setDrawAddFunction(addfunction);
	}

  if (this->mephcommandbutton->getMoused()==MOUSED)
	{
  	addfunction=this->mephcommandbutton->getDrawAddFunction();
 		this->mephcommandbutton->setDrawAddFunction(MEPHFUNCTIONOR);
	  this->mephcommandbutton->setForeColor(0x1fff,0x1fff,0x1fff);
  	mephgraphicparam[0].setRectangle(1,1,this->mephcommandbutton->getWidth()-2,this->mephcommandbutton->getHeight()-2);
 		this->mephcommandbutton->fillRectangles(mephgraphicparam,1);
	  this->mephcommandbutton->setDrawAddFunction(addfunction);
  }
	
	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
	
}

void MephCommandButtonImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephcommandbutton->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephcommandbutton->getX(),mephcommandbutton->getY(),mephcommandbutton->getWidth(),
		  mephcommandbutton->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephcommandbutton->getX(),mephcommandbutton->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephcommandbutton->getWidth(),mephcommandbutton->getHeight());
		}
	}
	
	if ((mephupdateparam & MephUPressed) || (mephupdateparam & MephUMoused))
		if (this->mephcommandbutton->getDecorated())
  		this->drawButtonDecoration();
	
	XFlush(disp);
}

const Display * MephCommandButtonImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephCommandButtonImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephcommandbutton->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephCommandButtonImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephCommandButton * mephcommandbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (CommandButton_mouseDown);
}

void (*MephCommandButtonImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephCommandButton * mephcommandbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (CommandButton_mouseUp);
}

void (*MephCommandButtonImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephCommandButton * mephcommandbutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (CommandButton_mouseOver);
}

void (*MephCommandButtonImp_X11::catchEventPaint (void (*eventpaint)(class MephCommandButton * mephcommandbutton,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (CommandButton_paint);
}

void (*MephCommandButtonImp_X11::catchEventConfigure (void (*eventconfigure)(class MephCommandButton * mephcommandbutton,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (CommandButton_configure);
}

void (*MephCommandButtonImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephCommandButton * mephcommandbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (CommandButton_keyDown);
}

void (*MephCommandButtonImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephCommandButton * mephcommandbutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (CommandButton_keyUp);
}

/***********************************************************************************************/

void MephCommandButtonImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephCommandButtonImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephCommandButtonImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephCommandButtonImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephCommandButtonImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephCommandButtonImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephCommandButtonImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void CommandButton_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void CommandButton_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void CommandButton_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void CommandButton_paint (void)
{
	if (!CommandButton_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void CommandButton_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void CommandButton_keyDown (void)
{
  printf ("Boton keypress \n");
	fflush(stdout);
}

void CommandButton_keyUp (void)
{
  printf ("Mousekeyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/