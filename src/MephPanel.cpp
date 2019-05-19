#include "MephPanel.h"
#include <stdio.h>

MephPanel::MephPanel(class MephApp const * mephapp):backmode(SOLID)
{	
	this->imagemode[0]=MEPHWINDOWED|MEPHSOLID;
	this->addfunction=MEPHFUNCTIONCOPY;
//	this->mephimage=NULL;
	this->mephpanelsingleton=this->mephpanelsingleton->getMephPanelSingleton();
	this->mephpanelimp=this->mephpanelsingleton->getMephPanelImp();
	this->mephpanelimp->initValues(mephapp->getMephAppImp());
	
}

MephPanel::~MephPanel()
{
//  delete this->mephimage;
  delete this->mephpanelimp;
}

void MephPanel::addTo (const class MephVisObjImp * mephvisobjimp)
{
	class MephVisObjImp *mvoi=(class MephVisObjImp *) mephvisobjimp;
	
	this->x[0]=0;
	this->y[0]=0;
	this->height[0]=mvoi->getHeight();
	this->width[0]=mvoi->getWidth();
	
  this->mephpanelimp->initValues((const class MephPanel *) this,mephvisobjimp);
}

void MephPanel::addTo (const class MephVisObjImp * mephvisobjimp,short x,short y,unsigned short width,unsigned short height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
  this->mephpanelimp->initValues((const class MephPanel *) this,mephvisobjimp);
}


void MephPanel::setAddFunction(int addfunction)
{
  this->addfunction=addfunction;
	this->mephpanelimp->changeAddFunction(addfunction);
}

int MephPanel::getAddFunction()
{
  return(this->addfunction);
}

const class MephPanelImp * MephPanel::getMephPanelImp()
{
	return(this->mephpanelimp);
}

/*unsigned short MephPanel::getBackColorR()
{
  return(this->backcolor.getRed());
}

unsigned short MephPanel::getBackColorG()
{
  return(this->backcolor.getGreen());
}

unsigned short MephPanel::getBackColorB()
{
  return(this->backcolor.getBlue());
}

unsigned short MephPanel::getForeColorR()
{
	return(this->forecolor.getRed());
}

unsigned short MephPanel::getForeColorG()
{
	return(this->forecolor.getGreen());
}

unsigned short MephPanel::getForeColorB()
{
	return(this->forecolor.getBlue());
}

unsigned long MephPanel::getBackColorIndex()
{
  return(this->backcolor.getColorIndex());
}

unsigned long MephPanel::getForeColorIndex()
{
	return(this->forecolor.getColorIndex());
}
			
void MephPanel::setBackColor(unsigned short red,unsigned short green,unsigned short blue)
{
  this->backcolor.setColor(red,green,blue);
}

void MephPanel::setBackColor(unsigned long colorindex)
{
  this->backcolor.setColor(colorindex);
}

void MephPanel::setForeColor(unsigned short red,unsigned short green,unsigned short blue)
{
	this->forecolor.setColor(red,green,blue);
}

void MephPanel::setForeColor(unsigned long colorindex)
{
	this->forecolor.setColor(colorindex);
}*/

void MephPanel::refresh()
{
	this->mephpanelimp->refresh();
}

void MephPanel::move(int x,int y)
{
	this->x[0]=x;
	this->y[0]=y;
}

void MephPanel::moveResize(int x,int y,unsigned int width,unsigned int height)
{
	this->x[0]=x;
	this->y[0]=y;
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephpanelimp->resize();
}

void MephPanel::resize(unsigned int width,unsigned int height)
{
	this->width[0]=width;
	this->height[0]=height;
	
	this->mephpanelimp->resize();
}

void MephPanel::refresh(int x,int y,unsigned int width,unsigned int height)
{
	this->mephpanelimp->refresh(x,y,width,height);
}


