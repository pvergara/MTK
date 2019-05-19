#include "MephDrawImp_X11.h"
#include "MephDraw.h"
#include "MephPanelImp.h"

MephDrawImp_X11::~MephDrawImp_X11()
{
  delete this->mephvisobjimp;
//	delete this->mephappimp;
}

void MephDrawImp_X11::clearScreen(void)
{
  if (this->mephvisobjimp->getId()!=0)
	{
    XSetWindowBackgroundPixmap((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),None);
    XSetWindowBackground((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),0);
  	XClearWindow((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId());
	}
	else
	{
    XSetWindowBackgroundPixmap((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),None);
    XSetWindowBackground((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),0);
  	XClearWindow((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow());
	}
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::initValues(class MephDraw const * mephdraw,class MephVisObjImp const * mephvisobjimp)
{
	this->mephdraw=(class MephDraw *) mephdraw;
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
	
  if (this->mephvisobjimp->getId()!=0)
  	this->gc=XCreateGC((Display *) this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),0,NULL);
	else
  	this->gc=XCreateGC((Display *) this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),0,NULL);
}

void MephDrawImp_X11::setBackground()
{
  if (this->mephvisobjimp->getId()!=0)
	{
	  XSetWindowBackground((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->mephdraw->getForeColorIndex());
  	XClearWindow((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId());
	}
	else
	{
  	XSetWindowBackground((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->mephdraw->getForeColorIndex());
  	XClearWindow((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow());
	}
	
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::setAddFunction()
{
	if (this->mephvisobjimp!=0)
		XSetFunction((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mephdraw->getAddFunction());
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::setForeColor()
{
	if (this->mephvisobjimp!=NULL)
		XSetForeground((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mephdraw->getForeColorIndex());
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::setBackColor()
{
	if (this->mephvisobjimp!=NULL)
		XSetBackground((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mephdraw->getForeColorIndex());
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::drawPoints(class MephGraphicParam * mephgraphicparam, int n)
{
	XPoint *points=new XPoint[n];
	int i;

	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			points[i].x=mephgraphicparam[i].getX();
			points[i].y=mephgraphicparam[i].getY();
		}

    if (this->mephvisobjimp->getId()!=0)
  		XDrawPoints((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,points,n,CoordModeOrigin);
	  else
  		XDrawPoints((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,points,n,CoordModeOrigin);
	}
	
	delete []points;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::drawLines(class MephGraphicParam * mephgraphicparam, int n)
{
	XPoint *lines=new XPoint[n*2];
	int i,j;

	if (this->mephvisobjimp!=NULL)
	{
		for (i=j=0;j<n;i+=2,j++)
		{
			lines[i].x=mephgraphicparam[j].getX();
			lines[i].y=mephgraphicparam[j].getY();
			lines[i+1].x=mephgraphicparam[j].getX2();
			lines[i+1].y=mephgraphicparam[j].getY2();
		}			

    if (this->mephvisobjimp->getId()!=0)
  		XDrawLines((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,lines,n*2,CoordModeOrigin);
		else
  		XDrawLines((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,lines,n*2,CoordModeOrigin);
			
	}
	
	delete []lines;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::drawRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	XRectangle *rectangles=new XRectangle[n];
	int i;
	
	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			rectangles[i].x=mephgraphicparam[i].getX();
			rectangles[i].y=mephgraphicparam[i].getY();
			rectangles[i].width=mephgraphicparam[i].getWidth();
			rectangles[i].height=mephgraphicparam[i].getHeight();
		}			

    if (this->mephvisobjimp->getId()!=0)
  		XDrawRectangles((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,rectangles,n);
		else
  		XDrawRectangles((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,rectangles,n);
			
	}

	delete []rectangles;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::drawArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	XArc *arcs=new XArc[n];
	int i;
	
	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			arcs[i].x=mephgraphicparam[i].getX();
			arcs[i].y=mephgraphicparam[i].getY();
			arcs[i].width=mephgraphicparam[i].getWidth();
			arcs[i].height=mephgraphicparam[i].getHeight();
			arcs[i].angle1=mephgraphicparam[i].getAng();
			arcs[i].angle2=mephgraphicparam[i].getAng2();
		}			
    if (this->mephvisobjimp->getId()!=0)
		  XDrawArcs((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,arcs,n);
		else
 		  XDrawArcs((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,arcs,n);
	}
	
	delete []arcs;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode)
{
	XPoint *points=new XPoint[n];
	int i;
	
	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			points[i].x=mephgraphicparam[i].getX();
			points[i].y=mephgraphicparam[i].getY();
		}			

    if (this->mephvisobjimp->getId()!=0)
  		XFillPolygon((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,points,n,shape,mode);
    else
  		XFillPolygon((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,points,n,shape,mode);
	}

	delete []points;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::fillRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	XRectangle *rectangles=new XRectangle[n];
	int i;
	
	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			rectangles[i].x=mephgraphicparam[i].getX();
			rectangles[i].y=mephgraphicparam[i].getY();
			rectangles[i].width=mephgraphicparam[i].getWidth();
			rectangles[i].height=mephgraphicparam[i].getHeight();
		}			

    if (this->mephvisobjimp->getId()!=0)
  		XFillRectangles((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,rectangles,n);
    else
  		XFillRectangles((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,rectangles,n);
	}

	delete []rectangles;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}

void MephDrawImp_X11::fillArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	XArc *arcs=new XArc[n];
	int i;
	
	if (this->mephvisobjimp!=NULL)
	{
		for (i=0;i<n;i++)
		{
			arcs[i].x=mephgraphicparam[i].getX();
			arcs[i].y=mephgraphicparam[i].getY();
			arcs[i].width=mephgraphicparam[i].getWidth();
			arcs[i].height=mephgraphicparam[i].getHeight();
			arcs[i].angle1=mephgraphicparam[i].getAng();
			arcs[i].angle2=mephgraphicparam[i].getAng2();
		}

    if (this->mephvisobjimp->getId()!=0)
  		XFillArcs((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),this->gc,arcs,n);
		else
  		XFillArcs((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),this->gc,arcs,n);
	}
	delete []arcs;
	XFlush((Display *) this->mephvisobjimp->getDisplay());
}