#include "MephColorImp_X11.h"

void MephColorImp_X11::initValues(class MephVisObjImp const * mephvisobjimp)
{
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;
}

MephColorImp_X11::~MephColorImp_X11()
{
	delete mephvisobjimp;
}

unsigned short MephColorImp_X11::getRed(unsigned long colorindex)
{
  Display *disp=(Display *) this->mephvisobjimp->getDisplay();
	this->color.pixel=colorindex;
	XQueryColor(disp,DefaultColormap(disp,DefaultScreen(disp)),&color);
	return (this->color.red);
}

unsigned short MephColorImp_X11::getGreen(unsigned long colorindex)
{
  Display *disp=(Display *)this->mephvisobjimp->getDisplay();
	this->color.pixel=colorindex;
	XQueryColor(disp,DefaultColormap(disp,DefaultScreen(disp)),&color);
	return (this->color.green);
}

unsigned short MephColorImp_X11::getBlue(unsigned long colorindex)
{
  Display *disp=(Display *)this->mephvisobjimp->getDisplay();
	this->color.pixel=colorindex;
	XQueryColor(disp,DefaultColormap(disp,DefaultScreen(disp)),&color);
	return (this->color.blue);
}

unsigned long MephColorImp_X11::getColorIndex(unsigned short red,unsigned short green,unsigned short blue)
{
  Display *disp=(Display *)this->mephvisobjimp->getDisplay();
	this->color.red=red;
	this->color.green=green;
	this->color.blue=blue;
	XAllocColor(disp,DefaultColormap(disp,DefaultScreen(disp)),&color);

	return (this->color.pixel);
}
	
/*Display * MephColorImp_X11::MephAppImpX11_getDisplay ()
{
  return (MephAppImp_X11::disp);
}*/
