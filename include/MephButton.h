#ifndef MephButton_h
#define MephButton_h 1

#include "MephVisObj.h"
#include "MephWindowImp.h"
#include "MephPanelContainer.h"

#define ENABLED  1
#define DISABLED 0

class MephButton: public MephVisObj//,public MephPanelContainer
{
  public:
	
	  MephButton();
	  ~MephButton();
	
	  virtual void addTo(const class MephWindowImp * mephwindowimp){};
	
  protected:
	  char *caption;
	  char state;
};

#endif