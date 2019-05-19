#include "MephTextRaw.h"
#include <stdio.h>

MephTextRaw::MephTextRaw():bold(0),italic(0),twobyteschar(0),highlight(0),size(12),maxlength(256),x(1),y(1),linespace(5)
{
	sprintf(this->fontname,"%s","-*-helvetica-medium-r-*-*-12-*-*-*-*-*-*-*");
	this->text=new char [256];
	sprintf(this->text,"%s","");
  this->mephtextrawsingleton=this->mephtextrawsingleton->getMephTextRawSingleton();
  this->mephtextrawimp=this->mephtextrawsingleton->getMephTextRawImp();
}

void MephTextRaw::initValues (const class MephVisObjImp *mephvisobjimp)
{
	this->mephtextrawimp->initValues(this,mephvisobjimp);
	this->forecolor.initValues(mephvisobjimp);
	this->backcolor.initValues(mephvisobjimp);
	this->forecolor.setColor(0,0,0);
	this->mephtextrawimp->setForeColor();
	this->backcolor.setColor(0xFFFF,0xFFFF,0xFFFF);
	this->mephtextrawimp->setBackColor();
}
	
/*MÉTODOS ESPECÍFICOS*/
	
void MephTextRaw::show()
{
	this->mephtextrawimp->show();
}

//	  void hide();
	
/*MÉTODOS DE ATRIBUTOS*/
char *MephTextRaw::getFontName()
{
	return (this->fontname);
}

void MephTextRaw::putFontName(char fontname[256])
{
	sprintf (this->fontname,"%s",fontname);
}

char MephTextRaw::setFontName(char fontname[256])
{
	sprintf(this->fontname,"%s",fontname);
	return(this->mephtextrawimp->loadFont());
}

char MephTextRaw::getBold()
{
	return (this->bold);	
}

char MephTextRaw::setBold(char bold)
{
	char aux;

	aux=this->bold;
	this->bold=bold;
	
	if (this->mephtextrawimp->refreshFont())
	  return(1);
	else
	{
		this->bold=aux;
	  return(0);
	}
}

void MephTextRaw::putBold(char bold)
{
	this->bold=bold;
}

char MephTextRaw::getItalic()
{
	return (this->italic);
}

char MephTextRaw::setItalic(char italic)
{
	char aux;

	aux=this->italic;
	this->italic=italic;

	if (this->mephtextrawimp->refreshFont())
	  return(1);
	else
	{
  	this->italic=aux;
	  return(0);
	}
}

void MephTextRaw::putItalic(char italic)
{
	this->italic=italic;
}

void MephTextRaw::setTwoBytesChar(char twobyteschar)
{
	this->twobyteschar=twobyteschar;
}

char MephTextRaw::getTwoBytesChar()
{
	return(this->twobyteschar);
}

char MephTextRaw::getHighlight()
{
	return(this->highlight);
}

void MephTextRaw::setHighlight(int highlight)
{
	this->highlight=highlight;
}

char MephTextRaw::getSize()
{
	return(this->size);
}

/*DEVUELVE 0 SI NO HA PODIDO CAMBIAR EL TAMAÑO Y 1 SI SI HA PODIDO*/
char MephTextRaw::setSize(char size)
{
	char aux;
	aux=this->size;
	this->size=size;
	
	if(this->mephtextrawimp->refreshFont())
	  return(1);
	else
	{
		this->size=aux;
	 	return(0);
	}
}

void MephTextRaw::putSize(char size)
{
	this->size=size;
}
    
