#include "MephDraw.h"

MephDraw::MephDraw():mode(0),addfunction(MEPHFUNCTIONCOPY)
{
	this->mephdrawsingleton=this->mephdrawsingleton->getMephDrawSingleton();
	this->mephdrawimp=this->mephdrawsingleton->getMephDrawImp();
}

MephDraw::~MephDraw()
{
	delete this->mephdrawimp;
//  delete this->mephdrawsingleton;
}


/*void MephDraw::initValues(const class MephVisObjImp * mephvisobjimp,class MephApp const * mephapp)
{
	this->mephdrawimp->initValues(this,mephapp->getMephAppImp(),mephvisobjimp);
}*/

void MephDraw::clearScreen(void)
{
	this->mephdrawimp->clearScreen();
}

void MephDraw::initValues(class MephVisObjImp const * mephvisobjimp)
{
	this->mephdrawimp->initValues(this,mephvisobjimp);
	this->forecolor.initValues(mephvisobjimp);
	this->backcolor.initValues(mephvisobjimp);
}
	
void MephDraw::drawPoints(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->drawPoints(mephgraphicparam,n,0);
}

void MephDraw::drawLines(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->drawLines(mephgraphicparam,n,0);
}

void MephDraw::drawRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->drawRectangles(mephgraphicparam,n,0);
}

void MephDraw::drawArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->drawArcs(mephgraphicparam,n,0);
}

void MephDraw::fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode)
{
	this->mephdrawimp->fillPolygons(mephgraphicparam,n,shape,mode,0);
}

void MephDraw::fillRectangles(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->fillRectangles(mephgraphicparam,n,0);
}

void MephDraw::fillArcs(class MephGraphicParam * mephgraphicparam, int n)
{
	this->mephdrawimp->fillArcs(mephgraphicparam,n,0);
}
		
void MephDraw::drawPoints(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->drawPoints(mephgraphicparam,n,index);
}

void MephDraw::drawLines(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->drawLines(mephgraphicparam,n,index);
}

void MephDraw::drawRectangles(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->drawRectangles(mephgraphicparam,n,index);
}

void MephDraw::drawArcs(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->drawArcs(mephgraphicparam,n,index);
}

void MephDraw::fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode,int index)
{
	this->mephdrawimp->fillPolygons(mephgraphicparam,n,shape,mode,index);
}

void MephDraw::fillRectangles(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->fillRectangles(mephgraphicparam,n,index);
}

void MephDraw::fillArcs(class MephGraphicParam * mephgraphicparam, int n,int index)
{
	this->mephdrawimp->fillArcs(mephgraphicparam,n,index);
}
		
void MephDraw::setBackground(unsigned short red,unsigned short green,unsigned short blue)
{
	this->forecolor.setColor(red,green,blue);
	this->mephdrawimp->setBackground(0);
}

void MephDraw::setBackground(unsigned long colorindex)
{
	this->forecolor.setColor(colorindex);
	this->mephdrawimp->setBackground(0);
}

void MephDraw::setBackground(unsigned short red,unsigned short green,unsigned short blue,int index)
{
	this->forecolor.setColor(red,green,blue);
	this->mephdrawimp->setBackground(index);
}

void MephDraw::setBackground(unsigned long colorindex,int index)
{
	this->forecolor.setColor(colorindex);
	this->mephdrawimp->setBackground(index);
}

void MephDraw::setMode(char mode)
{
	this->mode=mode;
}

char MephDraw::getMode()
{
	return(mode);
}
		
void MephDraw::setAddFunction(int addfunction)
{
	this->addfunction=addfunction;
	this->mephdrawimp->setAddFunction();
}

int MephDraw::getAddFunction ()
{
	return(this->addfunction);
}
	

/*MephDraw::setImage(char *)
{
}

MephDraw::setMask(char *)
{
}*/
		
unsigned short MephDraw::getForeColorR()
{
	return(this->forecolor.getRed());
}

unsigned short MephDraw::getForeColorG()
{
	return(this->forecolor.getGreen());
}

unsigned short MephDraw::getForeColorB()
{
	return(this->forecolor.getBlue());
}

unsigned long MephDraw::getForeColorIndex()
{
	return(this->forecolor.getColorIndex());
}
	
void MephDraw::setForeColor(unsigned short red,unsigned short green,unsigned short blue)
{
	this->forecolor.setColor(red,green,blue);
	this->mephdrawimp->setForeColor();
}

void MephDraw::setForeColor(unsigned long colorindex)
{
	this->forecolor.setColor(colorindex);
	this->mephdrawimp->setForeColor();
}
	  
unsigned short MephDraw::getBackColorR()
{
	return(this->backcolor.getRed());
}

unsigned short MephDraw::getBackColorG()
{
	return(this->backcolor.getGreen());
}

unsigned short MephDraw::getBackColorB()
{
	return(this->backcolor.getBlue());
}

unsigned long MephDraw::getBackColorIndex()
{
	return(this->backcolor.getColorIndex());
}
	
void MephDraw::setBackColor(unsigned short red,unsigned short green,unsigned short blue)
{
	this->backcolor.setColor(red,green,blue);
	this->mephdrawimp->setBackColor();
}

void MephDraw::setBackColor(unsigned long colorindex)
{
	this->backcolor.setColor(colorindex);
	this->mephdrawimp->setBackColor();
}
