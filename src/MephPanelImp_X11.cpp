#include "MephPanelImp_X11.h"
#include "MephPanel.h"
#include <stdio.h>

MephPanelImp_X11::MephPanelImp_X11():aux(NULL),mephpanel(NULL),mephvisobjimp(NULL)//,mephpanelimp(NULL)
{
}

MephPanelImp_X11::~MephPanelImp_X11()
{
	delete this->mephvisobjimp;
	delete this->mephpanel;
	delete this->mephappimp;
}

void MephPanelImp_X11::initValues(const class MephPanel *mephpanel,const class MephVisObjImp * mephvisobjimp)
{
	Display *disp=(Display *) this->mephappimp->getDisplay();
	
	this->mephpanel=(class MephPanel *) mephpanel;
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
	

	this->id[0]=XCreatePixmap(disp,this->mephvisobjimp->getWindow(),this->mephpanel->getWidth(),this->mephpanel->getHeight(),DefaultDepth(disp,this->mephappimp->getScreen()));
  //ESTE PIXMAP SE USARµ PARA COPIAR EL FONDO DE LOS PIXMAP SOBRE LOS QUE VAMOS A ESCRIBIR
	//PARA MAS INFORMACIÓN ECHAR UN VISTAZO A LOS MTODOS "copyBackPixmap" y "backPixmapToMe"
	this->aux=XCreatePixmap(disp,this->id[0],this->mephpanel->getWidth(),this->mephpanel->getHeight(),DefaultDepth(disp,this->mephappimp->getScreen()));
	
	this->gc=XCreateGC(disp,this->id[0],0,NULL);
}

void MephPanelImp_X11::initValues(class MephAppImp const *mephappimp)
{
	this->mephappimp=(class MephAppImp *) mephappimp;
}

