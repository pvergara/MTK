#include "MephTextRawImp_X11.h"
#include "MephTextRaw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MephTextRawImp_X11::initValues (const class MephTextRaw *mephtextraw,const class MephVisObjImp *mephvisobjimp)
{
	this->mephtextraw=(class MephTextRaw *)mephtextraw;
	this->mephvisobjimp=(class MephVisObjImp *)mephvisobjimp;
	
  if (this->mephvisobjimp->getId()!=0)
	  this->gc=XCreateGC((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),0,NULL);
	else
	  this->gc=XCreateGC((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),0,NULL);
	
	this->loadFont();
}

void MephTextRawImp_X11::show()
{
	int i,j;
	char *text;
	char *aux;
	int y,linespace=this->mephtextraw->getLineSpace();
	Display *disp=(Display *)this->mephvisobjimp->getDisplay();
	
	text=new char [strlen(this->mephtextraw->getText())+1];
	sprintf(text,"%s",this->mephtextraw->getText());
	
	if (this->mephtextraw->getTwoBytesChar())/*TEXTO...RARRIIITOOO*/
	{
    for ( i=0; i < strlen( text ) / 2; i++ )
	  {
      this->xchar2b[i].byte1 = text[ i*2     ];
      this->xchar2b[i].byte2 = text[ i*2 + 1 ];
    }

		if (this->mephtextraw->getHighlight())//CON RESALTADO
			if (this->mephvisobjimp->getId())//PARA PANELES
			  XDrawImageString16((Display *)disp,this->mephvisobjimp->getId(),this->gc,this->mephtextraw->getX(),this->mephtextraw->getY(),this->xchar2b,strlen(text)/2);
  		else//PARA LOS DEMÁS MEPHVISOJB'S
			  XDrawImageString16((Display *)disp,this->mephvisobjimp->getWindow(),this->gc,this->mephtextraw->getX(),this->mephtextraw->getY(),this->xchar2b,strlen(text)/2);
		else//SIN RESALTADO
			if (this->mephvisobjimp->getId())//PARA PANELES
			  XDrawString16((Display *)disp,this->mephvisobjimp->getId(),this->gc,this->mephtextraw->getX(),this->mephtextraw->getY(),this->xchar2b,strlen(text)/2);
			else//PARA LOS DEMÁS MEPHVISOBJ'S
			  XDrawString16((Display *)disp,this->mephvisobjimp->getWindow(),this->gc,this->mephtextraw->getX(),this->mephtextraw->getY(),this->xchar2b,strlen(text)/2);
			
	}
	else/*TEXTO NORRMAALIIITOOO*/
	{
		y=this->mephtextraw->getY()+linespace;
		aux=new char [strlen(text)];
		j=0;
		for (i=0;i<strlen(text);i++)
		{
			aux[j]=text[i];
			if ((text[i+1]=='\n') || (text[i+1]=='\x0'))
			{
				aux[j+1]='\x0';
				i++;
    		if (this->mephtextraw->getHighlight())//CON RESALTADO
		    	if (this->mephvisobjimp->getId())//PARA PANELES
			      XDrawImageString(disp,this->mephvisobjimp->getId(),this->gc,this->mephtextraw->getX(),y,aux,strlen(aux));
    			else//PARA LOS DEMÁS MEPHVISOBJ'S
		    	  XDrawImageString(disp,this->mephvisobjimp->getWindow(),this->gc,this->mephtextraw->getX(),y,aux,strlen(aux));
    		else//SIN RESALTADO
		    	if (this->mephvisobjimp->getId())//PARA PANELES
    			  XDrawString(disp,this->mephvisobjimp->getId(),this->gc,this->mephtextraw->getX(),y,aux,strlen(aux));
		    	else//SIN RESALTADO
			      XDrawString(disp,this->mephvisobjimp->getWindow(),this->gc,this->mephtextraw->getX(),y,aux,strlen(aux));
				y+=(((xfontstruct->ascent)-(xfontstruct->descent))+linespace);
				j=0;
			}
			else
  			j++;
		}
		delete []aux;
	}
	delete[] text;
	XFlush(disp);
}

