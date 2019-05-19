#ifndef MephImageImp_X11_h
#define MephImageImp_X11_h 1

#include "MephImageImp.h"
//#include "MephWindowImp.h"
#include "MephPanelImp.h"

#include <Imlib.h>
//#include <Imlib2.h>
#include <X11/extensions/shape.h>

class MephImageImp_X11 : public MephImageImp
{
  public:
      MephImageImp_X11();
      MephImageImp_X11(const class MephImage & mephimage,const class MephWindowImp_X11 & mephwindowimp_x11);
      MephImageImp_X11(const MephImageImp_X11 &right);
      ~MephImageImp_X11();
      const MephImageImp_X11 & operator=(const MephImageImp_X11 &right);
      int operator==(const MephImageImp_X11 &right) const;
      int operator!=(const MephImageImp_X11 &right) const;
	
	    void loadImage(int index);
	    void showImage(int indexImage,int indexWindow);
//	    void showImage();
			const char * getImageData();
			const char * getImageData(int index,char *result);
			void getShapeColor (int *red,int *green,int *blue);
			void getShapeColor (int *red,int *green,int *blue,int index,char *result);
      void shape (int indexImage,int indexWindow);
			void unshape (void);

	
	    void refresh(int index);
      void setAddFunction();
		  void setBackground(int indexImage,int indexWindow);
      void initValues(class MephImage const *mephimage,class MephVisObjImp const  * mephvisobjimp);

  private:
      map <int,ImlibImage *>image;
			
			map<int,ImlibData *>data;
      map <int,Pixmap> picture;
      map <int,Pixmap> mask;
			GC gc;
	    class MephVisObjImp *mephvisobjimp;
	    class MephImage *mephimage;
};

#endif
