#include "MephWindowImp_X11.h"
#include "MephWindow.h"
#include <stdio.h>
#include <X11/Xatom.h>

void Window_mouseDown (void);
void Window_mouseUp (void);
void Window_mouseOver (void);
void Window_paint (void);
void Window_configure (void);
void Window_keyDown (void);
void Window_keyUp (void);

XEvent Window_event;

MephWindowImp_X11::MephWindowImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL),neweventconfiguretomephmenu(NULL),mephmenu(NULL)
{
}

MephWindowImp_X11::MephWindowImp_X11(const MephWindowImp_X11 &right)
{
}


MephWindowImp_X11::~MephWindowImp_X11()
{
  delete this->mephwindow;
	delete this->mephappimp;
}


const Display * MephWindowImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

const MephWindowImp_X11 & MephWindowImp_X11::operator=(const MephWindowImp_X11 &right)
{
}


int MephWindowImp_X11::operator==(const MephWindowImp_X11 &right) const
{
}

int MephWindowImp_X11::operator!=(const MephWindowImp_X11 &right) const
{
}

const class MephWindowImp *MephWindowImp_X11::getMephWindowImp()
{
  return ((const class MephWindowImp *) this);
}

void MephWindowImp_X11::initValues(const class MephWindow *mephwindow)
{
	Atom DestroyWindow;
	Display *disp=(Display *)this->mephappimp->getDisplay();
		
  this->mephwindow=(class MephWindow *) mephwindow;

  parent=this->mephappimp->getRootWindow();
	
  if ( (this->id[0]=XCreateSimpleWindow(disp,parent,
		this->mephwindow->getX(),this->mephwindow->getY(),
	    this->mephwindow->getWidth(),this->mephwindow->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	DestroyWindow=XInternAtom(disp,"WM_DELETE_WINDOW",False);
  XSetWMProtocols((Display *)this->mephappimp->getDisplay(),this->id[0],&DestroyWindow,1);
	
//	**********************************AQUUI!!!!! (mas eventos)***************************
	XSelectInput(disp,this->id[0],StructureNotifyMask|ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask);
}

void MephWindowImp_X11::initValues(const class MephWindow *mephwindow,class MephAppImp const *mephappimp)
{
	Atom DestroyWindow;
	Display *disp;
		
  this->mephwindow=(class MephWindow *) mephwindow;
	this->mephappimp=(class MephAppImp *)mephappimp;
	disp=(Display *)this->mephappimp->getDisplay();

  parent=this->mephappimp->getRootWindow();
	
  if ( (this->id[0]=XCreateSimpleWindow(disp,parent,
		this->mephwindow->getX(),this->mephwindow->getY(),
	    this->mephwindow->getWidth(),this->mephwindow->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	
	DestroyWindow=XInternAtom(disp,"WM_DELETE_WINDOW",False);
  XSetWMProtocols(disp,this->id[0],&DestroyWindow,1);
	
//	**********************************AQUUI!!!!! (mas eventos)***************************
	XSelectInput(disp,this->id[0],StructureNotifyMask|ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask);
  this->mephappimp->contain(this);
}

void MephWindowImp_X11::update (MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  /*YA LO SE FRAN...PARA ESTO TAMBIêN SE CREA UNA CLASE...PERO ES QUE EN ESTE CASO...CREO QUE 
	LA SANTA PROGRAMACI”N ESTRUCTURADA NO NOS DEJARµ... SOLO HACE FALTA VER COMO SE RELLENAN
	ESTOS DATOS...Y LO SIENTO PERO NO SE PUEDE :-) */
  struct MotifWmHints
  {
    unsigned long       flags;
    unsigned long       functions;
    unsigned long       decorations;
    long                inputMode;
    unsigned long       status;
  }*motifwmhints; 


	Atom hints_atom = None;
	Atom type;
	int format;
	unsigned long nitems,bytes_after;

	/*CCCCCCCCCCCCCUUUUUUUUUUUUUUUUIIIIIIIIIIIIDDDDDDDDAAAAAAAAAADDDDDDDDDDDDOOOOOOOOOO
	CUANDO SE CREE EL ENABLED RECORDAR QUE ESO TAMBIêN AFECTARµ AL TABINDEX!!!!!!!!!!!*/
	
	
  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephwindow->getVisible())
		{
		  XMapRaised(disp,this->id[0]);
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,this->id[0]);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize))==(MephUCoord & MephUSize))
	{
    XMoveResizeWindow (disp,this->id[0],this->mephwindow->getX(),this->mephwindow->getY(),this->mephwindow->getWidth(),
		  this->mephwindow->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
	   XMoveWindow(disp,this->id[0],this->mephwindow->getX(),this->mephwindow->getY());
	  if (mephupdateparam & MephUSize)
	   XResizeWindow(disp,this->id[0],this->mephwindow->getWidth(),this->mephwindow->getHeight());
	}

	if ((mephupdateparam & MephUDecoration) || (mephupdateparam & MephUDecorationFunction))
	{

		hints_atom=XInternAtom(disp,"_MOTIF_WM_HINTS",False);
		
		XGetWindowProperty(disp,this->id[0],hints_atom,0,sizeof(MotifWmHints)/sizeof(unsigned long),
			False,AnyPropertyType,&type,&format,&nitems,&bytes_after,(unsigned char **) &motifwmhints);
		
    if (type==None)
			motifwmhints=(MotifWmHints *) malloc(sizeof(MotifWmHints));
		
    if (mephupdateparam & MephUDecoration)
		{
			motifwmhints->flags |= MWM_HINTS_DECORATIONS;
			motifwmhints->decorations = this->mephwindow->getDecoration();
		}

		if (mephupdateparam & MephUDecorationFunction)
		{
  		motifwmhints->flags |= MWM_HINTS_FUNCTIONS;
	    motifwmhints->functions = this->mephwindow->getDecorationFunction();
	  }
		
		XChangeProperty(disp,this->id[0],hints_atom,hints_atom,32,PropModeReplace,
			(unsigned char *) motifwmhints,sizeof(MotifWmHints)/sizeof(unsigned long));
		
		XFree(motifwmhints);
		
	}

	if (mephupdateparam & MephUTitle)
	{
	  XStoreName(disp,id,(char const *) this->mephwindow->getTitle());
	}
	
	XFlush(disp);
}

Window MephWindowImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephWindowImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephWindowImp_X11::getWindows()
{
	return (this->id);
}

int MephWindowImp_X11::getWidth()
{
  return (this->mephwindow->getWidth());
}

int MephWindowImp_X11::getHeight()
{
	return (this->mephwindow->getHeight());
}


void MephWindowImp_X11::recieveNoMotion()
{
	/*AQUÕ REALMENTE HAY POCO QUE HACER A NO SER QUE EL USUARIO QUIERA HACER ALGO*/
}

void MephWindowImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;
	
	/*VARIABLE GLOBAL QUE ME GUSTA MAS BIEN BASTANTE POCO PERO... ME TEMO QUE AQUÕ NO ME QUEDA OTRA QUE JODERME*/
	Window_event=event;
	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydown==NULL)
			  Window_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephwindow,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			if (this->neweventkeyup==NULL)
			  Window_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephwindow,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			if (this->neweventmousedown==NULL)
			  Window_mouseDown();
		  else
				this->neweventmousedown(this->mephwindow,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
		}break;

		case ButtonRelease:
		{
			if (this->neweventmouseup==NULL)
			  Window_mouseUp();
		  else
				this->neweventmouseup(this->mephwindow,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
		}break;

		case MotionNotify:
		{
			if (this->neweventmouseover==NULL)
			  Window_mouseOver();
		  else
				this->neweventmouseover(this->mephwindow,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
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
			if (this->neweventpaint==NULL)
			  Window_paint();
		  else
				this->neweventpaint(this->mephwindow,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
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
			if ((this->neweventconfigure==NULL) && (this->neweventconfiguretomephmenu==NULL))
			  Window_configure();
		  else
			{
				if (this->neweventconfiguretomephmenu!=NULL)
  				(this->mephmenu->*neweventconfiguretomephmenu)(this->mephwindow,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
				if (this->neweventconfigure!=NULL)
  				this->neweventconfigure(this->mephwindow,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			}
  		this->mephwindow->notify(event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
		}break;

		case CreateNotify:
		{
		  printf ("create\n");
			fflush(stdout);
		}break;

		case DestroyNotify:
		{
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
			XDestroyWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
		  printf ("ClientMessage\n");
			fflush(stdout);
		}
	};
}

char MephWindowImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephwindow->getTabIndexEnabled()));
}

void MephWindowImp_X11::end(void)
{
	XDestroyWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephWindowImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (Window_mouseDown);
}

void (*MephWindowImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (Window_mouseUp);
}

void (*MephWindowImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephWindow * mephwindow,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (Window_mouseOver);
}

void (*MephWindowImp_X11::catchEventPaint (void (*eventpaint)(class MephWindow * mephwindow,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (Window_paint);
}

void (*MephWindowImp_X11::catchEventConfigure (void (*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (Window_configure);
}

void (*MephWindowImp_X11::catchEventConfigure (void (MephMenu::*eventconfigure)(class MephWindow * mephwindow,int x,int y,int width,int height),class MephMenu *mephmenu)) (void)
{
	this->mephmenu=mephmenu;
	this->neweventconfiguretomephmenu=eventconfigure;
	return (NULL);
}

void (*MephWindowImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (Window_keyDown);
}

void (*MephWindowImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephWindow * mephwindow,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (Window_keyUp);
}

/***********************************************************************************************/

void MephWindowImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephWindowImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephWindowImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephWindowImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephWindowImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephWindowImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephWindowImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void Window_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void Window_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void Window_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void Window_paint (void)
{
	if (!Window_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void Window_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void Window_keyDown (void)
{
  printf ("keypress \n");
	fflush(stdout);
}

void Window_keyUp (void)
{
  printf ("keyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/