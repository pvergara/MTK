#ifndef MephImage_h
#define MephImage_h 1

#include "MephImageSingleton.h"
#include "MephImageImp.h"

#include "MephPanelImp.h"
#include "MephWindowImp.h"
#include "MephApp.h"
#include "MephGen.h"

#define MEPHSOLID 0x0
#define MEPHIMAGE 0x1 << 1L

class MephImage 
{
  public:
      MephImage();

      MephImage(const MephImage &right);

      ~MephImage();

      const MephImage & operator=(const MephImage &right);

      int operator==(const MephImage &right) const;

      int operator!=(const MephImage &right) const;

      void initValues(class MephVisObjImp const * mephvisobjimp);
//      void initValues(const class MephWindowImp & mephwindowimp);
//      void initValues(const class MephVisObjImp & mephvisobjimp,class MephApp const *mephapp);

      void loadImage (char *path);
      void loadImage (char *path,int index);
      void showImage ();
      void showImage (int indexImage,int indexWindow);
      void hideImage ();
      void unloadImage ();

      void shape(char *path);
      void shape(char *path,int indexImage,int indexWindow);

			void refresh(void);
			void refresh(int index);
			
			const char * getImagePath();
			const char * getImagePath(int index,char *result);
			map <int,char *> getImagePaths();

			const char * getImageData();
			const char * getImageData(int index,char *result);
			int getX();
			int getY();

			int getAddFunction();
			void setAddFunction(int addfunction);
			void setBackground(char * image,unsigned int width,unsigned int height, unsigned char imagemode);
			void setBackground(char * image,unsigned int width,unsigned int height, unsigned char imagemode,int indexImage,int indexWindow);

			unsigned int getWidth();
			unsigned int getWidth(int index,char *result);
			map <int,int> getWidths();

			unsigned int getHeight();
			unsigned int getHeight(int index,char *result);
			map <int,int> getHeights();

			void setWidth(int width);
			void setWidth(int width,int index);
			void setHeight(int height);
			void setHeight(int height,int index);

			void getShapeColor (int *red,int *green,int *blue);
			void getShapeColor (int *red,int *green,int *blue,int index,char * result);

			int getScaleWidth();
			int getScaleHeight();
			unsigned char getImageMode();
			unsigned char getImageMode(int index,char *result);
			map <int,unsigned char> getImageModes();

  private:
			
      map <int,char *>imagepath;
      map <int,int> width;
      map <int,int> height;
	map <int,unsigned char> imagemode;

      int x;
      int y;
      int scalewidth;
      int scaleheight;
			int addfunction;
			class MephImageImp *mephimageimp;
      class MephImageSingleton *mephimagesingleton;
};

#endif
