#include "MephTextBoxImp_X11.h"
#include "MephTextBox.h"
#include "MephGraphicParam.h"
#include <stdio.h>

void TextBox_mouseDown (void);
void TextBox_mouseUp (void);
void TextBox_mouseOver (void);
void TextBox_paint (void);
void TextBox_configure (void);
void TextBox_keyDown (void);
void TextBox_keyUp (void);

XEvent TextBox_event;

MephTextBoxImp_X11::~MephTextBoxImp_X11()
{
	delete this->mephtextbox;
	delete this->mephwindowimp;
	delete this->mephappimp;
}

MephTextBoxImp_X11::MephTextBoxImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL)
{
}

void MephTextBoxImp_X11::initValues(const class MephTextBox *mephtextbox)
{
  this->mephtextbox=(class MephTextBox *) mephtextbox;
}
void MephTextBoxImp_X11::initValues(const class MephTextBox *mephtextbox, class MephAppImp const *mephappimp)
{
  this->mephtextbox=(class MephTextBox *) mephtextbox;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephTextBoxImp_X11::initValues(const class MephWindowImp * mephwindowimp)
{
	this->mephwindowimp=(class MephWindowImp *) mephwindowimp;
  this->parent=this->mephwindowimp->getWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephtextbox->getX(),this->mephtextbox->getY(),
	    this->mephtextbox->getWidth(),this->mephtextbox->getHeight(),0,
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

void MephTextBoxImp_X11::recieveNoMotion()
{
	this->mephtextbox->setMoused(NOTMOUSED);
//	this->mephtextbox->setMoused(NOTPRESSED);
	printf ("LEEEREEELEE!!!!!!\n");
	fflush(stdout);
}

void MephTextBoxImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i;
	KeySym keysym;

	switch(event.type)
	{
		case KeyPress:
		{
	  	i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
			if (i>5)
				i=5-1;
  		keychar[i]='\x0';
			if (this->neweventkeydown==NULL)
			{
			  TextBox_keyDown();
				this->writeText(keychar,keysym,event.xkey.state);
				this->drawButtonDecoration();
			}
		  else
			{
				this->neweventkeydown(this->mephtextbox,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			i=XLookupString(&event.xkey,keychar,1,&keysym,NULL);
			if (keysym==XK_space)
  			this->mephtextbox->notify(NOTPRESSED);
			if (this->neweventkeyup==NULL)
			  TextBox_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephtextbox,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			this->mephtextbox->notify(PRESSED);
			this->mephtextbox->setMoused(MOUSED);
			if (this->neweventmousedown==NULL)
			  TextBox_mouseDown();
		  else
				this->neweventmousedown(this->mephtextbox,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
			this->mephtextbox->notify(NOTPRESSED);
			/*ESTE IF MARCA UNA DIFERENCIA MUY IMPORTANTE ENTRE LO QUE ES UN CLICK DE UN BOT”N
			Y UN RELEASE DEL MISMO BOT”N. UN CLICK SIEMPRE SE PRODUCIRµ DENTRO DE LOS LÕMITES
			DEL BOT”N MIENTRAS QUE UN RELEASE NO TIENE PORQUE*/
			if ((event.xbutton.x>=this->mephtextbox->getWidth()) ||(event.xbutton.y>=this->mephtextbox->getHeight()))
  			this->mephtextbox->setMoused(NOTMOUSED);
			else
	  		this->mephtextbox->setMoused(MOUSED);

			if (this->neweventmouseup==NULL)
			  TextBox_mouseUp();
		  else
				this->neweventmouseup(this->mephtextbox,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
			if (this->mephtextbox->getMoused()==NOTMOUSED)
			{
   		  this->mephtextbox->setMoused(MOUSED);
			}
      if (this->mephtextbox->getPressed()==NOTPRESSED)
			{
  			if ((event.xmotion.state==Button1Mask) || (event.xmotion.state==Button2Mask) || (event.xmotion.state==Button3Mask) || (event.xmotion.state==Button4Mask) || (event.xmotion.state==Button5Mask) )
 		      this->mephtextbox->setMoused(PRESSED);
			}
			if (this->neweventmouseover==NULL)
			  TextBox_mouseOver();
		  else
				this->neweventmouseover(this->mephtextbox,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
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
				if (this->mephtextbox->getDecorated())
  			  this->drawButtonDecoration();
  			if (this->neweventpaint==NULL)
	  		  TextBox_paint();
		    else
			  	this->neweventpaint(this->mephtextbox,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephtextbox->setFocused(FOCUSED);
			if (this->mephtextbox->getDecorated())
  		  this->drawButtonDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephtextbox->setFocused(NOTFOCUSED);
 			if (this->mephtextbox->getDecorated())
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
			  TextBox_configure();
		  else
				this->neweventconfigure(this->mephtextbox,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
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

Window MephTextBoxImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephTextBoxImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephTextBoxImp_X11::getWindows()
{
	return (this->id);
}

int MephTextBoxImp_X11::getHeight()
{
	this->mephtextbox->getHeight();
}

int MephTextBoxImp_X11::getWidth()
{
	this->mephtextbox->getWidth();
}

void MephTextBoxImp_X11::writeText(char *keychar,KeySym keysym,unsigned int state)
{
	int i;
	if (keysym!=XK_Tab)
	{
	  char *aux=new char [256];

    for (i=0;i<255;i++)
      aux[i]='a';
    aux[i]='\x0';
    sprintf(aux,"%s",this->mephtextbox->getText());
		aux[strlen(this->mephtextbox->getText())]='\x0';
  	if (keysym==XK_BackSpace)
	  {
  		aux[strlen(aux)-1]='\x0';
	  }
		else
		{
	    strcat(aux,keychar);
  		aux[strlen(this->mephtextbox->getText())+strlen(keychar)+1]='\x0';
		}
	  this->mephtextbox->setText(aux);
    if (this->mephtextbox->getWidth()<this->mephtextbox->getTextWidth())
	  	this->mephtextbox->setTextX (this->mephtextbox->getWidth()-this->mephtextbox->getTextWidth());
    delete aux;
	}
}

void MephTextBoxImp_X11::drawButtonDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[4];
	int addfunction;


	XClearWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
  this->mephtextbox->setBackground();
	if ((this->mephtextbox->getImagePath()!=NULL) && (strcmp(mephtextbox->getImagePath(),"")))
  	this->mephtextbox->showImage();
	this->mephtextbox->showText();

	mephgraphicparam[0].setLine(0,0,this->mephtextbox->getWidth()-1,0);	
	mephgraphicparam[1].setLine(0,1,this->mephtextbox->getWidth()-3,1);	
	mephgraphicparam[2].setLine(0,0,0,this->mephtextbox->getHeight()-1);	
	mephgraphicparam[3].setLine(1,0,1,this->mephtextbox->getHeight()-3);

  this->mephtextbox->setForeColor(0xFF,0xFF,0xFF);

	this->mephtextbox->drawLines(mephgraphicparam,4);

  mephgraphicparam[0].setLine(this->mephtextbox->getWidth()-1,this->mephtextbox->getHeight()-1,this->mephtextbox->getWidth()-1,0);	
  mephgraphicparam[1].setLine(this->mephtextbox->getWidth()-2,this->mephtextbox->getHeight()-1,this->mephtextbox->getWidth()-2,1);	
  mephgraphicparam[2].setLine(this->mephtextbox->getWidth()-1,this->mephtextbox->getHeight()-1,0,this->mephtextbox->getHeight()-1);
  mephgraphicparam[3].setLine(this->mephtextbox->getWidth()-1,this->mephtextbox->getHeight()-2,1,this->mephtextbox->getHeight()-2);

  this->mephtextbox->setForeColor(0xAFFF,0xAFFF,0xAFFF);

	this->mephtextbox->drawLines(mephgraphicparam,4);
	
	XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
	
}

void MephTextBoxImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephtextbox->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephtextbox->getX(),mephtextbox->getY(),mephtextbox->getWidth(),
		  mephtextbox->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephtextbox->getX(),mephtextbox->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephtextbox->getWidth(),mephtextbox->getHeight());
		}
	}
	
	if ((mephupdateparam & MephUPressed) || (mephupdateparam & MephUMoused))
		if (this->mephtextbox->getDecorated())
  		this->drawButtonDecoration();
	
	XFlush(disp);
}

const Display * MephTextBoxImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephTextBoxImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephtextbox->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephTextBoxImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (TextBox_mouseDown);
}

void (*MephTextBoxImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (TextBox_mouseUp);
}

void (*MephTextBoxImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephTextBox * mephtextbox,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (TextBox_mouseOver);
}

void (*MephTextBoxImp_X11::catchEventPaint (void (*eventpaint)(class MephTextBox * mephtextbox,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (TextBox_paint);
}

void (*MephTextBoxImp_X11::catchEventConfigure (void (*eventconfigure)(class MephTextBox * mephtextbox,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (TextBox_configure);
}

void (*MephTextBoxImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (TextBox_keyDown);
}

void (*MephTextBoxImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephTextBox * mephtextbox,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (TextBox_keyUp);
}

/***********************************************************************************************/

void MephTextBoxImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephTextBoxImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephTextBoxImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephTextBoxImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephTextBoxImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephTextBoxImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephTextBoxImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void TextBox_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);	
}

void TextBox_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);	
}

void TextBox_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void TextBox_paint (void)
{
	if (!TextBox_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void TextBox_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void TextBox_keyDown (void)
{
  printf ("Tecla Abajo \n");
	fflush(stdout);
}

void TextBox_keyUp (void)
{
  printf ("Tecla Arriba \n");
	fflush(stdout);
}
/***********************************************************************************************/
