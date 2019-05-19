#include "MephMenuImp_X11.h"
#include "MephMenu.h"
#include "MephGraphicParam.h"
#include <stdio.h>

XEvent Menu_event;

MephMenuImp_X11::~MephMenuImp_X11()
{
	delete this->mephmenu;
	delete this->mephvisobjimp;
	delete this->mephappimp;
}

MephMenuImp_X11::MephMenuImp_X11()
{
}

void MephMenuImp_X11::initValues(const class MephMenu *mephmenu, class MephAppImp const *mephappimp)
{
  this->mephmenu=(class MephMenu *) mephmenu;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephMenuImp_X11::initValues(const class MephVisObjImp * mephvisobjimp)
{
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
	
	this->parent=this->mephappimp->getRootWindow();
  
	if ( (this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(),
		this->mephmenu->getX(),this->mephmenu->getY(),
	    this->mephmenu->getWidth(),this->mephmenu->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }
	XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[0],ExposureMask|StructureNotifyMask);

/*NECESITA RECIBIR EL EVENTO DE ELIMINACIÓN DE VENTANA*/
  this->mephappimp->contain(this);
}

void MephMenuImp_X11::recieveEvent(XEvent event)
{
	if(event.type==Expose)
	{
		this->drawDecoration();
	}
	if(event.type==DestroyNotify)
	{
		XDestroyWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
	}
}

void MephMenuImp_X11::drawDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[4];

	mephgraphicparam[0].setLine(0,0,this->mephmenu->getWidth()-1,0);	
	mephgraphicparam[1].setLine(0,1,this->mephmenu->getWidth()-2,1);	
	mephgraphicparam[2].setLine(0,0,0,this->mephmenu->getHeight()-1);	
	mephgraphicparam[3].setLine(1,1,1,this->mephmenu->getHeight()-2);	

  this->mephmenu->setForeColor(0xFFFF,0xFFFF,0xFFFF);

	this->mephmenu->drawLines(mephgraphicparam,4);

  mephgraphicparam[0].setLine(this->mephmenu->getWidth()-1,this->mephmenu->getHeight()-1,this->mephmenu->getWidth()-1,0);	
  mephgraphicparam[1].setLine(this->mephmenu->getWidth()-1,this->mephmenu->getHeight()-1,0,this->mephmenu->getHeight()-1);
  mephgraphicparam[2].setLine(this->mephmenu->getWidth()-2,this->mephmenu->getHeight()-1,2,this->mephmenu->getHeight()-2);
  mephgraphicparam[3].setLine(this->mephmenu->getWidth()-2,this->mephmenu->getHeight()-2,this->mephmenu->getWidth()-2,1);	
  this->mephmenu->setForeColor(0xAFFF,0xAFFF,0xAFFF);
	this->mephmenu->drawLines(mephgraphicparam,4);



  XFlush((Display *)this->mephappimp->getDisplay());
	delete [] mephgraphicparam;
}

/*UTILIZA LOS PARµMETROS GEOMTRICOS DEL MEPHVISOBJ AL QUE PERTENECE STA FLOATINGWINDOW*/
/*void MephMenuImp_X11::show(void)
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
	
	printf ("X: %d Y: %d WIDTH: %d HEIGHT: %d\n",x_return,y_return,this->mephmenu->getWidth(),this->mephmenu->getHeight());
	fflush(stdout);

  if ((x_return+width_return+this->mephmenu->getWidth())<this->mephappimp->getSWidth())
    this->mephmenu->move(x_return,this->mephmenu->getY());
  else
    this->mephmenu->move(x_return-this->mephmenu->getWidth(),this->mephmenu->getY());

  if ((y_return+height_return+this->mephmenu->getHeight())<(this->mephappimp->getSHeight()))
    this->mephmenu->move(this->mephmenu->getX(),y_return+height_return);
  else
    this->mephmenu->move(this->mephmenu->getX(),y_return-this->mephmenu->getHeight());
  
  this->update(MephUVisible|MephUCoord);
	this->grabbing();
}

/*UTILIZA LAS COORDENADAS QUE SE LE PASAN COMO REFERENCIA PARA SABER DONDE PONERSE*/
/*void MephMenuImp_X11::show(int x,int y)
{
  if ((x+this->mephmenu->getWidth())<this->mephappimp->getSWidth())
    this->mephmenu->move(x,this->mephmenu->getY());
  else
    this->mephmenu->move(x-this->mephmenu->getWidth(),this->mephmenu->getY());

  if ((y+this->mephmenu->getHeight())<this->mephappimp->getSHeight())
    this->mephmenu->move(this->mephmenu->getX(),y);
  else
    this->mephmenu->move(this->mephmenu->getX(),y-this->mephmenu->getHeight());

  this->update(MephUVisible|MephUCoord);
	this->grabbing();
}*/

