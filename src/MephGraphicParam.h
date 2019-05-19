#ifndef MephGraphicParam_h
#define MephGraphicParam_h 1

class MephGraphicParam
{
	public:
	
	  MephGraphicParam();
	
	  void setX(short x);
	  void setY(short y);
	  void setX2(short x2);
	  void setY2(short y2);
	  void setAng(short ang);
	  void setAng2(short ang2);
	
	  void setWidth(unsigned short width);
		void setHeight(unsigned short height);
		
		void setPoint(short x,short y);
		void setLine (short x,short y,short x2,short y2);
		void setRectangle(short x,short y,unsigned short width,unsigned short height);
		void setArc(short x,short y,unsigned short width ,unsigned short height,short ang,short ang2);
		
		short getX();
		short getY();
		short getX2();
		short getY2();
		short getAng();
		short getAng2();
		
		unsigned short getWidth();
		unsigned short getHeight();
		
	private:
	  short x;
	  short y;
	  short x2;
	  short y2;
	
	  unsigned short width;
	  unsigned short height;
	
	  short ang,ang2;
};

#endif