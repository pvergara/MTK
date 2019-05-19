#include "MephScrollBarImp_X11.h"
#include "MephScrollBar.h"
#include "MephGraphicParam.h"
#include <stdio.h>

void ScrollBar_mouseDown (void);
void ScrollBar_mouseUp (void);
void ScrollBar_mouseOver (void);
void ScrollBar_paint (void);
void ScrollBar_change(void);
void ScrollBar_configure (void);
void ScrollBar_keyDown (void);
void ScrollBar_keyUp (void);

XEvent ScrollBar_event;

MephScrollBarImp_X11::~MephScrollBarImp_X11()
{
	delete this->mephscrollbar;
	delete this->mephvisobjimp;
	delete this->mephappimp;
}

MephScrollBarImp_X11::MephScrollBarImp_X11():neweventmousedown(NULL),neweventmouseup(NULL),neweventmouseover(NULL),neweventpaint(NULL),neweventconfigure(NULL),neweventkeydown(NULL),neweventkeyup(NULL),/*neweventchange(NULL),*/neweventchangetomephlistbox(NULL)
{
}

void MephScrollBarImp_X11::initValues(const class MephScrollBar *mephscrollbar, class MephAppImp const *mephappimp)
{
  this->mephscrollbar=(class MephScrollBar *) mephscrollbar;
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephScrollBarImp_X11::initValues(const class MephVisObjImp * mephvisobjimp)
{
	char i,e;
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
  this->parent=this->mephvisobjimp->getWindow();

	if ((this->id[0]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),parent,
    this->mephscrollbar->getX(),this->mephscrollbar->getY(),
	    this->mephscrollbar->getWidth(),this->mephscrollbar->getHeight(),0,
	    0,0))==0)
  {
    cerr << "Could not create window";
    exit(-1);
  }

	for (i=1;i<4;i++)
	  if ( (this->id[i]=XCreateSimpleWindow((Display *) this->mephappimp->getDisplay(),this->id[0],
  		this->mephscrollbar->getX(i,&e),this->mephscrollbar->getY(i,&e),
	      this->mephscrollbar->getWidth(i,&e),this->mephscrollbar->getHeight(i,&e),0,
	      0,0))==0)
    {
      cerr << "Could not create window";
      exit(-1);
    }
	for (i=0;i<4;i++)
	{
		printf ("width[i]:%d\n",this->mephscrollbar->getWidth(i,&e));
		fflush(stdout);
	}
		
	for (i=0;i<4;i++)
	  XSelectInput((Display *)this->mephappimp->getDisplay(),this->id[i],ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|FocusChangeMask|ColormapChangeMask|StructureNotifyMask);
	
	this->update(MephUSize);

  this->mephappimp->contain(this,4);
}

void MephScrollBarImp_X11::recieveNoMotion()
{
//	this->mephscrollbar->setMoused(NOTMOUSED);
}

