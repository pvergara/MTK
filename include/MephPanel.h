#ifndef MephPanel_h
#define MephPanel_h 1

#include "MephPanelImp.h"
#include "MephPanelSingleton.h"
#include "MephVisObj.h"
#include "MephVisObjImp.h"
#include "MephGen.h"

#define SOLID 0
//#define IMAGE 1

#define SHAPE 1 /*EXCLUYENTE CON SOLID, VAMOS QUE, O ERES S”LIDO O TRANSPARENTE*/
#define IMAGE 2 /*INDEPENDIENTEMENTE DE QUE HAYA IMAGEN, SI ESTA ES TRANSPARENTE SE VERµ EL SOLID O EL SHAPE*/

/*MODOS DE CARGA DE IMµGENES*/
/*CUIDADO CON ESTOS MOOODIIITOOSS QUE LA COSA ESTµ UN PELÕN CAMBIAADIIITAA*/
#define MEPHWINDOWED    0<<0L
#define MEPHIMAGED      1<<0L
#define MEPHSOLID       0<<1L
#define MEPHIMAGE       1<<1L
#define MEPHGEOMETRIC   1<<2L

class MephPanel:public MephVisObj
{

  public:
      MephPanel(class MephApp const * mephapp);
      ~MephPanel();
	    
	    void addTo (const class MephVisObjImp * mephvisobjimp);
	    void addTo (const class MephVisObjImp * mephvisobjimp,short x,short y,unsigned short width,unsigned short height);
	    
	    void setAddFunction(int addfunction);
	    int getAddFunction();


			void copyBackPixmap();
			void backPixmapToMe();

      void refresh(void);
      void refresh(int x,int y,unsigned int width,unsigned int height);
			
			void move(int x,int y);
			void resize(unsigned int width,unsigned int height);
			void moveResize(int x,int y,unsigned int width,unsigned int height);
      char getBackMode();
			char getImageMode();
			char getImageMode(int index,char *result);
			map <int,char> getImageModes();
      const class MephPanelImp * getMephPanelImp();
	
	
			
	private:
			char backmode;
	
	    class MephPanelImp *mephpanelimp;
	    class MephPanelSingleton *mephpanelsingleton;
	
			/*EL PANEL ES EL ÈNICO MEPHVISOBJ QUE USA FUNCI”N DE A—ADIDURA*/
			int addfunction;
};

#endif
/*			unsigned short getBackColorR();
			unsigned short getBackColorG();
			unsigned short getBackColorB();

			unsigned short getForeColorR();
			unsigned short getForeColorG();
			unsigned short getForeColorB();

			unsigned long getBackColorIndex();

			unsigned long getForeColorIndex();
	
			void setBackColor(unsigned short red,unsigned short green,unsigned short blue);
			void setBackColor(unsigned long colorindex);
			
			void setForeColor(unsigned short red,unsigned short green,unsigned short blue);
			void setForeColor(unsigned long colorindex);*/

			/******************************************************************************************************************/
/*			void createImage();
      void deleteImage();
			
      char loadImage(char *path);
      char showImage();*/
			

//			char getImageVisible();
			/******************************************************************************************************************/
/*      void setBackground(unsigned short red,unsigned short green,unsigned short blue);
      void setBackground(unsigned long colorindex);*/

/*CUIIIIDAADOOO AQUÕ ES DONDE TENDRµ QUE ACTUAR EL POLIMORFISMO (PUES LOS MODOS DE IMAGEN NO ES EL MISMO QUE
			EN EL RESTO DE MEPHVISOBJS)!!!!!!!!!!!!!!*/
/*      void setBackground(char * image);
				void setBackground(char *image, unsigned char imagemode);*/
/*			class MephColor backcolor;
			class MephColor forecolor;
			class MephImage * mephimage;*/
