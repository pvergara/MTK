#include "MephColor.h"

MephColor::MephColor():red(58000),green(58000),blue(58000)
{
  this->mephcolorsingleton=this->mephcolorsingleton->getMephColorSingleton();
  this->mephcolorimp=this->mephcolorsingleton->getMephColorImp();
}

void MephColor::initValues(class MephVisObjImp const * mephvisobjimp)
{
	this->mephcolorimp->initValues(mephvisobjimp);
	this->colorindex=this->mephcolorimp->getColorIndex(this->red,this->green,this->blue);
}

MephColor::~MephColor()
{
  delete this->mephcolorimp;
//	delete this->mephcolorsingleton;
}

unsigned short MephColor::getRed()
{
  return (this->mephcolorimp->getRed(this->colorindex));
}

unsigned short MephColor::getGreen()
{
  return (this->mephcolorimp->getGreen(this->colorindex));
}

unsigned short MephColor::getBlue()
{
  return (this->mephcolorimp->getBlue(this->colorindex));
}

unsigned long MephColor::getColorIndex()
{
  return (this->mephcolorimp->getColorIndex(this->red,this->green,this->blue));
}

void MephColor::setColor(unsigned short red,unsigned short green,unsigned short blue)
{
  this->red=red;
  this->green=green;
  this->blue=blue;
	
	this->colorindex=this->mephcolorimp->getColorIndex(this->red,this->green,this->blue);
}

void MephColor::setColor(unsigned long colorindex)
{
  this->colorindex=colorindex;
	
	this->red=this->mephcolorimp->getRed(colorindex);
	this->green=this->mephcolorimp->getGreen(colorindex);
	this->blue=this->mephcolorimp->getBlue(colorindex);
}