void MephScrollBarImp_X11::recieveEvent(XEvent event)
{
	char keychar [5];
	char i,e;
	KeySym keysym;
	int naux;
	unsigned int aux;
	static int scroll;
	float inc,faux;

	switch(event.type)
	{
		case KeyPress:
		{
			if (this->neweventkeydown==NULL)
			  ScrollBar_keyDown();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeydown(this->mephscrollbar,keychar,keysym,event.xkey.state);
			}
		}break;

		case KeyRelease:
		{
			if (this->neweventkeyup==NULL)
			  ScrollBar_keyUp();
		  else
			{
				i=XLookupString(&event.xkey,keychar,5,&keysym,NULL);
				if (i>5)
					i=5-1;
				keychar[i]='\x0';
				this->neweventkeyup(this->mephscrollbar,keychar,keysym,event.xkey.state);
			}
		}break;

		case ButtonPress:
		{
			if (event.xbutton.button==Button1)
			{
				this->scroll(event);
				
				if (event.xany.window==this->id[3])
					if (this->mephscrollbar->getOrientation()==HORIZONTAL)
					  scroll=event.xbutton.x;
					else
					  scroll=event.xbutton.y;
      }
			if (this->neweventmousedown==NULL)
			  ScrollBar_mouseDown();
		  else
				this->neweventmousedown(this->mephscrollbar,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

		}break;

		case ButtonRelease:
		{
			if (this->neweventmouseup==NULL)
			  ScrollBar_mouseUp();
		  else
				this->neweventmouseup(this->mephscrollbar,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);

			printf ("buttonrelease\n");
			fflush(stdout);
		}break;

		case MotionNotify:
		{
  		if (((event.xany.window==this->id[3]) && (event.xmotion.state & Button1Mask)) && (this->mephscrollbar->getMin()<this->mephscrollbar->getMax()))
			{
	      aux=0;
      	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
          for (i=1;i<4;i++)
	          aux+=this->mephscrollbar->getWidth(i,&e);
				else
          for (i=1;i<4;i++)
	          aux+=this->mephscrollbar->getHeight(i,&e);

      	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
          aux=this->mephscrollbar->getWidth(0,&e)-aux;
				else
          aux=this->mephscrollbar->getHeight(0,&e)-aux;
				
	      inc=(float) (this->mephscrollbar->getMax()-this->mephscrollbar->getMin())/aux;
	      if ((inc>0) && (inc<=1))
	 	      inc=1;

       	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    	    naux=event.xmotion.x-scroll;
			  else
    	    naux=event.xmotion.y-scroll;
					
    	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()+naux*inc))
    		{
		      this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
         	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
      			this->mephscrollbar->setX(this->mephscrollbar->getWidth(1,&e),3);
					else
      			this->mephscrollbar->setY(this->mephscrollbar->getHeight(1,&e),3);
        }
    	  else
    		{
					if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+naux*inc))
					{
  		      this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
          	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
        			this->mephscrollbar->setX(this->mephscrollbar->getX(2,&e)-this->mephscrollbar->getWidth(3,&e),3);
					  else
        			this->mephscrollbar->setY(this->mephscrollbar->getY(2,&e)-this->mephscrollbar->getHeight(3,&e),3);
					}
					else
					{
     	   	  faux=(float)this->mephscrollbar->getScrollPosition()+(float)(naux*inc);
  	  	    this->mephscrollbar->putScrollPosition((int) faux);
          	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
  	  	  	  this->mephscrollbar->setX(this->mephscrollbar->getX(3,&e)+naux,3);
						else
  	  	  	  this->mephscrollbar->setY(this->mephscrollbar->getY(3,&e)+naux,3);
					}
		    }			
      	printf ("\n%f\n",this->mephscrollbar->getScrollPosition());
	      fflush(stdout);

        XMoveWindow((Display *)this->mephappimp->getDisplay(),this->id[3],mephscrollbar->getX(3,&i),mephscrollbar->getY(3,&i));						
      	if (this->neweventchange!=NULL)
	        neweventchange (this->mephscrollbar);
      	if (this->neweventchangetomephlistbox!=NULL)
	        (this->mephlistbox->*neweventchangetomephlistbox) (this->mephscrollbar);
			}

			if (this->neweventmouseover==NULL)
			  ScrollBar_mouseOver();
		  else
				this->neweventmouseover(this->mephscrollbar,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.state);
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
				if (this->mephscrollbar->getDecorated())
  			  this->drawDecoration();
  			if (this->neweventpaint==NULL)
	  		  ScrollBar_paint();
		    else
			  	this->neweventpaint(this->mephscrollbar,event.xexpose.x,event.xexpose.y,event.xexpose.width,event.xexpose.height,event.xexpose.count);
			}
		}break;

		case ColormapNotify:
		{
		  printf ("colormapnotify\n");
			fflush(stdout);
		}break;

		case FocusIn:
		{
			this->mephscrollbar->setFocused(FOCUSED);
			if (this->mephscrollbar->getDecorated())
  		  this->drawDecoration();
		  printf ("focusin\n");
			fflush(stdout);
		}break;

		case FocusOut:
		{
			this->mephscrollbar->setFocused(NOTFOCUSED);
			if (this->mephscrollbar->getDecorated())
  		  this->drawDecoration();
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
			  ScrollBar_configure();
		  else
				this->neweventconfigure(this->mephscrollbar,event.xconfigure.x,event.xconfigure.y,event.xconfigure.width,event.xconfigure.height);
			
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

Window MephScrollBarImp_X11::getWindow()
{
	return (this->id[0]);
}

Window MephScrollBarImp_X11::getWindow(int index,char *result)
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

map <int,Window> MephScrollBarImp_X11::getWindows()
{
	return (this->id);
}

int MephScrollBarImp_X11::getHeight()
{
	this->mephscrollbar->getHeight();
}

int MephScrollBarImp_X11::getWidth()
{
	this->mephscrollbar->getWidth();
}

void MephScrollBarImp_X11::scroll(XEvent event)
{
	long aux;
	char i,e;
	static float scroll;
	
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    scroll=this->mephscrollbar->getX(3,&e);
	else
    scroll=this->mephscrollbar->getY(3,&e);

	aux=0;
	
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getWidth(i,&e);
  else		
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getHeight(i,&e);

	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    aux=this->mephscrollbar->getWidth(0,&e)-aux;
	else
    aux=this->mephscrollbar->getHeight(0,&e)-aux;

			
  if (event.xany.window==this->id[0]) //SE HA PULSADO SOBRE LA VENTANA CONTENEDORA
	{
  	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
  	{
      if (event.xbutton.x<this->mephscrollbar->getX(3,&e))
 	    {
     	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMaxInterval()))
	      {
     			this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
  	   		this->mephscrollbar->setX(this->mephscrollbar->getWidth(1,&e),3);
    	  }
      	else
  	   	{
       		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMaxInterval();
     		  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMaxInterval());
	      	this->mephscrollbar->setX(scroll,3);
	 	    }			
  	  }
      else
      { 
        if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMaxInterval()))
  	    {
  		    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
     	  	this->mephscrollbar->setX(this->mephscrollbar->getX(2,&e)-this->mephscrollbar->getWidth(3,&e),3);
  	    }
        else
    		{
          scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMaxInterval();
	        this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMaxInterval());
  	      this->mephscrollbar->setX(scroll,3);
       	}			
      }
	  }
		else
		{
   	  if (event.xbutton.y<this->mephscrollbar->getY(3,&e))
      {
     	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMaxInterval()))
  	    {
     			this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
 	    		this->mephscrollbar->setY(this->mephscrollbar->getHeight(1,&e),3);
   		  }
   	  	else
 	     	{
       		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMaxInterval();
     		  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMaxInterval());
  	    	this->mephscrollbar->setY(scroll,3);
 	      }			
 	    }
   	  else
      { 
   	    if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMaxInterval()))
 		    {
 			    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
   	 	  	this->mephscrollbar->setY(this->mephscrollbar->getY(2,&e)-this->mephscrollbar->getHeight(3,&e),3);
 	      }
       	else
   		  {
       		scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMaxInterval();
         	this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMaxInterval());
 	        this->mephscrollbar->setY(scroll,3);
      	}			
      }
		}
	}
			 

  if (event.xany.window==this->id[1]) //SE HA PULSADO EL BOT”N DE DECREMENTO
	{
  	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		{
  	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval()))
	  	{
  	    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
			  this->mephscrollbar->setX(this->mephscrollbar->getWidth(1,&e),3);
      }
	    else
		  {
     		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
	  	  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval());
		  	this->mephscrollbar->setX(scroll,3);
  		}			
		}
		else
		{
  	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval()))
	  	{
  	    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
			  this->mephscrollbar->setY(this->mephscrollbar->getHeight(1,&e),3);
      }
	    else
		  {
     		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
	  	  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval());
		  	this->mephscrollbar->setY(scroll,3);
  		}			
		}
	}

	if (event.xany.window==this->id[2]) //SE HA PULSADO EL BOT”N DE INCREMENTO
  {
  	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		{
 	  	if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMinInterval()))
    	{
	    	this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
  		  this->mephscrollbar->setX(this->mephscrollbar->getX(2,&e)-this->mephscrollbar->getWidth(3,&e),3);
		  }
	  	else
   		{
   		  scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
		    this->mephscrollbar->putScrollPosition((this->mephscrollbar->getMinInterval()+this->mephscrollbar->getScrollPosition()));
	  		this->mephscrollbar->setX(scroll,3);
  		}
	  }
		else
		{
 	  	if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMinInterval()))
    	{
	    	this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
  		  this->mephscrollbar->setY(this->mephscrollbar->getY(2,&e)-this->mephscrollbar->getHeight(3,&e),3);
		  }
	  	else
   		{
   		  scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
		    this->mephscrollbar->putScrollPosition((this->mephscrollbar->getMinInterval()+this->mephscrollbar->getScrollPosition()));
	  		this->mephscrollbar->setY(scroll,3);
  		}
		}
 	}
	
  XMoveWindow((Display *)this->mephappimp->getDisplay(),this->id[3],mephscrollbar->getX(3,&i),mephscrollbar->getY(3,&i));
	
  /*AQUÕ SEGURAMENTE TENGA QUE HABER MAS CONDICIONES PORQUE, QUIZ¡S EL EVENTO EST… REDIRECCIONADO A UN FLOATINGWINDOW EN VEZ
	DE AL LISTBOX*/
	if (this->neweventchangetomephlistbox!=NULL)
	  (this->mephlistbox->*neweventchangetomephlistbox) (this->mephscrollbar);
 	if (this->neweventchange!=NULL)
    neweventchange (this->mephscrollbar);
}

