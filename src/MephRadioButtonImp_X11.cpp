#include "MephRadioButtonImp_X11.h"
#include "MephRadioButton.h"
#include "MephRadioButtonImp.h"
#include "MephGraphicParam.h"
#include <stdio.h>

void RadioButton_mouseDown (void);
void RadioButton_mouseUp (void);
void RadioButton_mouseOver (void);
void RadioButton_paint (void);
void RadioButton_configure (void);
void RadioButton_keyDown (void);
void RadioButton_keyUp (void);

XEvent RadioButton_event;

MephRadioButtonImp_X11::~MephRadioButtonImp_X11()
{
	delete this->mephradiobutton;
	delete this->mephwindowimp;
	delete this->mephappimp;
}

MephRadioButtonImp_X11::MephRadioButtonImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL)
{
}

void MephRadioButtonImp_X11::initValues(const class MephRadioButton *mephradiobutton)
{
  this->mephradiobutton=(class MephRadioButton *) mephradiobutton;
}
void MephRadioButtonImp_X11::initValues(const class MephRadioButton *mephradiobutton, class MephAppImp const *mephappimp)
{
  this->mephradiobutton=(class MephRadioButton *) mephradiobutton;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephRadioButtonImp_X11::initValues(const class MephWindowImp * mephwindowimp)
{
	this->mephwindowimp=(class MephWindowImp *) mephwindowimp;
  this->parent=this->mephwindowimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephradiobutton->getX(),this->mephradiobutton->getY(),
	    this->mephradiobutton->getWidth(),this->mephradiobutton->getHeight(),0,
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

void MephRadioButtonImp_X11::recieveNoMotion()
{
	printf ("LEEEREEELEE!!!!!!\n");
	fflush(stdout);
}

void MephRadioButtonImp_X11::recieveEvent(XEvent event)
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
  			this->mephradiobutton->check();
			
			if (this->neweventkeydown==NULL)
			  RadioButton_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephradiobutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			if (this->neweventkeyup==NULL)
			  RadioButton_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephradiobutton,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			this->mephradiobutton->check();
			

			if (this->neweventmousedown==NULL)
			  RadioButton_mouseDown();
		  else
				this->neweventmousedown(this->mephradiobutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
//			this->mephradiobutton->notify(NOTPRESSED);
			/*ESTE IF MARCA UNA DIFERENCIA MUY IMPORTANTE ENTRE LO QUE ES UN CLICK DE UN BOT”N
			Y UN RELEASE DEL MISMO BOT”N. UN CLICK SIEMPRE SE PRODUCIRµ DENTRO DE LOS LÕMITES
			DEL BOT”N MIENTRAS QUE UN RELEASE NO TIENE PORQUE*/
/*			if ((event.xbutton.x>=this->mephradiobutton->getWidth()) ||(event.xbutton.y>=this->mephradiobutton->getHeight()))
  			this->mephradiobutton->setMoused(NOTMOUSED);
			else
	  		this->mephradiobutton->setMoused(MOUSED);*/

			if (this->neweventmouseup==NULL)
			  RadioButton_mouseUp();
		  else
				this->neweventmouseup(this->mephradiobutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
	//		if (this->mephradiobutton->getMoused()==NOTMOUSED)
			{
//   		  this->mephradiobutton->setMoused(MOUSED);
			}
//      if (this->mephradiobutton->getPressed()==NOTPRESSED)
			{
/*  			if ((event.xmotion.state==Button1Mask) || (event.xmotion.state==Button2Mask) || (event.xmotion.state==Button3Mask) || (event.xmotion.state==Button4Mask) || (event.xmotion.state==Button5Mask) )
 		      this->mephradiobutton->setMoused(PRESSED);*/
			}
			if (this->neweventmouseover==NULL)
			  RadioButton_mouseOver();
		  else
				this->neweventmouseover(this->mephradiobutton,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
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
				if (this->mephradiobutton->getDecorated())
  			  this->drawButtonDecoration();
  			if (this->neweventpaint==NULL)
	  		  RadioButton_paint();
		    else
			  	this->neweventpaint(this->mephradiobutton,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephradiobutton->setFocused(FOCUSED);
			if (this->mephradiobutton->getDecorated())
  		  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephradiobutton->setFocused(NOTFOCUSED);
			if (this->mephradiobutton->getDecorated())
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
			  RadioButton_configure();
		  else
				this->neweventconfigure(this->mephradiobutton,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
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

Window MephRadioButtonImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephRadioButtonImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephRadioButtonImp_X11::getWindows()
{
	return (this->id);
}

int MephRadioButtonImp_X11::getHeight()
{
	this->mephradiobutton->getHeight();
}

int MephRadioButtonImp_X11::getWidth()
{
	this->mephradiobutton->getWidth();
}

void MephRadioButtonImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[2];
	unsigned long colorindex;
	int addfunction;


	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephradiobutton->setBackground();
	if ((this->mephradiobutton->getImagePath()!=NULL) && (strcmp(mephradiobutton->getImagePath(),"")))
  	this->mephradiobutton->showImage();
	this->mephradiobutton->setTextX(25);
	this->mephradiobutton->setTextY(7);
	this->mephradiobutton->showText();

	this->mephradiobutton->setForeColor(0xFFFF,0xFFFF,0xFFFF);
	mephgraphicparam[0].setArc(1,1,13,13,225*64,405*64);
	mephgraphicparam[1].setArc(2,2,11,11,225*64,405*64);
	this->mephradiobutton->drawArcs(mephgraphicparam,2);
	this->mephradiobutton->setForeColor(0x3000,0x3000,0x3000);
//	mephgraphicparam[0].setArc(1,1,15,15,45*64,225*64);
	mephgraphicparam[0].setArc(2,2,11,11,35*64,205*64);
	this->mephradiobutton->drawArcs(mephgraphicparam,1);

	this->mephradiobutton->setForeColor(0xFFFF,0xFFFF,0xFFFF);
	mephgraphicparam[0].setArc(3,3,9,9,0,360*64);
	this->mephradiobutton->fillArcs(mephgraphicparam,1);
	
	if (this->mephradiobutton->getFocused())
	{
  	this->mephradiobutton->setForeColor(0,0,0);
    mephgraphicparam[0].setRectangle(15,1,this->mephradiobutton->getWidth()-18,this->mephradiobutton->getHeight()-2);	
  	this->mephradiobutton->drawRectangles(mephgraphicparam,1);
	}
	
  if (this->mephradiobutton->getState()>0)
	{
  	this->mephradiobutton->setForeColor(0,0,0);
		mephgraphicparam[0].setArc(4,4,7,7,0,360*64);
		this->mephradiobutton->fillArcs(mephgraphicparam,1);
	}

	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
}

void MephRadioButtonImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephradiobutton->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephradiobutton->getX(),mephradiobutton->getY(),mephradiobutton->getWidth(),
		  mephradiobutton->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephradiobutton->getX(),mephradiobutton->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephradiobutton->getWidth(),mephradiobutton->getHeight());
		}
	}
	
	if ((mephupdateparam & MephUPressed) || (mephupdateparam & MephUMoused))
		if (this->mephradiobutton->getDecorated())
  		this->drawButtonDecoration();
	
	XFlush(disp);
}

const Display * MephRadioButtonImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephRadioButtonImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephradiobutton->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephRadioButtonImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (RadioButton_mouseDown);
}

void (*MephRadioButtonImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (RadioButton_mouseUp);
}

void (*MephRadioButtonImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephRadioButton * mephradiobutton,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (RadioButton_mouseOver);
}

void (*MephRadioButtonImp_X11::catchEventPaint (void (*eventpaint)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (RadioButton_paint);
}

void (*MephRadioButtonImp_X11::catchEventConfigure (void (*eventconfigure)(class MephRadioButton * mephradiobutton,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (RadioButton_configure);
}

void (*MephRadioButtonImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (RadioButton_keyDown);
}

void (*MephRadioButtonImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephRadioButton * mephradiobutton,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (RadioButton_keyUp);
}

/***********************************************************************************************/

void MephRadioButtonImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephRadioButtonImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephRadioButtonImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephRadioButtonImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephRadioButtonImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephRadioButtonImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephRadioButtonImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void RadioButton_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void RadioButton_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void RadioButton_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void RadioButton_paint (void)
{
	if (!RadioButton_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void RadioButton_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void RadioButton_keyDown (void)
{
  printf ("Mousekeypress \n");
	fflush(stdout);
}

void RadioButton_keyUp (void)
{
  printf ("Mousekeyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/