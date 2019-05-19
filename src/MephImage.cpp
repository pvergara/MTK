#include <iostream.h>
#include <alloc.h>
#include <stdio.h>
#include "MephImage.h"

MephImage::MephImage()
{
  this->mephimagesingleton=this->mephimagesingleton->getMephImageSingleton();
  this->mephimageimp=this->mephimagesingleton->getMephImageImp();
}


MephImage::MephImage(const MephImage &right)
{
}


MephImage::~MephImage()
{
//  delete this->imagepath;
  delete this->mephimageimp;
  delete this->mephimagesingleton;
}


const MephImage & MephImage::operator=(const MephImage &right)
{
}


int MephImage::operator==(const MephImage &right) const
{
}

int MephImage::operator!=(const MephImage &right) const
{
}

void MephImage::loadImage (char *path)
{
  this->loadImage(path,0);
}

/*index=>indice de la imagen*/
void MephImage::loadImage (char *path,int index)
{
  char load=1;
  
	if (this->imagepath[index]==NULL)
		this->imagepath[index]=new char[strlen(path)+1];
	else
	{
		/*SERÍA ESTéPIDO CARGAR UNA IMAGEN QUE YA EXISTE...VAMOS DIGO YO.AUNQUE UNA ACTUAL REFLEXIÓN ME HACE RECAPACITAR SOBRE ESTO
		PUES QUIZµS LO QUE DEBAN EVITAR RECARGAR LA IMAGEN NO SEA EL MISMO MEPHIMAGE SINO LO QUE LA LLAMAN ¿PORQUE? PUES MUY FACIL
		EN TIEMPO DE EJECUCIÓN DEL TOOLKIT (IDEA RETORCIDA PERO POSIBLE) SE PUEDE MODIFICAR LA MISMA IMAGEN QUE SE QUIERE RECARGAR
		PARA VOLVER A VER EL RESULTADO DE DICHA MODIFICACIÓN, AHORA PARA QUE ESTO OCURRA HABRÍA QUE "CARGAR" CUALQUIER COSA Y DESPUS
		VOLVER A CARGAR LO ANTERIOR, POR AHORA, HASTA QUE SE ME OCURRA QUIEN GANA EL DEBATE... SE QUEDA COMO LO ACABO DE DEJAR*/
		if (!strcmp(this->imagepath[index],path))
		{
			load=0;
		}
		else
		{
  		if (strlen(this->imagepath[index])<=strlen(path))
	  	{
		  	delete [] this->imagepath[index];
  			this->imagepath[index]=new char[strlen(path)+1];
	  	}
		}
	}
  
	if (load)
	{
  	sprintf(this->imagepath[index],"%s",path);
	  mephimageimp->loadImage(index);
	}
}



void MephImage::showImage ()
{
  this->showImage(0,0);
}

void MephImage::showImage (int indexImage, int indexWindow)
{
  mephimageimp->showImage(indexImage,indexWindow);
}


void MephImage::hideImage ()
{
//	this->visible=0;
}

void MephImage::unloadImage ()
{
}

void MephImage::initValues(class MephVisObjImp const * mephvisobjimp)
{
  this->mephimageimp->initValues(this,mephvisobjimp);
}

int MephImage::getAddFunction()
{
	return (this->addfunction);
}

void MephImage::setAddFunction(int addfunction)
{
	this->addfunction=addfunction;
	this->mephimageimp->setAddFunction();
}

const char * MephImage::getImagePath()
{
  return (this->imagepath[0]);
}

const char * MephImage::getImagePath(int index,char *result)
{
  if (this->imagepath[index])
  {
    result[0]=1;
    return (this->imagepath[index]);
  }
  else
  {
    result[0]=0;
    return(NULL);
  }
}

map <int,char *> MephImage::getImagePaths()
{
  return (this->imagepath);
}


int MephImage::getX()
{
  return (this->x);
}

int MephImage::getY()
{
  return (this->y);
}