void MephScrollBarImp_X11::drawDecoration()
{
	class MephGraphicParam *mephgraphicparam=new class MephGraphicParam[4];
	int addfunction;
	char e;
	char i;

	for (i=0;i<4;i++);
  	if ((this->mephscrollbar->getImagePath(i,&e)!=NULL) && (strcmp(mephscrollbar->getImagePath(i,&e),"")))
	  	this->mephscrollbar->showImage(i,i);
		
	this->mephscrollbar->setForeColor(0,0,0);
	mephgraphicparam[0].setRectangle(0,0,this->mephscrollbar->getWidth(1,&e)-1,this->mephscrollbar->getHeight(1,&e)-1);
	this->mephscrollbar->drawRectangles(mephgraphicparam,1,1);

	mephgraphicparam[0].setRectangle(0,0,this->mephscrollbar->getWidth(2,&e)-1,this->mephscrollbar->getHeight(2,&e)-1);
	this->mephscrollbar->drawRectangles(mephgraphicparam,1,2);
	/*FLECHAS DE DIRECCI”N*/
  if (this->mephscrollbar->getOrientation()==HORIZONTAL)
  {
 	  mephgraphicparam[0].setPoint(3,7);
 	  mephgraphicparam[1].setPoint(12,2);
	  mephgraphicparam[2].setPoint(12,11);
	  mephgraphicparam[3].setPoint(3,7);
	  this->mephscrollbar->fillPolygons(mephgraphicparam,4,0,0,1);

	  mephgraphicparam[0].setPoint(12,7);
	  mephgraphicparam[1].setPoint(3,11);
	  mephgraphicparam[2].setPoint(3,2);
	  mephgraphicparam[3].setPoint(12,7);
	  this->mephscrollbar->fillPolygons(mephgraphicparam,4,0,0,2);
  }
  else
  {
 	  mephgraphicparam[0].setPoint(7,2);
 	  mephgraphicparam[1].setPoint(2,12);
	  mephgraphicparam[2].setPoint(11,12);
	  mephgraphicparam[3].setPoint(7,2);
	  this->mephscrollbar->fillPolygons(mephgraphicparam,4,0,0,1);

	  mephgraphicparam[0].setPoint(7,12);
	  mephgraphicparam[1].setPoint(11,3);
	  mephgraphicparam[2].setPoint(2,3);
	  mephgraphicparam[3].setPoint(7,12);
	  this->mephscrollbar->fillPolygons(mephgraphicparam,4,0,0,2);
  }

	mephgraphicparam[0].setRectangle(0,0,this->mephscrollbar->getWidth(3,&e)-1,this->mephscrollbar->getHeight(3,&e)-1);
	this->mephscrollbar->drawRectangles(mephgraphicparam,1,3);

	XFlush((Display *)this->mephappimp->getDisplay());

	delete [] mephgraphicparam;
}

