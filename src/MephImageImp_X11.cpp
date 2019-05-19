#include <stdio.h>
#include "MephImageImp_X11.h"
#include "MephImage.h"

MephImageImp_X11::MephImageImp_X11()
{
}

MephImageImp_X11::MephImageImp_X11(const MephImageImp_X11 &right)
{
}


MephImageImp_X11::~MephImageImp_X11()
{
	this->image.clear();
	this->data.clear();
	delete this->mephvisobjimp;
	delete this->mephimage;
}


const MephImageImp_X11 & MephImageImp_X11::operator=(const MephImageImp_X11 &right)
{
}


int MephImageImp_X11::operator==(const MephImageImp_X11 &right) const
{
}

int MephImageImp_X11::operator!=(const MephImageImp_X11 &right) const
{
}

void MephImageImp_X11::initValues(class MephImage const * mephimage,class MephVisObjImp const * mephvisobjimp)
{
	this->mephimage=(class MephImage *) mephimage;
	this->mephvisobjimp=(class MephVisObjImp *) mephvisobjimp;

}

/*index=> INDICE DE LA IMAGEN QUE SE CARGARµ*/
void MephImageImp_X11::loadImage(int index)
{
	char e;
	this->data[index]=Imlib_init ((Display *) this->mephvisobjimp->getDisplay());
	
  if (this->mephvisobjimp->getId()!=0)
  	this->gc=XCreateGC((Display *) this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getId(),0,NULL);
  else
  	this->gc=XCreateGC((Display *) this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),0,NULL);

	if ((this->image[index]=Imlib_load_image(this->data[index],(char *) this->mephimage->getImagePath(index,&e)))!=NULL)
  {
    this->mephimage->setWidth(this->image[index]->rgb_width);
    this->mephimage->setHeight(this->image[index]->rgb_height);
	  this->refresh(index);
  }
	
}

void MephImageImp_X11::setAddFunction()
{
	XSetFunction((Display *) this->mephvisobjimp->getDisplay(),this->gc,this->mephimage->getAddFunction());
}

/*index=> INDICE DE LA IMAGEN A LA QUE SE LE MODIFICARµN EL ANCHO Y EL ALTO*/
void MephImageImp_X11::refresh(int index)
{
  char e;
  Imlib_render(this->data[index],this->image[index],this->mephimage->getWidth(index,&e),this->mephimage->getHeight(index,&e));
  this->picture[index]=Imlib_copy_image(this->data[index],this->image[index]);
  this->mask[index]=Imlib_copy_mask(this->data[index],this->image[index]);
}

/*void MephImageImp_X11::showImage()
{
  this->showImage(0,0);
}*/

void MephImageImp_X11::showImage(int indexImage,int indexWindow)
{
  char e;
	if (this->image[indexImage]!=NULL)
	{
	  if (this->mask[indexImage])
		{
      XSetClipMask( (Display *)this->mephvisobjimp->getDisplay(),this->gc,this->mask[indexImage]);
      XSetClipOrigin( (Display *)this->mephvisobjimp->getDisplay(),this->gc, 0, 0 );
	  }		

    if (this->mephvisobjimp->getId(indexWindow,&e)!=0)
		  XCopyArea((Display *)this->mephvisobjimp->getDisplay(),this->picture[indexImage],this->mephvisobjimp->getId(indexWindow,&e),this->gc,0,0,this->mephimage->getWidth(indexImage,&e),this->mephimage->getHeight(indexImage,&e),0,0);
    else
		{
			if (this->mephimage->getImageMode(indexImage,&e))
			{
		    XSetWindowBackgroundPixmap((Display *) this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(indexWindow,&e),this->picture[indexImage]);
    	  XClearWindow((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(indexWindow,&e));
			}
			else
  	  	XCopyArea((Display *)this->mephvisobjimp->getDisplay(),this->picture[indexImage],this->mephvisobjimp->getWindow(indexWindow,&e),this->gc,0,0,this->mephimage->getWidth(indexImage,&e),this->mephimage->getHeight(indexImage,&e),0,0);
		}

    XSetClipMask( (Display *)this->mephvisobjimp->getDisplay(),this->gc , None );
	}
	XFlush((Display *)this->mephvisobjimp->getDisplay());
}

const char * MephImageImp_X11::getImageData()
{
	if (this->image[0])
		return ((const char *) this->image[0]->rgb_data);
}

const char * MephImageImp_X11::getImageData(int index,char *result)
{
	if (this->image[index])
	{
		result[0]=1;
		return ((const char *) this->image[index]->rgb_data);
	}
	else
	{
		result[0]=0;
		return ((const char *) NULL);
	}
}


void MephImageImp_X11::getShapeColor (int *red,int *green,int *blue)
{
	char result;
	this->getShapeColor(red,green,blue,0,&result);
}

void MephImageImp_X11::getShapeColor (int *red,int *green,int *blue,int index,char *result)
{
	ImlibColor color;
	
	if (this->image[index])
	{
		Imlib_get_image_shape(this->data[index],this->image[index],&color);
		red[0]=color.r;
		green[0]=color.g;
		blue[0]=color.b;
		result[0]=1;
	}
	else
	{
		result[0]=0;
	}
}

void MephImageImp_X11::setBackground(int indexImage,int indexWindow)
{
	this->refresh(indexImage);
	this->showImage(indexImage,indexWindow);
}

void MephImageImp_X11::shape (int indexImage,int indexWindow)
{
	this->mephimage->setWidth(this->mephvisobjimp->getWidth(),indexImage);
	this->mephimage->setHeight(this->mephvisobjimp->getHeight(),indexImage);
	this->refresh(indexImage);
	this->showImage(indexImage,indexWindow);
//	XSetWindowBackgroundPixmap((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(), this->picture[indexImage]);
  if (this->mask[indexImage])
    XShapeCombineMask((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),ShapeBounding, 0, 0, this->mask[indexImage], ShapeSet);
}

void MephImageImp_X11::unshape (void)
{
  XShapeCombineMask((Display *)this->mephvisobjimp->getDisplay(),this->mephvisobjimp->getWindow(),ShapeBounding, 0, 0,None, ShapeSet);
}