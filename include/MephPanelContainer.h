#ifndef MephPanelContainer_h
#define MephPanelContainer_h 1

#include "MephPanel.h"

class MephPanelContainer
{
	public:
	
			~MephPanelContainer();
			MephPanelContainer();
/*	    virtual void createImage(){};
      virtual void deleteImage(){};
			
      virtual char loadImage(char *path){};
      virtual char showImage(){};
			
			virtual unsigned int getImageWidth(){};
			virtual unsigned int getImageHeight(){};
			virtual char setImageWidth(int width){};
			virtual char setImageHeight(int height){};			
	  	const char * getImagePath();
  
      void setBackground(unsigned short red,unsigned short green,unsigned short blue);
      void setBackground(unsigned long colorindex);
      void setBackground(char * image);
      void setBackground(char * image,unsigned char imagemode);*/
			void refreshPanel();
			void refreshPanel(int x,int y,unsigned int width,unsigned int height);
	    const class MephPanelImp * getMephPanelImp();

  protected:
	
	  class MephPanel *mephpanel;
	
};

#endif