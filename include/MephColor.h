#ifndef MephColor_h
#define MephColor_h 1

#include "MephColorSingleton.h"
#include "MephColorImp.h"
#include "MephApp.h"

class MephColor
{

	public:
	  MephColor();
	  MephColor(class MephApp const * mephapp);
	  ~MephColor();

	  void initValues(class MephVisObjImp const * mephvisobjimp);
	  unsigned short getRed();
	  unsigned short getGreen();
	  unsigned short getBlue();
	  unsigned long getColorIndex();
	
	  void setColor(unsigned short red,unsigned short green,unsigned short blue);
	  void setColor(unsigned long colorindex);
	  
  private:
	  unsigned short red;
	  unsigned short green;
	  unsigned short blue;
	  unsigned long colorindex;
	
	  class MephColorImp *mephcolorimp;
	  class MephColorSingleton *mephcolorsingleton;	
};

#endif