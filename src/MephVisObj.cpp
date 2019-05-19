#include "MephVisObj.h"

MephVisObj::MephVisObj():mephdraw(NULL),mephimage(NULL)/*,mephtextraw(NULL)*/,name(NULL),visible(1),tabindex(0),focused(NOTFOCUSED),decorated(1)
{
  x[0]=1;
  y[0]=1;
	width[0]=200;
	height[0]=200;
	imagemode[0]=0;
}

MephVisObj::MephVisObj(const MephVisObj &right)
      : name(NULL),visible(1)
{
  x[0]=1;
  y[0]=1;
	width[0]=200;
	height[0]=200;
	imagemode[0]=0;
}


MephVisObj::~MephVisObj()
{
  delete this->name;
}


const MephVisObj & MephVisObj::operator=(const MephVisObj &right)
{
}


int MephVisObj::operator==(const MephVisObj &right) const
{
}

int MephVisObj::operator!=(const MephVisObj &right) const
{
}


char const * MephVisObj::getName() const
{
  return (this->name);
}


void MephVisObj::setDecorated(char decorated)
{
	this->decorated=decorated;
}

char MephVisObj::getDecorated()
{
	return(this->decorated);
}

int MephVisObj::getX()
{
  return (this->x[0]);
}

int MephVisObj::getY()
{
  return (this->y[0]);
}

int MephVisObj::getWidth()
{
  return (this->width[0]);
}

int MephVisObj::getHeight()
{
  return (this->height[0]);
}


int MephVisObj::getX(int index,char *result)
{
	if (x[index])
	{
		result[0]=1;
    return (this->x[index]);
	}
	else
	{
		result[0]=0;
    return (0);
	}
}

int MephVisObj::getY(int index,char *result)
{
	if (y[index])
	{
		result[0]=1;
    return (this->y[index]);
	}
	else
	{
		result[0]=0;
    return (0);
	}
}

int MephVisObj::getWidth(int index,char *result)
{
	if (width[index])
	{
		result[0]=1;
    return (this->width[index]);
	}
	else
	{
		result[0]=0;
    return (0);
	}
}

int MephVisObj::getHeight(int index,char *result)
{
	if (height[index])
	{
		result[0]=1;
    return (this->height[index]);
	}
	else
	{
		result[0]=0;
    return (0);
	}
}

map <int,int> MephVisObj::getXs()
{
  return (this->x);
}

map <int,int> MephVisObj::getYs()
{
  return (this->y);
}

map <int,int> MephVisObj::getWidths()
{
  return (this->width);
}

map <int,int> MephVisObj::getHeights()
{
  return (this->height);
}


char MephVisObj::getVisible()
{
  return (this->visible);
}

char MephVisObj::getIsPanel()
{
}

void MephVisObj::initDrawValues(class MephVisObjImp const *mephvisobjimp)
{
	this->mephdraw=new MephDraw;
	this->mephdraw->initValues(mephvisobjimp);
}

void MephVisObj::initImageValues(class MephVisObjImp const *mephvisobjimp)
{
	this->mephimage=new MephImage;
	this->mephimage->initValues(mephvisobjimp);
}

void MephVisObj::initTextValues(class MephVisObjImp const *mephvisobjimp)
{
	this->mephtextraw=new MephTextRaw;
	this->mephtextraw->initValues(mephvisobjimp);
}
			
void MephVisObj::deleteMephDraw()
{
	delete this->mephdraw;
	this->mephdraw=NULL;
}

void MephVisObj::deleteMephImage()
{
	delete this->mephimage;
	this->mephimage=NULL;
}

void MephVisObj::deleteMephTextRaw()
{
	delete this->mephtextraw;
	this->mephtextraw=NULL;
}


void MephVisObj::setDrawAddFunction(int addfunction)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setAddFunction(addfunction);
}

int MephVisObj::getDrawAddFunction()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getAddFunction());
}

/*void MephVisObj::setTextRawAddFunction(int addfunction)
{
}

int getTextRawAddFunction()
{
}*/

void MephVisObj::showText()
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->show();
}

