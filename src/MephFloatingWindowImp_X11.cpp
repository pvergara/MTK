#include "MephFloatingWindowImp_X11.h"
#include "MephFloatingWindow.h"
#include "MephGraphicParam.h"
#include <stdio.h>

XEvent FloatingWindow_event;

MephFloatingWindowImp_X11::~MephFloatingWindowImp_X11()
{
	delete this->mephfloatingwindow;
	delete this->mephvisobjimp;
	delete this->mephappimp;
}

MephFloatingWindowImp_X11::MephFloatingWindowImp_X11()
{
}

void MephFloatingWindowImp_X11::initValues(const class MephFloatingWindow *mephfloatingwindow, class MephAppImp const *mephappimp)
{
  this->mephfloatingwindow=(class MephFloatingWindow *) mephfloatingwindow;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephFloatingWindowImp_X11::initValues(const class MephVisObjImp * mephvisobjimp)
{
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
	Atom DestroyWindow;
	XSetWindowAttributes attrib;

	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
	
	this->parent=this->mephappimp->getRootWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
		this->mephfloatingwindow->getX(),this->mephfloatingwindow->getY(),
	    this->mephfloatingwindow->getWidth(),this->mephfloatingwindow->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }

	attrib.override_redirect=True;
	attrib.save_under=True;
	XChangeWindowAttributes((Display *) this->mephappimp->getDisplay(),this->id[0],CWOverrideRedirect|CWSaveUnder,&attrib);
/*NECESITA RECIBIR EL EVENTO DE ELIMINACIÓN DE VENTANA*/
  this->mephappimp->contain(this->mephvisobjimp,this);
}

void MephFloatingWindowImp_X11::recieveEvent(XEvent event)
{
/*	if(event.type==ClientMessage)
	{
    XDestroyWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
	  printf ("destroy\n");
		fflush(stdout);
	}*/
}

/*UTILIZA LOS PARµMETROS GEOMTRICOS DEL MEPHVISOBJ AL QUE PERTENECE STA FLOATINGWINDOW*/
void MephFloatingWindowImp_X11::show(void)
{ 
  int x_return, y_return,x_parent_return,y_parent_return;
  unsigned int width_return, height_return,width_parent_return,height_parent_return;
  unsigned int border_width_return,border_parent_width_return;
  unsigned int depth_return,depth_parent_return;
  Window root_window;
	Window parent_window;
	XWindowAttributes attrib;
	

  XGetGeometry((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(), &root_window, &x_return, 
	&y_return, &width_return,&height_return, &border_width_return, &depth_return);
  XFlush((Display *)this->mephappimp->getDisplay());
	
	XTranslateCoordinates((Display*)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(),root_window,0,0,&x_return,&y_return,&parent_window);
	
  if ((x_return+width_return+this->mephfloatingwindow->getWidth())<this->mephappimp->getSWidth())
    this->mephfloatingwindow->move(x_return,this->mephfloatingwindow->getY());
  else
    this->mephfloatingwindow->move(x_return-this->mephfloatingwindow->getWidth(),this->mephfloatingwindow->getY());

  if ((y_return+height_return+this->mephfloatingwindow->getHeight())<(this->mephappimp->getSHeight()))
    this->mephfloatingwindow->move(this->mephfloatingwindow->getX(),y_return+height_return);
  else
    this->mephfloatingwindow->move(this->mephfloatingwindow->getX(),y_return-this->mephfloatingwindow->getHeight());
  
  this->update(MephUVisible|MephUCoord);
	this->grabbing();
}

/*UTILIZA LAS COORDENADAS QUE SE LE PASAN COMO REFERENCIA PARA SABER DONDE PONERSE*/
void MephFloatingWindowImp_X11::show(int x,int y)
{
  if ((x+this->mephfloatingwindow->getWidth())<this->mephappimp->getSWidth())
    this->mephfloatingwindow->move(x,this->mephfloatingwindow->getY());
  else
    this->mephfloatingwindow->move(x-this->mephfloatingwindow->getWidth(),this->mephfloatingwindow->getY());

  if ((y+this->mephfloatingwindow->getHeight())<this->mephappimp->getSHeight())
    this->mephfloatingwindow->move(this->mephfloatingwindow->getX(),y);
  else
    this->mephfloatingwindow->move(this->mephfloatingwindow->getX(),y-this->mephfloatingwindow->getHeight());

  this->update(MephUVisible|MephUCoord);
	this->grabbing();
}

Window MephFloatingWindowImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephFloatingWindowImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephFloatingWindowImp_X11::getWindows()
{
	return (this->id);
}

int MephFloatingWindowImp_X11::getHeight()
{
	this->mephfloatingwindow->getHeight();
}

int MephFloatingWindowImp_X11::getWidth()
{
	this->mephfloatingwindow->getWidth();
}

void MephFloatingWindowImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephfloatingwindow->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephfloatingwindow->getX(),mephfloatingwindow->getY(),mephfloatingwindow->getWidth(),
		  mephfloatingwindow->getHeight());
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephfloatingwindow->getX(),mephfloatingwindow->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephfloatingwindow->getWidth(),mephfloatingwindow->getHeight());
		}
	}
	
	XFlush(disp);
}

