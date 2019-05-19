#include "MephComboBoxImp_X11.h"
#include "MephComboBox.h"
#include "MephGraphicParam.h"
#include <stdio.h>

#define ComboMinWidth  15
#define ComboMinHeight 15

void ComboBox_mouseDown (void);
void ComboBox_mouseUp (void);
void ComboBox_mouseOver (void);
void ComboBox_paint (void);
void ComboBox_configure (void);
void ComboBox_keyDown (void);
void ComboBox_keyUp (void);

XEvent ComboBox_event;

MephComboBoxImp_X11::~MephComboBoxImp_X11()
{
	delete this->mephcombobox;
	delete this->mephwindowimp;
	delete this->mephappimp;
}

MephComboBoxImp_X11::MephComboBoxImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL)
{
}

void MephComboBoxImp_X11::initValues(const class MephComboBox *mephcombobox)
{
  this->mephcombobox=(class MephComboBox *) mephcombobox;
}
void MephComboBoxImp_X11::initValues(const class MephComboBox *mephcombobox, class MephAppImp const *mephappimp)
{
  this->mephcombobox=(class MephComboBox *) mephcombobox;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephComboBoxImp_X11::initValues(const class MephWindowImp * mephwindowimp)
{
  char e;
	this->mephwindowimp=(class MephWindowImp *) mephwindowimp;
  this->parent=this->mephwindowimp->getWindow();
  
  /*Ventana de muestra del item*/
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephcombobox->getX(),this->mephcombobox->getY(),
	    this->mephcombobox->getWidth(),this->mephcombobox->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }

  /*Ventana para mostrar el FloatingWindow*/
	if ( (this->id[1]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephcombobox->getX(0,&e)+(this->mephcombobox->getWidth(0,&e)),this->mephcombobox->getY(1,&e),
	    ComboMinHeight,this->mephcombobox->getHeight(1,&e),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	/**********************************AQUUI!!!!! (mas eventos)***************************/
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask|StructureNotifyMask);
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[1],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask|StructureNotifyMask);
  /****************************************************************************************/

  this->mephappimp->contain(this,2);
}

void MephComboBoxImp_X11::recieveNoMotion()
{
	this->mephcombobox->setMoused(NOTMOUSED);
//	this->mephcombobox->setMoused(NOTPRESSED);
	printf ("LEEEREEELEE!!!!!!\n");
	fflush(stdout);
}

void MephComboBoxImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydown==NULL)
			  ComboBox_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephcombobox,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			i=XLookupString(&event.xkey,keychar,1,&keysym,NULL);
			if (keysym==XK_space)
  			this->mephcombobox->notify(NOTPRESSED);
			if (this->neweventkeyup==NULL)
			  ComboBox_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephcombobox,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			this->mephcombobox->notify(PRESSED);
			this->mephcombobox->setMoused(MOUSED);
			if (this->neweventmousedown==NULL)
			  ComboBox_mouseDown();
		  else
				this->neweventmousedown(this->mephcombobox,event.xbutton.x,event.xbutton.y,event.xbutton.state);

		}break;

		case ButtonRelease:
		{
			if (event.xany.window==this->id[1])
				this->mephcombobox->showFloatingWindow();
			this->mephcombobox->notify(NOTPRESSED);
			/*ESTE IF MARCA UNA DIFERENCIA MUY IMPORTANTE ENTRE LO QUE ES UN CLICK DE UN BOT”N
			Y UN RELEASE DEL MISMO BOT”N. UN CLICK SIEMPRE SE PRODUCIRµ DENTRO DE LOS LÕMITES
			DEL BOT”N MIENTRAS QUE UN RELEASE NO TIENE PORQUE*/
			if ((event.xbutton.x>=this->mephcombobox->getWidth()) ||(event.xbutton.y>=this->mephcombobox->getHeight()))
  			this->mephcombobox->setMoused(NOTMOUSED);
			else
	  		this->mephcombobox->setMoused(MOUSED);

			if (this->neweventmouseup==NULL)
			  ComboBox_mouseUp();
		  else
				this->neweventmouseup(this->mephcombobox,event.xbutton.x,event.xbutton.y,event.xbutton.state);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
			if (this->mephcombobox->getMoused()==NOTMOUSED)
			{
   		  this->mephcombobox->setMoused(MOUSED);
			}
      if (this->mephcombobox->getPressed()==NOTPRESSED)
			{
  			if ((event.xmotion.state==Button1Mask) || (event.xmotion.state==Button2Mask) || (event.xmotion.state==Button3Mask) || (event.xmotion.state==Button4Mask) || (event.xmotion.state==Button5Mask) )
 		      this->mephcombobox->setMoused(PRESSED);
			}
			if (this->neweventmouseover==NULL)
			  ComboBox_mouseOver();
		  else
				this->neweventmouseover(this->mephcombobox,event.xbutton.x,event.xbutton.y,event.xbutton.state);
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
				if (this->mephcombobox->getDecorated())
				  this->drawButtonDecoration();
  			if (this->neweventpaint==NULL)
	  		  ComboBox_paint();
		    else
			  	this->neweventpaint(this->mephcombobox,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephcombobox->setFocused(FOCUSED);
				if (this->mephcombobox->getDecorated())
			  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephcombobox->setFocused(NOTFOCUSED);
				if (this->mephcombobox->getDecorated())
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
			  ComboBox_configure();
		  else
				this->neweventconfigure(this->mephcombobox,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
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

Window MephComboBoxImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephComboBoxImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephComboBoxImp_X11::getWindows()
{
	return (this->id);
}

int MephComboBoxImp_X11::getHeight()
{
	this->mephcombobox->getHeight();
}

int MephComboBoxImp_X11::getWidth()
{
	this->mephcombobox->getWidth();
}

void MephComboBoxImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[4];
	int addfunction;

	
	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephcombobox->setBackground();
	if ((this->mephcombobox->getImagePath()!=NULL) && (strcmp(mephcombobox->getImagePath(),"")))
  	this->mephcombobox->showImage();

	this->mephcombobox->setTextX((this->mephcombobox->getWidth()/2)-(this->mephcombobox->getTextWidth()/2));
	this->mephcombobox->setTextY((this->mephcombobox->getHeight()/2));
	this->mephcombobox->showText();

  this->mephcombobox->setForeColor(0,0,0);

  mephgraphicparam[0].setRectangle(0,0,14,14);
  this->mephcombobox->drawRectangles(mephgraphicparam,1,1);

  mephgraphicparam[0].setPoint(7,12);
  mephgraphicparam[1].setPoint(11,3);
  mephgraphicparam[2].setPoint(2,3);
  mephgraphicparam[3].setPoint(7,12);
  this->mephcombobox->fillPolygons(mephgraphicparam,4,0,0,1);

	
	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
	
}

void MephComboBoxImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];
	char e;

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephcombobox->getVisible())
		{
//		  XMapRaised(disp,id);	
		  XMapRaised(disp,this->id[0]);	
		  XMapRaised(disp,this->id[1]);	
		}
		else
		{
		  XUnmapWindow(disp,id);
		  XUnmapWindow(disp,this->id[1]);
		}
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephcombobox->getX(),mephcombobox->getY(),mephcombobox->getWidth(),
		  mephcombobox->getHeight());
    XMoveResizeWindow (disp,this->id[1],mephcombobox->getX(1,&e),mephcombobox->getY(1,&e),mephcombobox->getWidth(1,&e),
		  mephcombobox->getHeight(1,&e));
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		{
		   XMoveWindow(disp,id,mephcombobox->getX(),mephcombobox->getY());
		   XMoveWindow(disp,this->id[1],mephcombobox->getX(1,&e),mephcombobox->getY(1,&e));
		}
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephcombobox->getWidth(),mephcombobox->getHeight());
		   XResizeWindow(disp,this->id[1],mephcombobox->getWidth(1,&e),mephcombobox->getHeight(1,&e));
		}
	}
  if (mephupdateparam & MephUDecoration)
	{
		if (this->mephcombobox->getDecorated())
		  this->drawButtonDecoration();
	}
	
	XFlush(disp);
}

const Display * MephComboBoxImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephComboBoxImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephcombobox->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephComboBoxImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (ComboBox_mouseDown);
}

void (*MephComboBoxImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (ComboBox_mouseUp);
}

void (*MephComboBoxImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephComboBox * mephcombobox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (ComboBox_mouseOver);
}

void (*MephComboBoxImp_X11::catchEventPaint (void (*eventpaint)(class MephComboBox * mephcombobox,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (ComboBox_paint);
}

void (*MephComboBoxImp_X11::catchEventConfigure (void (*eventconfigure)(class MephComboBox * mephcombobox,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (ComboBox_configure);
}

void (*MephComboBoxImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (ComboBox_keyDown);
}

void (*MephComboBoxImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephComboBox * mephcombobox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (ComboBox_keyUp);
}

/***********************************************************************************************/

void MephComboBoxImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephComboBoxImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephComboBoxImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephComboBoxImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephComboBoxImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephComboBoxImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephComboBoxImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void ComboBox_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void ComboBox_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void ComboBox_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void ComboBox_paint (void)
{
	if (!ComboBox_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void ComboBox_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void ComboBox_keyDown (void)
{
  printf ("Boton keypress \n");
	fflush(stdout);
}

void ComboBox_keyUp (void)
{
  printf ("Mousekeyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/