Window MephMenuImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephMenuImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephMenuImp_X11::getWindows()
{
	return (this->id);
}

int MephMenuImp_X11::getHeight()
{
	this->mephmenu->getHeight();
}

int MephMenuImp_X11::getWidth()
{
	this->mephmenu->getWidth();
}

void MephMenuImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephmenu->getVisible())
		{
		  XMapRaised(disp,id);	
	    XFlush(disp);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephmenu->getX(),mephmenu->getY(),mephmenu->getWidth(),
		  mephmenu->getHeight());
		this->drawDecoration();
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephmenu->getX(),mephmenu->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephmenu->getWidth(),mephmenu->getHeight());
    	 this->drawDecoration();
		}
	}
	
	XFlush(disp);
}

const Display * MephMenuImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

/*void MephMenuImp_X11::grabbing(void)
{
	XEvent event;
	char end=0;
	char keychar [10];
	char i;
	KeySym keysym;
	

  this->mephmenu->notifyPaint();
	if ((XGrabPointer((Display *)this->mephappimp->getDisplay(),this->id[0],False,ButtonPressMask,GrabModeSync,GrabModeAsync,False,None,CurrentTime)==GrabSuccess) && (XGrabKeyboard((Display *)this->mephappimp->getDisplay(),this->id[0],False,GrabModeSync,GrabModeAsync,CurrentTime)==GrabSuccess))
	{
		while (!end)
		{		
  	  XAllowEvents((Display *)this->mephappimp->getDisplay(),SyncPointer,CurrentTime);
  	  XAllowEvents((Display *)this->mephappimp->getDisplay(),AsyncKeyboard,CurrentTime);
	    XWindowEvent((Display *)this->mephappimp->getDisplay(),this->id[0],ButtonPressMask|KeyPressMask,&event);

    	if (event.type==ButtonPress)
	    {
  	  	if ((event.xbutton.x_root>=this->mephmenu->getX()) && 
	  	  		(event.xbutton.x_root<=this->mephmenu->getX()+
		  	  	this->mephmenu->getWidth()) &&
			  	  (event.xbutton.y_root>=this->mephmenu->getY()) &&
  				  (event.xbutton.y_root<=this->mephmenu->getY()+
    				this->mephmenu->getHeight()))
	      {
		    	this->mephmenu->notify(event.xbutton.y);
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
					this->mephmenu->notifyKeyUp();
				}
				if (keysym==XK_Down)
				{
					this->mephmenu->notifyKeyDown();
				}
				if (keysym==XK_Right)
				{
					this->mephmenu->notifyKeyRight();
				}
				if (keysym==XK_Escape)
				{
					end=1;
				}
				if ((keysym==XK_Return) || (keysym==XK_KP_Enter))
				{
					this->mephmenu->notifyKeyEnter();
					end=1;
				}
      }
  	}
	  XUngrabPointer((Display *)this->mephappimp->getDisplay(),CurrentTime);
	  XUngrabKeyboard((Display *)this->mephappimp->getDisplay(),CurrentTime);
		XUnmapWindow((Display *)this->mephappimp->getDisplay(),this->id[0]);
	}
}*/

void MephMenuImp_X11::destroyWindow(const class MephItemImp * mephitemimp)
{
	class MephItemImp *mii=(class MephItemImp *)mephitemimp;
	XDestroyWindow((Display *)this->mephappimp->getDisplay(),mii->getWindow());
}