const Display * MephFloatingWindowImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

void MephFloatingWindowImp_X11::grabbing(void)
{
	XEvent event;
	char end=0;
	char keychar [10];
	char i;
	KeySym keysym;
	

  this->mephfloatingwindow->notifyPaint();
	if ((XGrabPointer((Display *)this->mephappimp->getDisplay(),this->id[0],False,ButtonPressMask,GrabModeSync,GrabModeAsync,False,None,CurrentTime)==GrabSuccess) && (XGrabKeyboard((Display *)this->mephappimp->getDisplay(),this->id[0],False,GrabModeSync,GrabModeAsync,CurrentTime)==GrabSuccess))
	{
		while (!end)
		{		
  	  XAllowEvents((Display *)this->mephappimp->getDisplay(),SyncPointer,CurrentTime);
  	  XAllowEvents((Display *)this->mephappimp->getDisplay(),AsyncKeyboard,CurrentTime);
	    XWindowEvent((Display *)this->mephappimp->getDisplay(),this->id[0],ButtonPressMask|KeyPressMask,&event);

    	if (event.type==ButtonPress)
	    {
  	  	if ((event.xbutton.x_root>=this->mephfloatingwindow->getX()) && 
	  	  		(event.xbutton.x_root<=this->mephfloatingwindow->getX()+
		  	  	this->mephfloatingwindow->getWidth()) &&
			  	  (event.xbutton.y_root>=this->mephfloatingwindow->getY()) &&
  				  (event.xbutton.y_root<=this->mephfloatingwindow->getY()+
    				this->mephfloatingwindow->getHeight()))
	      {
		    	this->mephfloatingwindow->notify(event.xbutton.y);
  		  }
				end=1;
      }
    	if (event.type==KeyPress)
	    {
				i=XLookupString(&event.xkey,keychar,10,&keysym,NULL);
				if (i>10)
					i=10-1;
				keychar[i]='\x0';
				if (keysym==XK_Up)
				{
					this->mephfloatingwindow->notifyKeyUp();
				}
				if (keysym==XK_Down)
				{
					this->mephfloatingwindow->notifyKeyDown();
				}
				if (keysym==XK_Right)
				{
//					this->mephfloatingwindow->notifyKeyRight();
					end=1;
				}
				if (keysym==XK_Left)
				{
//					this->mephfloatingwindow->notifyKeyLeft();
					end=1;
				}
				if (keysym==XK_Escape)
				{
					end=1;
				}
				if ((keysym==XK_Return) || (keysym==XK_KP_Enter))
				{
					this->mephfloatingwindow->notifyKeyEnter();
					end=1;
				}
      }
  	}
	  XUngrabPointer((Display *)this->mephappimp->getDisplay(),CurrentTime);
	  XUngrabKeyboard((Display *)this->mephappimp->getDisplay(),CurrentTime);
		XUnmapWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
		if (keysym==XK_Right)
			this->mephfloatingwindow->notifyKeyRight();
		if (keysym==XK_Left)
			this->mephfloatingwindow->notifyKeyLeft();
	}
}

void MephFloatingWindowImp_X11::destroyWindow(const class MephItemImp * mephitemimp)
{
	class MephItemImp *mii=(class MephItemImp *)mephitemimp;
	XDestroyWindow((Display *)this->mephappimp->getDisplay(),mii->getWindow());
}