void MephTextRaw::setText(char *text)
{
	int i;
	if (this->text!=NULL)
		delete this->text;

  if (this->maxlength!=0)
  	if ((strlen(text)+1)>this->maxlength)
		{
			this->text=new char [maxlength];
  		for (i=0;i<maxlength;i++)
        this->text[i]='a';
      this->text[i]='\x0';
    	strncpy(this->text,text,maxlength-1);
			this->text[maxlength-1]='\x0';
		}
		else
		{
	    this->text=new char [strlen(text)+1];
  		for (i=0;i<strlen(text);i++)
        this->text[i]='a';
      this->text[i]='\x0';
    	sprintf(this->text,"%s",text);
		}
	else
	{
	  this->text=new char [strlen(text)+1];
		for (i=0;i<strlen(text);i++)
      this->text[i]='a';
    this->text[i]='\x0';
  	sprintf(this->text,"%s",text);
	}

	this->mephtextrawimp->setText();
}
	  
char *MephTextRaw::getText()
{
	return(this->text);
}

/*DEVUELVE 0 SI NO HA PODIDO CAMBIAR EL TAMAÑO Y 1 SI SI HA PODIDO*/
	  
char MephTextRaw::setMaxLength(unsigned long maxlength)
{
	char *aux;

	if (maxlength<0)
		return(0);
	else
	{
		aux=new char[strlen(this->text+1)];
		sprintf(aux,"%s",this->text);
		this->maxlength=maxlength;
		this->setText(aux);
		delete []aux;
		return(1);
	}
	
}
	  
char MephTextRaw::getMaxLength()
{
	return(this->maxlength);
}

/*POOOSIIICIIIOONNAAAMMMIIIEENNTOOO DEEEELL TEEEXXTOOO!!!!!*/
	  
void MephTextRaw::setX(int x)
{
	this->x=x;
}

int MephTextRaw::getX()
{
	return(this->x);
}
	  
void MephTextRaw::setY(int y)
{
	this->y=y;
}

int MephTextRaw::getY()
{
	return(this->y);
}
	 
void MephTextRaw::setWidth(unsigned int width)
{
	this->width=width;
}
	 
int MephTextRaw::getWidth()
{
	return(this->width);
}
	 
void MephTextRaw::setHeight(unsigned int height)
{
	this->height=height;
}
		
int MephTextRaw::getHeight()
{
	return(this->height);
}
/***********************************************************/
	
/*CCCCCCCCCOOOOOLLLLLLLOOOOORRRRRRR DEEEELL TEEEXXTOOO!!!!!*/
unsigned short MephTextRaw::getForeColorR()
{
	return(this->forecolor.getRed());
}

unsigned short MephTextRaw::getForeColorG()
{
	return(this->forecolor.getGreen());
}

unsigned short MephTextRaw::getForeColorB()
{
	return(this->forecolor.getBlue());
}

unsigned long MephTextRaw::getForeColorIndex()
{
	return(this->forecolor.getColorIndex());
}
	
void MephTextRaw::setForeColor(unsigned short red,unsigned short green,unsigned short blue)
{
	this->forecolor.setColor(red,green,blue);
	this->mephtextrawimp->setForeColor();
}

void MephTextRaw::setForeColor(unsigned long colorindex)
{
	this->forecolor.setColor(colorindex);
	this->mephtextrawimp->setForeColor();
}
	  
unsigned short MephTextRaw::getBackColorR()
{
	return(this->backcolor.getRed());
}

unsigned short MephTextRaw::getBackColorG()
{
	return(this->backcolor.getGreen());
}

unsigned short MephTextRaw::getBackColorB()
{
	return(this->backcolor.getBlue());
}

unsigned long MephTextRaw::getBackColorIndex()
{
	return(this->backcolor.getColorIndex());
}
	
void MephTextRaw::setBackColor(unsigned short red,unsigned short green,unsigned short blue)
{
	this->backcolor.setColor(red,green,blue);
	this->mephtextrawimp->setBackColor();
}

void MephTextRaw::setBackColor(unsigned long colorindex)
{
	this->backcolor.setColor(colorindex);
	this->mephtextrawimp->setBackColor();
}

/*char MephTextRaw::loadFont()
{
	this->mephtextrawimp->loadFont();
}*/

int MephTextRaw::getLineSpace()
{
	return(this->linespace);
}

void MephTextRaw::setLineSpace(int linespace)
{
	this->linespace=linespace;
}
