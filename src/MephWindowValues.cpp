#include "MephWindowValues.h"
	

MephWindowValues::MephWindowValues(Display const * const disp,Window const id)
{
  this->disp=disp;
	this->id=id;
}

MephWindowValues::MephWindowValues(Display const * const disp,Window const id,int width,int height)
{
  this->disp=disp;
	this->id=id;
	
	this->width=width;
	this->height=height;
}

Display * MephWindowValues::getDisplay() 
{
  return((Display *) this->disp);
}

Window MephWindowValues::getWindow()
{
  return (this->id);
}

int MephWindowValues::getWidth()
{
  return (this->width);
}

int MephWindowValues::getHeight()
{
  return (this->height);
}

void MephWindowValues::setWidth(int width)
{
  this->width=width;
}

void MephWindowValues::setHeight(int height)
{
	this->height=height;
}