/*SEGURAMENTE SE ELIMINEN LOS 4 MTODOS SIGUIENTES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*void MephPanel::createImage()
{
  if (this->mephimage==NULL)
	{
  	this->mephimage=new class MephImage;
		this->mephimage->initValues(*(this->mephpanelimp));
	}
}

void MephPanel::deleteImage()
{
  delete this->mephimage;
}

char MephPanel::loadImage(char *path)
{
  if (this->mephimage!=NULL)
    this->mephimage->loadImage(path);
//	return();
}

char MephPanel::showImage()
{
  if (this->mephimage!=NULL)
	{
    this->mephimage->showImage();
	  return (0);
	}
	else
	  return (-1);
} HHHHHHHHAAASSSSSSSSSSSTTTTTTTTTTAAAAAA AAAAAQQQQQQQQQQUUUUUUUUUUIIIIIIII!!!!!!!!!!!*/

/*unsigned int MephPanel::getImageWidth()
{
  if (this->mephimage!=NULL)
		return (this->mephimage->getWidth());
	else
		return(0);
}

unsigned int MephPanel::getImageHeight()
{
  if (this->mephimage!=NULL)
		return (this->mephimage->getHeight());
  else
		return (0);
}

char MephPanel::setImageWidth(int width)
{
  if (this->mephimage!=NULL)
	{
		this->mephimage->setWidth(width);
		return (1);
	}
  else
		return (-1);
}

char MephPanel::setImageHeight(int height)
{
  if (this->mephimage!=NULL)
	{
    this->mephimage->setHeight(height);
		return (1);
	}
  else
		return (-1);
}

const char * MephPanel::getImageData()
{
	if (this->mephimage!=NULL)
		return (this->mephimage->getImageData());
}

void MephPanel::getImageShapeColor (int *red,int *green,int *blue)
{
	if (this->mephimage!=NULL)
		this->mephimage->getShapeColor(red,green,blue);
}*/

char MephPanel::getBackMode()
{
	return (this->backmode);
}


/*void MephPanel::setBackground(unsigned short red,unsigned short green,unsigned short blue)
{
	this->backmode=SOLID;
	this->forecolor.setColor(red,green,blue);
	this->mephpanelimp->setBackground();
}

void MephPanel::setBackground(unsigned long colorindex)
{
	this->backmode=SOLID;
	this->forecolor.setColor(colorindex);
	this->mephpanelimp->setBackground();
}

void MephPanel::setBackground(char * image)
{
	this->backmode|=IMAGE;

	if (this->mephimage==NULL)
	{
	  this->mephimage=new class MephImage;
    this->mephimage->initValues(*(this->mephpanelimp));
	}

  this->mephimage->loadImage(image);

  if (!(this->imagemode & MEPHIMAGED))
	{
	  this->mephimage->setWidth(this->width);
    this->mephimage->setHeight(this->height);
	}
	else
	{
		this->width=this->mephimage->getWidth();
		this->height=this->mephimage->getHeight();
		this->mephpanelimp->resize();
	}
	
	this->mephpanelimp->setBackground();
}

void MephPanel::setBackground(char *image, unsigned char imagemode)
{
  this->imagemode=imagemode;
	this->setBackground(image);
}*/


void MephPanel::copyBackPixmap()
{
	this->mephpanelimp->copyBackPixmap();
}

void MephPanel::backPixmapToMe()
{
	/******/
	this->backmode=SHAPE;
	/******/
	this->mephpanelimp->backPixmapToMe();
}

char MephPanel::getImageMode()
{
	return (this->imagemode[0]);
}

char MephPanel::getImageMode(int index,char *result)
{
	if (this->imagemode[index])
	{
		result[0]=1;
	  return (this->imagemode[0]);
	}
	else
	{
		result[0]=0;
	  return (0);
	}
}

map <int,char> MephPanel::getImageModes()
{
	return (this->imagemode);
}

/*const char * MephPanel::getImagePath()
{
	if (this->mephimage)
		return (this->mephimage->getImagePath());
	else
		return (NULL);
}*/
