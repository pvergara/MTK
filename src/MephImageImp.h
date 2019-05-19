#ifndef MephImageImp_h
#define MephImageImp_h 1

//#include "MephWindowImp.h"
#include "MephPanelImp.h"
#include <map.h>


class MephImageImp 
{

  public:
      MephImageImp();
      MephImageImp(const MephImageImp &right);
      ~MephImageImp();

      const MephImageImp & operator=(const MephImageImp &right);

      int operator==(const MephImageImp &right) const;

      int operator!=(const MephImageImp &right) const;


      virtual void setAddFunction(){};
		  virtual void setBackground(int indexImage,int indexWindow){};
			virtual void loadImage (int index){};
      virtual void showImage (int indexImage,int indexWindow){};
      virtual void shape (int indexImage,int indexWindow){};
//      virtual void showImage (){};
      virtual void hideImage (int index){};
      virtual void unloadImage (int index){};
				
			virtual const char * getImageData(){};
			virtual const char * getImageData(int index,char *result){};

			virtual void getShapeColor (int *red,int *green,int *blue){};
			virtual void getShapeColor (int *red,int *green,int *blue,int index,char *result){};
			virtual void refresh(int index){};
      virtual void initValues(class MephImage const *mephimage,class MephVisObjImp const *mephvisobjlimp){};
//      virtual void initValues(const class MephImage &mephimage,class MephAppImp const *mephappimp,const class MephVisObjImp &mephvisojimp){};

};
#endif
