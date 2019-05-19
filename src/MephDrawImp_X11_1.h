#ifndef MephDrawImp_X11_h
#define MephDrawImp_X11_h 1

#include "X11/Xlib.h"

#include "MephDrawImp.h"
#include "MephAppImp.h"
//#include "MephVisObjImp.h"

class MephDrawImp_X11:public MephDrawImp
{
	public:

    ~MephDrawImp_X11();
		void clearScreen(void);
	  void drawPoints(class MephGraphicParam * mephgraphicparam, int n);
	  void drawLines(class MephGraphicParam * mephgraphicparam, int n);
	  void drawRectangles(class MephGraphicParam * mephgraphicparam, int n);
	  void drawArcs(class MephGraphicParam * mephgraphicparam, int n);
	  void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode);
	  void fillRectangles(class MephGraphicParam * mephgraphicparam, int n);
	  void fillArcs(class MephGraphicParam * mephgraphicparam, int n);
		void setBackground();
		
		void setAddFunction();

		void setForeColor();
		void setBackColor();

//	  void initValues(const class MephDraw mephdraw);	
		void initValues(class MephDraw const * mephdraw,class MephVisObjImp const * mephvisobjimp);
//		void initValues(class MephDraw const * mephdraw,class MephAppImp * mephappimp,const class MephVisObjImp * mephvisobjimp);
	
/*		setImage(char *);
		setMask(char *);*/
	
	private:
	  GC gc;
//	  Pixmap image,mask;
	
    //SE SUPONE QUE LA SIGUIENTE CLASE TIENE SENTIDO PUES DE ELLA PODREMOS SACAR EL DRAWABLE SOBRE EL 
	  //CUAL SE PINTARµN LAS LINEAS PEEERO COMO SE PIENSA TAMBIêN QUE, QUIZµS SE PINTE DIRECTAMENTE EN
	  //LOS VISOBJ PUES QUIZµS HAYA QUE A—ADIR LA OTRA CLASE TAMBIêN.
	  class MephVisObjImp * mephvisobjimp;
//		class MephAppImp *mephappimp;
	  class MephDraw * mephdraw;
	
};

#endif