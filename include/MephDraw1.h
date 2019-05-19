#ifndef MephDraw_h
#define MephDraw_h 1

#include "MephDrawSingleton.h"
#include "MephDrawImp.h"

#include "MephColor.h"
#include "MephGraphicParam.h"
#include "MephGen.h"
//#include "MephImage.h"

class MephDraw
{
	public:
	
	  MephDraw();
	  ~MephDraw();
	
	  void initValues(class MephVisObjImp const * mephvisobjimp);
//	  void initValues(const class MephPanelImp * mephpanelimp);
//	  void initValues(const class MephVisObjImp * mephvisobjimp,class MephApp const * mephapp);
	
    void clearScreen(void);
	  void drawPoints(class MephGraphicParam * mephgraphicparam, int n);
	  void drawLines(class MephGraphicParam * mephgraphicparam, int n);
	  void drawRectangles(class MephGraphicParam * mephgraphicparam, int n);
	  void drawArcs(class MephGraphicParam * mephgraphicparam, int n);
	  void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode);
	  void fillRectangles(class MephGraphicParam * mephgraphicparam, int n);
	  void fillArcs(class MephGraphicParam * mephgraphicparam, int n);
    void setBackground(unsigned short red,unsigned short green,unsigned short blue);
    void setBackground(unsigned long colorindex);
	
		
		void setMode(char mode);
		char getMode();
		
		void setAddFunction(int addfunction);
		int getAddFunction ();
		
/*		setImage(char *);
		setMask(char *);*/
		
	  unsigned short getForeColorR();
	  unsigned short getForeColorG();
	  unsigned short getForeColorB();
	  unsigned long getForeColorIndex();
	
	  void setForeColor(unsigned short red,unsigned short green,unsigned short blue);
	  void setForeColor(unsigned long colorindex);
	  
		unsigned short getBackColorR();
	  unsigned short getBackColorG();
	  unsigned short getBackColorB();
	  unsigned long getBackColorIndex();
	
	  void setBackColor(unsigned short red,unsigned short green,unsigned short blue);
	  void setBackColor(unsigned long colorindex);  

  private:
	
	  class MephDrawSingleton *mephdrawsingleton;
	  class MephDrawImp *mephdrawimp;
	
	  class MephColor backcolor,forecolor;
	  int addfunction;
	
//	  class MephImage *mephimage;
	
	/*EL MODO EL LA CLASE MEPHDRAW SE HARµ REFERENCIA AL TIPO DE RELLENO QUE TENDRµN DETERMINADOS TIPOS
	DE FORMAS, ESTOS RELLENOS PUEDEN SER SÓLIDOS (MODE TODO A CEROS) PUEDEN TENER UNA IMAGEN (MODE A 1)
	PUEDE TENER RELLENOS SÓLIDOS PERO CON TRANSPARENCIAS (MODE A 2) Y PUEDE TENER UNA IMAGEN Y 
	TRANSPARENCIA (MODE A 3)*/
	  char mode;  
};

#endif