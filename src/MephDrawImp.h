#ifndef MephDrawImp_h
#define MephDrawImp_h 1

#include "MephPanelImp.h"
#include "MephGraphicParam.h"

class MephDrawImp
{
	public:

		virtual void initValues(class MephDraw const * mephdraw,class MephVisObjImp const * mephvisobjimp){};
//		virtual void initValues(class MephDraw const * mephdraw,class MephAppImp * mephappimp,const class MephVisObjImp * mephvisobjimp){};

		virtual void clearScreen(void){};
		virtual void drawPoints(class MephGraphicParam * mephgraphicparam, int n,int index){};
	  virtual void drawLines(class MephGraphicParam * mephgraphicparam, int n,int index){};
	  virtual void drawRectangles(class MephGraphicParam * mephgraphicparam, int n,int index){};
	  virtual void drawArcs(class MephGraphicParam * mephgraphicparam, int n,int index){};
	  virtual void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode,int index){};
	  virtual void fillRectangles(class MephGraphicParam * mephgraphicparam, int n,int index){};
	  virtual void fillArcs(class MephGraphicParam * mephgraphicparam, int n,int index){};

		virtual void setForeColor(){};
		virtual void setBackColor(){};
		virtual void setAddFunction(){};
		virtual void setBackground(int index){};

//		virtual initValues(class MephDraw const * mephdraw){};

//		setMode(char mode);
//		char getMode();

/*		setImage(char *);
		setMask(char *);*/
};

#endif