unsigned int MephImage::getWidth()
{
  return (this->width[0]);
}

unsigned int MephImage::getWidth(int index,char *result)
{
  if (this->width[index])
  {
    result[0]=1;
    return (this->width[index]);
  }
  else
  {
    result[0]=0;
    return(NULL);
  }
}

map <int,int> MephImage::getWidths()
{
  return (this->width);
}

void MephImage::setWidth(int width)
{
  this->setWidth(width,0);
}

void MephImage::setWidth(int width,int index)
{
  this->width[index]=width;
}

unsigned int MephImage::getHeight()
{
  return (this->height[0]);
}

unsigned int MephImage::getHeight(int index,char * result)
{
  if (this->height[index])
  {
    result[0]=1;
    return (this->height[index]);
  }
  else
  {
    result[0]=0;
    return (NULL);
  }
}

map <int,int> MephImage::getHeights()
{
  return (this->height);
}

void MephImage::setHeight(int height)
{
  this->setHeight(height,0);
}

void MephImage::setHeight(int height,int index)
{
  this->height[index]=height;
}

int MephImage::getScaleWidth()
{
  return (this->scalewidth);
}

int MephImage::getScaleHeight()
{
  return (this->scaleheight);
}


const char * MephImage::getImageData()
{
  char result;
  return(this->getImageData(0,&result));
}

const char * MephImage::getImageData(int index,char *result)
{
	if (this->mephimageimp)
	  return (this->mephimageimp->getImageData(index,result));
	else	
	{
		result[0]=0;
		return(NULL);
	}
}

void MephImage::getShapeColor (int *red,int *green,int *blue)
{
  char result;
	return(this->mephimageimp->getShapeColor(red,green,blue,0,&result));
}

void MephImage::getShapeColor (int *red,int *green,int *blue,int index,char *result)
{
	if (this->mephimageimp)
    this->mephimageimp->getShapeColor(red,green,blue,index,result);
  else
    result[0]=0;
}


/*char MephImage::getVisible()
{
	return (this->visible);
}*/

/*void MephImage::setVisible(char visible)
{
	this->visible=visible;
}*/

void MephImage::setBackground(char * image,unsigned int width,unsigned int height, unsigned char imagemode)
{
  this->setBackground(image,width,height,imagemode,0,0);
}

/*index=> LA VENTANA EN LA QUE SE CARGARµ LA IMAGEN!!!!*/
void MephImage::setBackground(char * image,unsigned int width,unsigned int height, unsigned char imagemode,int indexImage,int indexWindow)
{
  this->imagemode[indexWindow]=imagemode;

  this->loadImage(image,indexImage);
	if (!(imagemode & MEPHIMAGED))
	{
		this->width[indexImage]=width;
		this->height[indexImage]=height;
		this->mephimageimp->refresh(indexImage);
	}
  this->mephimageimp->setBackground(indexImage,indexWindow);
}

unsigned char MephImage::getImageMode()
{
  char result;
	return (this->getImageMode(0,&result));
}

unsigned char MephImage::getImageMode(int index,char *result)
{
  if (this->imagemode[index])
  {
      result[0]=1;
	return (this->imagemode[index]);
  }
  else
  {
      result[0]=0;
	return (NULL);
  }

}

map <int,unsigned char> MephImage::getImageModes()
{
	return (this->imagemode);
}


void MephImage::refresh(void)
{
	this->mephimageimp->refresh(0);
}

void MephImage::refresh(int index)
{
	this->mephimageimp->refresh(index);
}

void MephImage::shape(char *path)
{
  this->shape(path,0,0);
}

void MephImage::shape(char *path,int indexImage,int indexWindow)
{
	if (this->mephimageimp)
	{
    this->loadImage(path,indexImage);
    this->mephimageimp->shape(indexImage,indexWindow);
	}
}

void MephImage::unshape (void)
{
	if (this->mephimageimp)
    this->mephimageimp->unshape();	
}
