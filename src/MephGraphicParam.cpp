#include "MephGraphicParam.h"

MephGraphicParam::MephGraphicParam():x(0),y(0),width(0),height(0),x2(0),y2(0),ang(0),ang2(0)
{
}
	
void MephGraphicParam::setX(short x)
{
	this->x=x;
}
	  
void MephGraphicParam::setY(short y)
{
	this->y=y;
}

void MephGraphicParam::setX2(short x2)
{
		this->x2=x2;
}
	  
void MephGraphicParam::setY2(short y2)
{
		this->y2=y2;
}
	  
void MephGraphicParam::setAng(short ang)
{
		this->ang=ang;
}
	  
void MephGraphicParam::setAng2(short ang2)
{
		this->ang2=ang2;
}
	
void MephGraphicParam::setWidth(unsigned short width)
{
		this->width=width;
}
		
void MephGraphicParam::setHeight(unsigned short height)
{	
	this->height=height;
}
		
void MephGraphicParam::setPoint(short x,short y)
{
	this->x=x;
	this->y=y;
}
		
void MephGraphicParam::setLine (short x,short y,short x2,short y2)
{
	this->x=x;
	this->y=y;
	this->x2=x2;
	this->y2=y2;
}
		
void MephGraphicParam::setRectangle(short x,short y,unsigned short width,unsigned short height)
{
	this->x=x;
	this->y=y;
	this->width=width;
	this->height=height;
}

void MephGraphicParam::setArc(short x,short y,unsigned short width ,unsigned short height,short ang,short ang2)
{
	this->x=x;
	this->y=y;
	this->width=width;
	this->height=height;
	this->ang=ang;
	this->ang2=ang2;
}
		
short MephGraphicParam::getX()
{
	return (this->x);
}
		
short MephGraphicParam::getY()
{
	return (this->y);
}
		
short MephGraphicParam::getX2()
{
	return (this->x2);
}
		
short MephGraphicParam::getY2()
{
	return (this->y2);
}
		
short MephGraphicParam::getAng()
{
	return (this->ang);
}
		
short MephGraphicParam::getAng2()
{
	return (this->ang2);
}
		
unsigned short MephGraphicParam::getWidth()
{
	return (this->width);
}
		
unsigned short MephGraphicParam::getHeight()
{
	return (this->height);
}