char MephVisObj::setFontName(char fontname[256])
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->setFontName(fontname));
	else
		return(0);
}

char *MephVisObj::getFontName()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getFontName());
	else
		return(0);
}

char MephVisObj::getBold()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getBold());
	else
		return(0);
}

char MephVisObj::setBold(char bold)
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->setBold(bold));
	else
		return(0);
}

char MephVisObj::getItalic()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getItalic());
	else
		return(0);
}

char MephVisObj::setItalic(char italic)
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->setItalic(italic));
	else
		return(0);
}

char MephVisObj::getTwoBytesChar()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getTwoBytesChar());
	else
		return(0);
}

void MephVisObj::setTwoBytesChar(char twobyteschar)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setTwoBytesChar(twobyteschar);
}

char MephVisObj::getHighlight()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getHighlight());
	else
		return(0);
}

void MephVisObj::setHighlight(int highlight)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setHighlight(highlight);
}

char MephVisObj::getTextSize()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getSize());
	else
		return(0);
}

char MephVisObj::setTextSize(char size)
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getTwoBytesChar());
	else
		return(0);
}

void MephVisObj::setText(char *text)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setText(text);
}

char *MephVisObj::getText()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getText());
	else
		return(0);
}

char MephVisObj::setMaxLength(unsigned long maxlength)
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->setMaxLength(maxlength));
	else
		return(0);
}

char MephVisObj::getMaxLength()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getMaxLength());
	else
		return(0);
}


void MephVisObj::setTextX(int x)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setX(x);
}

int MephVisObj::getTextX()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getX());
	else
		return(0);
}

void MephVisObj::setTextY(int y)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setY(y);
}

int MephVisObj::getTextY()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getY());
	else
		return(0);
}

void MephVisObj::setTextWidth(unsigned int width)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setWidth(width);
}

int MephVisObj::getTextWidth()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getWidth());
	else
		return(0);
}

void MephVisObj::setTextHeight(unsigned int height)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setHeight(height);
}

int MephVisObj::getTextHeight()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getHeight());
	else
		return(0);
}

int MephVisObj::getLineSpace()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getLineSpace());
	else
		return(0);
}

void MephVisObj::setLineSpace(int linespace)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setLineSpace(linespace);
}
	
unsigned short MephVisObj::getTextForeColorR()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getForeColorR());
	else
		return(0);
}

unsigned short MephVisObj::getTextForeColorG()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getForeColorG());
	else
		return(0);
}

unsigned short MephVisObj::getTextForeColorB()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getForeColorB());
	else
		return(0);
}

unsigned long  MephVisObj::getTextForeColorIndex()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getForeColorIndex());
	else
		return(0);
}

void MephVisObj::setTextForeColor(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setForeColor(red,green,blue);
}

void MephVisObj::setTextForeColor(unsigned long colorindex)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setForeColor(colorindex);
}

unsigned short MephVisObj::getTextBackColorR()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getBackColorR());
	else
		return(0);
}

unsigned short MephVisObj::getTextBackColorG()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getBackColorG());
	else
		return(0);
}

unsigned short MephVisObj::getTextBackColorB()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getBackColorB());
	else
		return(0);
}

unsigned long MephVisObj::getTextBackColorIndex()
{
	if (this->mephtextraw!=NULL)
		return(this->mephtextraw->getBackColorIndex());
	else
		return(0);
}

	
void MephVisObj::setTextBackColor(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setBackColor(red,green,blue);
}

void MephVisObj::setTextBackColor(unsigned long colorindex)
{
	if (this->mephtextraw!=NULL)
		this->mephtextraw->setBackColor(colorindex);
}

void MephVisObj::clearScreen(void)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->clearScreen();
}

unsigned short MephVisObj::getBackColorR()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getBackColorR());
}

unsigned short MephVisObj::getBackColorG()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getBackColorG());
}

unsigned short MephVisObj::getBackColorB()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getBackColorB());
}

unsigned short MephVisObj::getForeColorR()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getForeColorR());
}

unsigned short MephVisObj::getForeColorG()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getForeColorG());
}