void MephTextRawImp_X11::setBackColor()
{
	XSetBackground((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mephtextraw->getBackColorIndex());
}

void MephTextRawImp_X11::setForeColor()
{
	XSetForeground((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mephtextraw->getForeColorIndex());
}

char MephTextRawImp_X11::refreshFont()
{
	char fontname[256],aux[256],aux2[5];
	int i,j;
	char fieldcount=1;
	
  sprintf(fontname,"%s",this->mephtextraw->getFontName());
	
	for (i=1;i<strlen(fontname);i++)
	{
		if (fontname[i]=='-')
			fieldcount++;

		if (fieldcount==3)
		{
			i++;
			strncpy(aux,fontname,i);
			aux[i]='\x0';
			for (;fieldcount==3;i++)
			{
   			if (fontname[i]=='-')
	    		fieldcount++;
			}
			i--;
			if (this->mephtextraw->getBold())
				strcat(aux,"bold");
			else
				strcat(aux,"medium");
			
			strcat(aux,&(fontname[i]));
			strcpy(fontname,aux);
			fontname[strlen(aux)]='\x0';
/*			printf("fontname: %s\n",fontname);
			fflush(stdout);
			getchar();		*/
			fieldcount=1;
			for (i=1;fieldcount<=4;i++)
  	  	if (fontname[i]=='-')
	  	  	fieldcount++;
		}

		if (fieldcount==4)
		{
			strncpy(aux,fontname,i);
			aux[i]='\x0';
			i++;
			for (;fieldcount==4;i++)
			{
   			if (fontname[i]=='-')
	    		fieldcount++;
			}
			i--;
			
			if (this->mephtextraw->getItalic())
				strcat(aux,"o");
			else
				strcat(aux,"r");

			strcat(aux,&(fontname[i-1]));
			strcpy(fontname,aux);
			fontname[strlen(aux)]='\x0';
/*			printf("fontname: %s\n",fontname);
			fflush(stdout);
			getchar();		*/
			fieldcount=1;
			for (i=1;fieldcount<7;i++)
  	  	if (fontname[i]=='-')
	  	  	fieldcount++;
		}
		
		if (fieldcount==7)
		{
			i++;
			strncpy(aux,fontname,i);
			aux[i]='\x0';
			j=i+1;
			for (;fieldcount==7;i++)
			{
   			if (fontname[i]=='-')
	    		fieldcount++;
			}
			i--;
			if (!this->mephtextraw->getSize())
				strcat(aux,"*");
			else
			{
				sprintf(aux2,"%d",this->mephtextraw->getSize());
				strcat(aux,aux2);
			}

			strcat(aux,&(fontname[i]));
			strcpy(fontname,aux);
			fontname[strlen(aux)]='\x0';
/*			printf("fontname: %s\n",fontname);
			fflush(stdout);
			getchar();		*/
		}
	}
  
	return (this->setFont(fontname));
}

char MephTextRawImp_X11::setFont(char *fontname)
{
	
	if ((this->xfontstruct=XLoadQueryFont((Display *)this->mephvisobjimp->getDisplay(),fontname))==NULL)
	{
		printf ("Badfont error\n");
		fflush(stdout);
		return(0);
	}
	else
	{
		this->mephtextraw->putFontName(fontname);
		/*CON ÉSTA LINEA SE PRETENDE QUE, CADA VEZ QUE SE CAMBIE ALGUNA DE LAS CARACTERÍSTICAS DEL TIPO DE LETRA, CAMBIE (COMO ES 
		NATURAL), TAMBIÉN EL ANCHO Y ALTO DEL TEXTO*/
		this->setText();
		XSetFont((Display *)this->mephvisobjimp->getDisplay(),this->gc,this->xfontstruct->fid);
		return(1);
	}
}

char MephTextRawImp_X11::loadFont()
{
	char fontname[256],aux[256];
	int i,j;
	char fieldcount;
	
  sprintf(fontname,"%s",this->mephtextraw->getFontName());
	
	fieldcount=1;
	if (fontname[0]=='-') /*NOMBRE DE FUENTE COMPLETO...O POR LO MENOS ESO ESPERO....*/
	{
  	/*AQUÍ HAY UN PROBLEMA DE CONCEPTO... VAMOS A VER, EL USUARIO PUEDE QUERE ESCRIBIR EL NOMBRE COMPLETO DE LA FUENTE....ALGO
	  QUE ES UN COÑAZO PERO... HAY GENTE MUUUYY RAAARAA... BUENO EL ASUNTO ES QUE SI QUIERE ESCRIBIR ESE NOMBRE COMPLETO, DENTRO
		DE ÉL NOS ENCONTRAREMOS CON CARACTERÍSTICAS TAN CURIOSAS COMO NEGRITA SI O NO... CURSIVA SI O NO... Y EL TAMAÑO... ESTAS
		TRES CARACTERÍSTICAS HAN DE QUEDAR REGISTRADAS EN EL MODELO DEL PAQUETE MEPHTEXTRAW...QUE EN ESTE CASO EL LA CLASE MEPHTEXTRAW
		PEEEEROOO AHORA LLEGA LA MISMA PERSONA QUE, DESPUEÉS DE ESCIBIR EL NOMBRE LARGO DE LA FUENTE, QUIERE CAMBIAR ALGÚN PARAMENTRO
		DE LOS TRES ANTES MENCIONADOS*/
		for (i=1;i<strlen(fontname);i++)
		{
			if (fontname[i]=='-')
				fieldcount++;

			if (fieldcount==3)
			{
				i++;
				j=0;
				for (;fieldcount==3;i++,j++)
				{
					aux[j]=fontname[i];
    			if (fontname[i]=='-')
		    		fieldcount++;
				}
				aux[j-1]='\x0';
				i--;
				if (strcmp(aux,"bold")==0) /*Si está determinado que se vea en negrita*/
					this->mephtextraw->putBold(1);
				else
					this->mephtextraw->putBold(0);
			}

			if (fieldcount==4)
			{
				i++;
				j=0;
				for (;fieldcount==4;i++,j++)
				{
					aux[j]=fontname[i];
    			if (fontname[i]=='-')
		    		fieldcount++;
				}
				aux[j-1]='\x0';
				i--;
				if (strcmp(aux,"o")==0) /*Si está determinado que se vea en cursiva*/
					this->mephtextraw->putItalic(1);
				else
					this->mephtextraw->putItalic(0);
			}

			if (fieldcount==7)
			{
				i++;
				j=0;
				for (;fieldcount==7;i++,j++)
				{
					aux[j]=fontname[i];
    			if (fontname[i]=='-')
		    		fieldcount++;
				}
				aux[j-1]='\x0';
				i--;
				if (strcmp(aux,"*")==0) /*Si está determinado el tamaño*/
					this->mephtextraw->putSize(0);
				else
				{
					j=atoi(aux);
					this->mephtextraw->putSize(j);
				}
			}
		}
	}
	else
	{
		sprintf(fontname,"%s",this->mephtextraw->getFontName());

		sprintf(aux,"%s",fontname);
		sprintf(fontname,"%s","-*-");
		
		strcat(fontname,aux);
		
		if (!this->mephtextraw->getBold())
			strcat(fontname,"-medium-");
		else
			strcat(fontname,"-bold-");
		
		if (!this->mephtextraw->getItalic())
			strcat(fontname,"r-");
		else
			strcat(fontname,"o-");
		
		strcat(fontname,"*-*-");
		
		if (this->mephtextraw->getSize()==0)
			strcat(fontname,"*-*-*-*-*-*-*-*");
		else
		{
			sprintf(aux,"%d",this->mephtextraw->getSize());
			strcat(fontname,aux);
			strcat(fontname,"-*-*-*-*-*-*-*");
		}
	}
	return(this->setFont(fontname));
}

void MephTextRawImp_X11::setText()
{
	int i,j;
	int count;
	int maxwidth=0;
	int width;
	char *text;
	char *aux;
	
	text=new char [strlen(this->mephtextraw->getText())];
	sprintf(text,"%s",this->mephtextraw->getText());
	
	if (this->mephtextraw->getTwoBytesChar())
	{
    for ( i=0; i < strlen( text ) / 2; i++ )
	  {
      this->xchar2b[i].byte1 = text[ i*2     ];
      this->xchar2b[i].byte2 = text[ i*2 + 1 ];
    }
		
		/*MEJOR NO FIARSE MUCHO DE ESTE ANCHO PERO...¿ALGUIEN ME PUEDE DECIR COMO CARAJO SE HACE UN RETORNO DE CARRO EN CHINO?*/
		this->mephtextraw->setWidth(XTextWidth16(this->xfontstruct,xchar2b,strlen( text ) / 2)); 
		this->mephtextraw->setHeight((this->xfontstruct->ascent)-(this->xfontstruct->descent));
	}
	else
	{
		aux=new char [strlen(text)];
		count=0;
		j=0;
		for (i=0;i<strlen(text);i++)
		{
			aux[j]=text[i];
			if ((text[i+1]=='\n') || (text[i+1]=='\x0'))
			{
				i+=2;
				aux[j]='\x0';
				width=XTextWidth(this->xfontstruct,aux,strlen(aux)+1);
				if (maxwidth<width)
					maxwidth=width;
				j=0;
				count++;
			}
			else
  			j++;
		}
		
		this->mephtextraw->setWidth(maxwidth);
		this->mephtextraw->setHeight((((this->xfontstruct->ascent)-(this->xfontstruct->descent))*(count+1))+(this->mephtextraw->getLineSpace()*(count-1)));
		delete aux;
	}
	delete text;
}
