#ifndef MephTextRawImp_h
#define MephTextRawImp_h 1

class MephTextRawImp
{
  public:
	  virtual void initValues (const class MephTextRaw *mephtextraw,const class MephVisObjImp *mephvisobjimp){};
		virtual void show(){};
  	virtual char loadFont(){};
		virtual char refreshFont(){};
			
		virtual void setBackColor(){};
		virtual void setForeColor(){};
		virtual void setText(){};
};

#endif