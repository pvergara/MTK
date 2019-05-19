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
	  void drawPoints(class MephGraphicParam * mephgraphicparam, int n,int index);
	  void drawLines(class MephGraphicParam * mephgraphicparam, int n,int index);
	  void drawRectangles(class MephGraphicParam * mephgraphicparam, int n,int index);
	  void drawArcs(class MephGraphicParam * mephgraphicparam, int n,int index);
	  void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode,int index);
	  void fillRectangles(class MephGraphicParam * mephgraphicparam, int n,int index);
	  void fillArcs(class MephGraphicParam * mephgraphicparam, int n,int index);
		void setBackground(int index);
		
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
	  //CUAL SE PINTAR�N LAS LINEAS PEEERO COMO SE PIENSA TAMBI�N QUE, QUIZ�S SE PINTE DIRECTAMENTE EN
	  //LOS VISOBJ PUES QUIZ�S HAYA QUE A�ADIR LA OTRA CLASE TAMBI�N.
	  class MephVisObjImp * mephvisobjimp;
//		class MephAppImp *mephappimp;
	  class MephDraw * mephdraw;

};

#endif