void MephPanelImp_X11::copyBackPixmap()
{
	XCopyArea((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(),this->aux,this->gc,this->mephpanel->getX(),this->mephpanel->getY(),this->mephpanel->getWidth(),this->mephpanel->getHeight(),0,0);
}


void MephPanelImp_X11::backPixmapToMe()
{
	XCopyArea((Display *)this->mephappimp->getDisplay(),this->aux,this->id[0],this->gc,0,0,this->mephpanel->getWidth(),this->mephpanel->getHeight(),0,0);
}

void MephPanelImp_X11::changeAddFunction(int addfunction)
{
	XSetFunction((Display *)this->mephappimp->getDisplay(),this->gc,addfunction);
}

GC MephPanelImp_X11::getGC()
{
	return (this->gc);
}

Pixmap MephPanelImp_X11::getId()
{
	return (this->id[0]);
}

Pixmap MephPanelImp_X11::getId(int index,char *result)
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

map <int,Pixmap> MephPanelImp_X11::getIds()
{
	return (this->id);
}

int MephPanelImp_X11::getWidth()
{
	return (this->mephpanel->getWidth());
}

int MephPanelImp_X11::getHeight()
{
	return (this->mephpanel->getHeight());
}

void MephPanelImp_X11::refresh()
{
	if (this->mephvisobjimp) /*SI NO COPIAMOS EN UN PANEL DIRECTAMENTE.
														AQUÍ AFECTAN LOS MODOS AZULEJO DE CARGA DE IMµGENES*/
  {
	  if (!((this->mephpanel->getImageMode()) & MEPHIMAGE))
    	XCopyArea((Display *)this->mephappimp->getDisplay(),this->id[0],this->mephvisobjimp->getWindow(),this->gc,0,0,this->mephpanel->getWidth(),this->mephpanel->getHeight(),this->mephpanel->getX(),this->mephpanel->getY());
		else
		{
			XSetWindowBackgroundPixmap((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(),this->id[0]);
			XClearWindow((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow());
		}
	}
	/*ESTE YA NO SIRVE
	else
  	XCopyArea(this->MephAppImpX11_getDisplay(),this->id,this->mephpanelimp->getId(),this->gc,0,0,this->mephpanel->getWidth(),this->mephpanel->getHeight(),this->mephpanel->getX(),this->mephpanel->getY());
	/******************/	
	XFlush((Display *)this->mephappimp->getDisplay());
}

void MephPanelImp_X11::refresh(int x,int y,unsigned int width,unsigned int height)
{
/*	XGCValues gcval;
	
	XGetGCValues(this->MephAppImpX11_getDisplay(),this->gc,GCStipple,&gcval);
	
  XShapeCombineMask(this->MephAppImpX11_getDisplay(),this->mephvisobjimp->getWindow(),ShapeBounding,0,0,gcval.stipple,ShapeSet);
	XSetWindowBackgroundPixmap(this->MephAppImpX11_getDisplay(),this->mephvisobjimp->getWindow(),this->id);
	
	XClearWindow(this->MephAppImpX11_getDisplay(),this->mephvisobjimp->getWindow());*/
	if (this->mephvisobjimp) /*SI NO COPIAMOS EN UN PANEL DIRECTAMENTE.
														AQUÍ AFECTAN LOS MODOS AZULEJO DE CARGA DE IMµGENES*/
  {
  	XCopyArea((Display *)this->mephappimp->getDisplay(),this->id[0],this->mephvisobjimp->getWindow(),this->gc,x,y,width,height,x,y);
    if (this->mephpanel->getImageMode() & MEPHIMAGE)
		{
			XSetWindowBackgroundPixmap((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow(),this->id[0]);
			XClearWindow((Display *)this->mephappimp->getDisplay(),this->mephvisobjimp->getWindow());
		}
	}
	/*ESTE YA NO SIRVE
	else
	  XCopyArea(this->MephAppImpX11_getDisplay(),this->id,this->mephpanelimp->getId(),this->gc,0,0,width,height,x,y);
  /******************/		
	XFlush((Display *)this->mephappimp->getDisplay());
}


void MephPanelImp_X11::resize()
{
	Display *disp=(Display *)this->mephappimp->getDisplay();

	XFreeGC(disp,this->gc);
	XFreePixmap(disp,this->id[0]);
	
	if (this->mephvisobjimp)
  	this->id[0]=XCreatePixmap(disp,this->mephvisobjimp->getWindow(),this->mephpanel->getWidth(),this->mephpanel->getHeight(),DefaultDepth(disp,this->mephappimp->getScreen()));
	/*ESTE YA NO SIRVE
	else
  	this->id=XCreatePixmap(disp,this->mephpanelimp->getWindow(),this->mephpanel->getWidth(),this->mephpanel->getHeight(),DefaultDepth(disp,this->MephAppImpX11_getScreen()));
	/******************/
	
 	this->gc=XCreateGC(disp,this->id[0],0,NULL);
  
	this->setBackground();
}

void MephPanelImp_X11::setBackground()
{
	Display *disp=(Display *)this->mephappimp->getDisplay();

//	if (!this->mephpanel->getBackMode()) /*MODO SÓLIDO*/
	if (!(this->mephpanel->getBackMode() & SHAPE))
  {	
	  XSetForeground(disp,this->gc,this->mephpanel->getForeColorIndex());
	  XFillRectangle(disp,this->id[0],this->gc,0,0,this->mephpanel->getWidth(),this->mephpanel->getHeight());
	}
//	else /*ESTE ELSE FUERA*/
	if (this->mephpanel->getBackMode() & IMAGE)
	{
    /*ESTO YA NO HARÍA FALTA -->/*MODO SÓLIDO PERO CON IMAGEN
	  if ((!((this->mephpanel->getImageMode()) & MEPHIMAGE)) && (!(this->mephpanel->getImageMode() & MEPHGEOMETRIC)) ) 
		{
  		if (this->mephpanel->getWidth()>this->mephpanel->getImageWidth())
	  	{
    	  XSetForeground(disp,this->gc,this->mephpanel->getForeColorIndex());
	      XFillRectangle(disp,this->id,this->gc,this->mephpanel->getImageWidth(),0,this->mephpanel->getWidth(),this->mephpanel->getHeight());
  		}
	  	if (this->mephpanel->getHeight()>this->mephpanel->getImageHeight())
  		{
	      XSetForeground(disp,this->gc,this->mephpanel->getForeColorIndex());
	      XFillRectangle(disp,this->id,this->gc,0,this->mephpanel->getImageHeight(),this->mephpanel->getWidth(),this->mephpanel->getHeight());
		  }
		}
		/*************************/
//		else
  		if (this->mephpanel->getImageMode() & MEPHGEOMETRIC)
			{
  	  	if (this->mephpanel->getWidth()!=this->mephpanel->getImageWidth())
					this->mephpanel->setImageWidth(this->mephpanel->getWidth());
	    	if (this->mephpanel->getHeight()!=this->mephpanel->getImageHeight())
					this->mephpanel->setImageHeight(this->mephpanel->getHeight());
 			}
   	this->mephpanel->showImage();
	}
}

const Display * MephPanelImp_X11::getDisplay()
{
	return(this->mephappimp->getDisplay());
}