void MephScrollBarImp_X11::update(MephUpdateParam mephupdateparam)
{
	Display *disp=(Display *)this->mephappimp->getDisplay();
	Window id=this->id[0];
	int i;
	char e;
	float scroll;
	long aux;

  if (mephupdateparam & MephUVisible)
	{
	  if (this->mephscrollbar->getVisible())
		{
			for (i=0;i<4;i++)
		    XMapRaised(disp,this->id[i]);
		}
		else
		  XUnmapWindow(disp,id);
	}
	
	if ((mephupdateparam & (MephUCoord | MephUSize)))
	{
    XMoveResizeWindow (disp,id,mephscrollbar->getX(),mephscrollbar->getY(),mephscrollbar->getWidth(),
		  mephscrollbar->getHeight());

		if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		  if ((this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
			  this->mephscrollbar->setWidth(this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
		  else
			  this->mephscrollbar->setWidth(5,3);
		else
		  if ((this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
			  this->mephscrollbar->setHeight(this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
		  else
			  this->mephscrollbar->setHeight(5,3);

		XResizeWindow(disp,this->id[3],mephscrollbar->getWidth(3,&e),mephscrollbar->getHeight(3,&e));
	}
  else
	{
	  if (mephupdateparam & MephUCoord)
		   XMoveWindow(disp,id,mephscrollbar->getX(),mephscrollbar->getY());
	  if (mephupdateparam & MephUSize)
		{
		   XResizeWindow(disp,id,mephscrollbar->getWidth(),mephscrollbar->getHeight());
			
  		if (this->mephscrollbar->getOrientation()==HORIZONTAL)
	  	  if ((this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
		  	  this->mephscrollbar->setWidth(this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
		    else
  			  this->mephscrollbar->setWidth(5,3);
	  	else
		    if ((this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
			    this->mephscrollbar->setHeight(this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
  		  else
	  		  this->mephscrollbar->setHeight(5,3);

  		XResizeWindow(disp,this->id[3],mephscrollbar->getWidth(3,&e),mephscrollbar->getHeight(3,&e));
		}
	}

  if ((mephupdateparam & MephUOrientation) && (this->mephscrollbar->getVisible()))
	{
  	for (i=0;i<3;i++)
   		XMoveResizeWindow(disp,this->id[i],this->mephscrollbar->getX(i,&e),this->mephscrollbar->getY(i,&e),this->mephscrollbar->getWidth(i,&e),this->mephscrollbar->getHeight(i,&e));

		if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		  if ((this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
			  this->mephscrollbar->setWidth(this->mephscrollbar->getWidth(0,&e)-(this->mephscrollbar->getWidth(1,&e)+this->mephscrollbar->getWidth(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
		  else
			  this->mephscrollbar->setWidth(5,3);
		else
		  if ((this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e)))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin())>5)
			  this->mephscrollbar->setHeight(this->mephscrollbar->getHeight(0,&e)-(this->mephscrollbar->getHeight(1,&e)+this->mephscrollbar->getHeight(2,&e))-(this->mephscrollbar->getMax()-this->mephscrollbar->getMin()),3);
		  else
			  this->mephscrollbar->setHeight(5,3);
 		XMoveResizeWindow(disp,this->id[3],this->mephscrollbar->getX(3,&e),this->mephscrollbar->getY(3,&e),this->mephscrollbar->getWidth(3,&e),this->mephscrollbar->getHeight(3,&e));
	}

	if (mephupdateparam & MephUPositionUp)
	{
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    scroll=this->mephscrollbar->getX(3,&e);
	else
    scroll=this->mephscrollbar->getY(3,&e);

	aux=0;
	
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getWidth(i,&e);
  else		
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getHeight(i,&e);

	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    aux=this->mephscrollbar->getWidth(0,&e)-aux;
	else
    aux=this->mephscrollbar->getHeight(0,&e)-aux;

	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		{
  	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval()))
	  	{
//  	    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
			  this->mephscrollbar->setX(this->mephscrollbar->getWidth(1,&e),3);
      }
	    else
		  {
     		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
//	  	  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval());
		  	this->mephscrollbar->setX(scroll,3);
  		}			
		}
		else
		{
  	  if (this->mephscrollbar->getMin()>(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval()))
	  	{
//  	    this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMin());
			  this->mephscrollbar->setY(this->mephscrollbar->getHeight(1,&e),3);
      }
	    else
		  {
     		scroll-=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
//	  	  this->mephscrollbar->putScrollPosition(this->mephscrollbar->getScrollPosition()-this->mephscrollbar->getMinInterval());
		  	this->mephscrollbar->setY(scroll,3);
  		}			
		}
    XMoveWindow((Display *)this->mephappimp->getDisplay(),this->id[3],mephscrollbar->getX(3,&e),mephscrollbar->getY(3,&e));
		printf ("ARRIBA\n");
		fflush(stdout);
 	}

	if (mephupdateparam & MephUPositionDown)
  {
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    scroll=this->mephscrollbar->getX(3,&e);
	else
    scroll=this->mephscrollbar->getY(3,&e);

	aux=0;
	
	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getWidth(i,&e);
  else		
    for (i=1;i<4;i++)
	    aux+=this->mephscrollbar->getHeight(i,&e);

	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
    aux=this->mephscrollbar->getWidth(0,&e)-aux;
	else
    aux=this->mephscrollbar->getHeight(0,&e)-aux;

	if (this->mephscrollbar->getOrientation()==HORIZONTAL)
		{
 	  	if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMinInterval()))
    	{
//	    	this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
  		  this->mephscrollbar->setX(this->mephscrollbar->getX(2,&e)-this->mephscrollbar->getWidth(3,&e),3);
		  }
	  	else
   		{
   		  scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
//		    this->mephscrollbar->putScrollPosition((this->mephscrollbar->getMinInterval()+this->mephscrollbar->getScrollPosition()));
	  		this->mephscrollbar->setX(scroll,3);
  		}
	  }
		else
		{
 	  	if (this->mephscrollbar->getMax()<(this->mephscrollbar->getScrollPosition()+this->mephscrollbar->getMinInterval()))
    	{
//	    	this->mephscrollbar->putScrollPosition(this->mephscrollbar->getMax());
  		  this->mephscrollbar->setY(this->mephscrollbar->getY(2,&e)-this->mephscrollbar->getHeight(3,&e),3);
		  }
	  	else
   		{
   		  scroll+=((float) aux / ((float) this->mephscrollbar->getMax()-(float) this->mephscrollbar->getMin())) * (float) this->mephscrollbar->getMinInterval();
//		    this->mephscrollbar->putScrollPosition((this->mephscrollbar->getMinInterval()+this->mephscrollbar->getScrollPosition()));
	  		this->mephscrollbar->setY(scroll,3);
  		}
		}
    XMoveWindow((Display *)this->mephappimp->getDisplay(),this->id[3],mephscrollbar->getX(3,&e),mephscrollbar->getY(3,&e));
		printf ("ABAJO\n");
		fflush(stdout);
  }
	XFlush(disp);
}

const Display * MephScrollBarImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}

char MephScrollBarImp_X11::setTabIndex(MephTabIndex tabindex)
{
	return(this->mephappimp->setTabIndex(this->id[0],tabindex,this->mephscrollbar->getTabIndexEnabled()));
}

/***************************************MêTODOS DE EVENTOS**************************************/
void (*MephScrollBarImp_X11::catchEventMouseDown (void (*eventmousedown)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmousedown=eventmousedown;
	return (ScrollBar_mouseDown);
}

void (*MephScrollBarImp_X11::catchEventMouseUp (void (*eventmouseup)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseup=eventmouseup;
	return (ScrollBar_mouseUp);
}

void (*MephScrollBarImp_X11::catchEventMouseOver (void (*eventmouseover)(class MephScrollBar * mephscrollbar,int x,int y,unsigned int mephbutton))) (void)
{
	this->neweventmouseover=eventmouseover;
	return (ScrollBar_mouseOver);
}

void (*MephScrollBarImp_X11::catchEventPaint (void (*eventpaint)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height,int count))) (void)
{
	this->neweventpaint=eventpaint;
	return (ScrollBar_paint);
}

void (*MephScrollBarImp_X11::catchEventChange (void (*eventchange)(class MephScrollBar * mephscrollbar))) (void)
{
	this->neweventchange=eventchange;
	return (ScrollBar_change);
}

void (*MephScrollBarImp_X11::catchEventChange (void (MephListBox::*eventchange)(class MephScrollBar * mephscrollbar),class MephListBox * mephlistbox)) (void)
{
	this->mephlistbox=mephlistbox;
	this->neweventchangetomephlistbox=eventchange;
	return (ScrollBar_change);
}

void (*MephScrollBarImp_X11::catchEventConfigure (void (*eventconfigure)(class MephScrollBar * mephscrollbar,int x,int y,int width,int height))) (void)
{
	this->neweventconfigure=eventconfigure;
	return (ScrollBar_configure);
}

void (*MephScrollBarImp_X11::catchEventKeyDown (void (*eventkeydown)(class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeydown=eventkeydown;
	return (ScrollBar_keyDown);
}

void (*MephScrollBarImp_X11::catchEventKeyUp   (void (*eventkeyup)  (class MephScrollBar * mephscrollbar,char mephchar[5],int mephkeysymbol,unsigned int mephkeymask))) (void)
{
	this->neweventkeyup=eventkeyup;
	return (ScrollBar_keyUp);
}

/***********************************************************************************************/

void MephScrollBarImp_X11::undoEventMouseDown(void)
{
	this->neweventmousedown=NULL;
}

void MephScrollBarImp_X11::undoEventMouseUp(void)
{
	this->neweventmouseup=NULL;
}

void MephScrollBarImp_X11::undoEventMouseOver(void)
{
	this->neweventmouseover=NULL;
}

void MephScrollBarImp_X11::undoEventPaint(void)
{
	this->neweventpaint=NULL;
}

void MephScrollBarImp_X11::undoEventChange(void)
{
	this->neweventchange=NULL;
}

void MephScrollBarImp_X11::undoEventConfigure(void)
{
	this->neweventconfigure=NULL;
}

void MephScrollBarImp_X11::undoEventKeyDown(void)
{
	this->neweventkeydown=NULL;
}

void MephScrollBarImp_X11::undoEventKeyUp(void)
{
	this->neweventkeyup=NULL;
}
/***************************************MêTODOS DE EVENTOS ANTIGUOS*****************************/
void ScrollBar_mouseDown (void)
{
	printf ("buttonpress\n");
	fflush(stdout);
}

void ScrollBar_mouseUp (void)
{
	printf ("buttonrelease\n");
	fflush(stdout);
}

void ScrollBar_mouseOver (void)
{
/*	printf ("motionnotify\n");
	fflush(stdout);	*/
}

void ScrollBar_paint (void)
{
	if (!ScrollBar_event.xexpose.count)
	{
    printf ("expose\n");
	  fflush(stdout);
	}
}

void ScrollBar_change (void)
{
  printf ("change\n");
  fflush(stdout);
}

void ScrollBar_configure (void)
{
  printf ("CONFIGURE\n");
	fflush(stdout);
}

void ScrollBar_keyDown (void)
{
  printf ("Boton keypress \n");
	fflush(stdout);
}

void ScrollBar_keyUp (void)
{
  printf ("Mousekeyrelease \n");
	fflush(stdout);
}
/***********************************************************************************************/