unsigned short MephVisObj::getForeColorB()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getForeColorB());
}

unsigned long MephVisObj::getBackColorIndex()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getBackColorIndex());
}

unsigned long MephVisObj::getForeColorIndex()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getForeColorIndex());
}
			
void MephVisObj::setBackColor(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setBackColor(red,green,blue);
}

void MephVisObj::setBackColor(unsigned long colorindex)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setBackColor(colorindex);
}

void MephVisObj::setForeColor(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephdraw!=NULL)
	{
		this->mephdraw->setForeColor(red,green,blue);
//		this->backcolor[0]=this->mephdraw->getForeColorIndex();
	}
}

void MephVisObj::setForeColor(unsigned long colorindex)
{
	if (this->mephdraw!=NULL)
	{
		this->mephdraw->setForeColor(colorindex);
		this->backcolor[0]=colorindex;
	}
}

void MephVisObj::setBackground(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephdraw!=NULL)
	{
  	this->mephdraw->setBackground(red,green,blue);
		this->backcolor[0]=this->mephdraw->getForeColorIndex();
	}
}

void MephVisObj::setBackground(unsigned long colorindex)
{
	if (this->mephdraw!=NULL)
	{
		this->backcolor[0]=colorindex;
  	this->mephdraw->setBackground(colorindex);
	}
}

void MephVisObj::setBackground()
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setBackground(this->backcolor[0]);
}

void MephVisObj::setBackground(unsigned short red,unsigned short green,unsigned short blue,int index)
{
	if (this->mephdraw!=NULL)
	{
  	this->mephdraw->setBackground(red,green,blue,index);
		this->backcolor[index]=this->mephdraw->getForeColorIndex();
	}
}

void MephVisObj::setBackground(unsigned long colorindex,int index)
{
	if (this->mephdraw!=NULL)
	{
		this->backcolor[index]=colorindex;
  	this->mephdraw->setBackground(colorindex,index);
	}
}

void MephVisObj::setBackground(int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setBackground(this->backcolor[index]);
}

unsigned long MephVisObj::getBackColor()
{
	return (this->backcolor[0]);
}

unsigned long MephVisObj::getBackColor(int index,char *result)
{
	if (this->backcolor[index])
	{
		result[0]=1;
	  return (this->backcolor[0]);
	}
	else
	{
		result[0]=0;
	  return (0);
	}
}

map <int,unsigned long> MephVisObj::getBackColors()
{
	return (this->backcolor);
}

void MephVisObj::drawPoints(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawPoints(mephgraphicparam,n);
}

void MephVisObj::drawLines(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawLines(mephgraphicparam,n);
}

void MephVisObj::drawRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawRectangles(mephgraphicparam,n);
}

void MephVisObj::drawArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawArcs(mephgraphicparam,n);
}

void MephVisObj::fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillPolygons(mephgraphicparam,n,shape,mode);
}

void MephVisObj::fillRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillRectangles(mephgraphicparam,n);
}

void MephVisObj::fillArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillArcs(mephgraphicparam,n);
}

void MephVisObj::drawPoints(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawPoints(mephgraphicparam,n,index);
}

void MephVisObj::drawLines(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawLines(mephgraphicparam,n,index);
}

void MephVisObj::drawRectangles(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawRectangles(mephgraphicparam,n,index);
}

void MephVisObj::drawArcs(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->drawArcs(mephgraphicparam,n,index);
}

void MephVisObj::fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillPolygons(mephgraphicparam,n,shape,mode,index);
}

void MephVisObj::fillRectangles(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillRectangles(mephgraphicparam,n,index);
}

void MephVisObj::fillArcs(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->fillArcs(mephgraphicparam,n,index);
}


void MephVisObj::setDrawMode(char mode)
{
	if (this->mephdraw!=NULL)
		this->mephdraw->setMode(mode);
}

char MephVisObj::getDrawMode()
{
	if (this->mephdraw!=NULL)
		return(this->mephdraw->getMode());
}

void MephVisObj::refreshImage(void)
{
	if (this->mephimage!=NULL)
		this->mephimage->refresh();
}

