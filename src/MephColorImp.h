#ifndef MephColorImp_h
#define MephColorImp_h 1

class MephColorImp
{
  public:
	  virtual void initValues(class MephVisObjImp const * mephvisobjimp){};

		virtual unsigned short getRed(unsigned long colorindex){};
	  virtual unsigned short getGreen(unsigned long colorindex){};
	  virtual unsigned short getBlue(unsigned long colorindex){};
	  virtual unsigned long getColorIndex(unsigned short red,unsigned short green,unsigned short blue){};
};

#endif