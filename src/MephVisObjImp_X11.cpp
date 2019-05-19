#include "MephVisObjImp_X11.h"

MephVisObjImp_X11::MephVisObjImp_X11():mephappimp(NULL)
{
}

MephVisObjImp_X11::MephVisObjImp_X11(const MephVisObjImp_X11 &right)
{
}


MephVisObjImp_X11::~MephVisObjImp_X11()
{
}


const MephVisObjImp_X11 & MephVisObjImp_X11::operator=(const MephVisObjImp_X11 &right)
{
}


int MephVisObjImp_X11::operator==(const MephVisObjImp_X11 &right) const
{
}

int MephVisObjImp_X11::operator!=(const MephVisObjImp_X11 &right) const
{
}

int MephVisObjImp_X11::getScreen ()
{
	if (this->mephappimp!=NULL)
    return (this->mephappimp->getScreen());
}

int MephVisObjImp_X11::getNScreen ()
{
	if (this->mephappimp!=NULL)
    return (this->mephappimp->getNscreen());
}

const Display *MephVisObjImp_X11::getDisplay()
{
	if (this->mephappimp!=NULL)
    return ((Display *) this->mephappimp->getDisplay());
}

Window MephVisObjImp_X11::getRootWindow() 
{
	if (this->mephappimp!=NULL)
    return (this->mephappimp->getRootWindow());
}

/*GC MephVisObjImp_X11::getGC()
{
	return(this->gc);
}
/*void MephVisObjImp_X11::initValues(int x,int y,int width,int height)
{
  parent=MephAppImpX11_getRootWindow();
  if ( (MephVisObjImp_X11::id=XCreateSimpleWindow(MephAppImpX11_getDisplay(),parent,x,y,width,height,0,0,0))==0 )
  {
    cerr << "Could not create window";
    exit(-1);
  }
}*/