void MephVisObj::refreshImage(int index)
{
	if (this->mephimage!=NULL)
		this->mephimage->refresh(index);
}

void MephVisObj::setBackground(char * image)
{
	this->setBackground(image,this->imagemode[0]);
}

void MephVisObj::setBackground(char * image, unsigned char imagemode)
{
	this->setBackground(image,imagemode,0,0);
}
void MephVisObj::setBackground(char * image,unsigned char imagemode,int indexImage,int indexWindow)
{
  /*MephImage comprobar  el imagemode y si ve que es MEPHIMAGED y no MEPHWINDOWED
	no har  caso ni al ancho ni al alto*/
	if (this->mephimage!=NULL)
		this->mephimage->setBackground(image,this->width[0],this->height[0],imagemode,indexImage,indexWindow);
}

void MephVisObj::setImageAddFunction(int addfunction)
{
	if (this->mephimage!=NULL)
		this->mephimage->setAddFunction(addfunction);
}

int MephVisObj::getImageAddFunction()
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getAddFunction(	));
}

char MephVisObj::showImage()
{
  this->showImage(0,0);
}

char MephVisObj::showImage(int indexImage,int indexWindow)
{
	if (this->mephimage!=NULL)
		this->mephimage->showImage(indexImage,indexWindow);
}

unsigned int MephVisObj::getImageWidth()
{
	if (this->mephimage!=NULL)
		return (this->mephimage->getWidth());
}

unsigned int MephVisObj::getImageWidth(int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getWidth(index,result));
}

unsigned int MephVisObj::getImageHeight()
{
	if (this->mephimage!=NULL)
		return (this->mephimage->getHeight());
}

unsigned int MephVisObj::getImageHeight(int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getHeight(index,result));
}

char MephVisObj::setImageWidth(int width)
{
	if (this->mephimage!=NULL)
		this->mephimage->setWidth(width);
}

char MephVisObj::setImageWidth(int width,int index)
{
	if (this->mephimage!=NULL)
		this->mephimage->setWidth(width,index);
}

char MephVisObj::setImageHeight(int height)
{
	if (this->mephimage!=NULL)
		this->mephimage->setHeight(height);
}

char MephVisObj::setImageHeight(int height,int index)
{
	if (this->mephimage!=NULL)
		this->mephimage->setHeight(height,index);
}

const char * MephVisObj::getImageData()
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImageData());
}

const char * MephVisObj::getImageData(int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImageData(index,result));
}

void MephVisObj::getImageShapeColor (int *red,int *green,int *blue)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getShapeColor(red,green,blue));
}

void MephVisObj::getImageShapeColor (int *red,int *green,int *blue,int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getShapeColor(red,green,blue,index,result));
}

const char * MephVisObj::getImagePath()
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImagePath());
}

const char * MephVisObj::getImagePath(int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImagePath(index,result));
}

char MephVisObj::getBackMode()
{
}

char MephVisObj::getImageMode()
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImageMode());
}

char MephVisObj::getImageMode(int index,char *result)
{
	if (this->mephimage!=NULL)
		return(this->mephimage->getImageMode(index,result));
}

MephTabIndex MephVisObj::getTabIndex()
{
	return(this->tabindex);
}

void MephVisObj::putTabIndex (MephTabIndex tabindex)
{
	this->tabindex=tabindex;
}

char MephVisObj::getTabIndexEnabled ()
{
	return(this->visible /*& this->enable*/);
}

char MephVisObj::getFocused()
{
	return (this->focused);
}

void MephVisObj::setFocused(char focused)
{
	this->focused=focused;
}

void MephVisObj::shape(char *path)
{
	if (this->mephimage!=NULL)
		this->mephimage->shape(path);
}

void MephVisObj::shape(char *path,int indexImage,int indexWindow)
{
	if (this->mephimage!=NULL)
		this->mephimage->shape(path,indexImage,indexWindow);
}

void MephVisObj::unshape (void)
{
	if (this->mephimage!=NULL)
		this->mephimage->unshape();
}
