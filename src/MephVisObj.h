#ifndef MephVisObj_h
#define MephVisObj_h 1

#include "MephApp.h"
#include "MephImage.h"
#include "MephDraw.h"
#include "MephGen.h"
#include "MephTextRaw.h"
#include <map.h>

#define MEPHSHIFTSTATE       1<<0L
#define MEPHSHIFTLOCKSTATE   1<<1L
#define MEPHCONTROLSTATE     1<<2L
#define MEPHALTSTATE         1<<3L
#define MEPHCAPLOCKSTATE     1<<4L
#define MEPHSCROLLLOCKSTATE  1<<7L
#define MEPHALTGRSTATE       1<<13L

#define MEPHKEYCHAR 5

#define NOTFOCUSED 0
#define FOCUSED    1

class MephVisObj
{

  public:
      MephVisObj();
      MephVisObj(const MephVisObj &right);
      ~MephVisObj();

      const MephVisObj & operator=(const MephVisObj &right);
      int operator==(const MephVisObj &right) const;
      int operator!=(const MephVisObj &right) const;

	    char const * getName() const;
	    int getX();
	    int getY();
	    int getWidth();
	    int getHeight();

	    int getX(int index,char *result);
	    int getY(int index,char *result);
	    int getWidth(int index,char *result);
	    int getHeight(int index,char *result);

      map <int,int> getXs();
	    map <int,int> getYs();
	    map <int,int> getWidths();
	    map <int,int> getHeights();
	    char getVisible();
			
			/***************************************************************************************************************/
	    char getIsPanel();
			void setDecorated(char decorated);
			char getDecorated();
		
	    void initDrawValues(class MephVisObjImp const *mephvisobjimp);
			void initImageValues(class MephVisObjImp const *mephvisobjimp);
	  	void initTextValues(class MephVisObjImp const *mephvisobjimp);
			
			void deleteMephDraw();
			void deleteMephImage();
  		void deleteMephTextRaw();


			void setDrawAddFunction(int addfunction);
			int getDrawAddFunction();

			void setImageAddFunction(int addfunction);
			int getImageAddFunction();
			
			/*MêTODOS DEL MEPHTEXTRAW*/
  	  void showText();
  	  char setFontName(char fontname[256]);
	    char *getFontName();
  	  char getBold();
	    char setBold(char bold);
  	  char getItalic();
	    char setItalic(char italic);
  		char getTwoBytesChar();
	    void setTwoBytesChar(char twobyteschar);
	    char getHighlight();
  	  void setHighlight(int highlight);
	    char getTextSize();
	    char setTextSize(char size);
      void setText(char *text);
	    char *getText();
  	  char setMaxLength(unsigned long maxlength);
	    char getMaxLength();

  	  /*POOOSIIICIIIOONNAAAMMMIIIEENNTOOO DEEEELL TEEEXXTOOO!!!!!*/
	    void setTextX(int x);
  	  int getTextX();
	    void setTextY(int y);
		  int getTextY();
  	  void setTextWidth(unsigned int width);
	    int getTextWidth();
  	  void setTextHeight(unsigned int height);
	  	int getTextHeight();
		  int getLineSpace();
  		void setLineSpace(int linespace);
	    /***********************************************************/
	
  	  /*CCCCCCCCCOOOOOLLLLLLLOOOOORRRRRRR DEEEELL TEEEXXTOOO!!!!!*/
	    unsigned short getTextForeColorR();
	    unsigned short getTextForeColorG();
  	  unsigned short getTextForeColorB();
	    unsigned long  getTextForeColorIndex();
	
  	  void setTextForeColor(unsigned short red,unsigned short green,unsigned short blue);
	    void setTextForeColor(unsigned long colorindex);
	  
  		unsigned short getTextBackColorR();
	    unsigned short getTextBackColorG();
	    unsigned short getTextBackColorB();
  	  unsigned long getTextBackColorIndex();
	
  	  void setTextBackColor(unsigned short red,unsigned short green,unsigned short blue);
	    void setTextBackColor(unsigned long colorindex);  
			/*************************/

/*			void setTextRawAddFunction(int addfunction);
			int getTextRawAddFunction();*/

			/*METODOS QUE IRµN PARA EL PAQUETE MEPHDRAW*/
			/*TANTO FORE COMO BACK COLOR SERµN PROPIEDAD EXCLUSIVA DE MEPHDRAW*/
			void clearScreen(void);
			unsigned short getBackColorR();
			unsigned short getBackColorG();
			unsigned short getBackColorB();
			unsigned short getForeColorR();
			unsigned short getForeColorG();
			unsigned short getForeColorB();
			unsigned long getBackColorIndex();
			unsigned long getForeColorIndex();
			/*CUIDADO NO CONFUNDIR ESTE MêTODO CON GETBACKCOLORINDEX (êSTE NO TIENE INDEX)
			PORQUE TIENEN PROP”SITOS DISTÕNTOS, êSTE SIRVE PARA "RECORDAR" CUAL ES EL
			COLOR DE FONDO DE CUALQUIER MEPHVISOBJ, ESTO SE ESTµ HACIENDO ASÕ PORQUE
			TODAS LAS RUTINAS DE DIBUJO DEL FONDO DE VISOBJ'S USAN LOS COLORES DEL MEPHDRAW
			Y CLARO, SI EN ALGÈN MOMENTO HACE FALTA RECORDAR CUAL ES EL COLOR QUE SE ESTABA
			USANDO PARA PINTAR EL FONDO DE LOS OBJETOS VISIBLES Y SE HA PINTADO ALGO 
			ANTERIORMENTE CON OTRO COLOR NO SE PODRÕA RECORDAR A NO SER QUE DICHO VALOR
			QUEDE ALMACENADO EN ESTE CASO EN FORMA DE "BACKCOLOR"*/
			unsigned long getBackColor();
			unsigned long getBackColor(int index,char *result);
			map <int,unsigned long> getBackColors();
  		void setBackColor(unsigned short red,unsigned short green,unsigned short blue);
			void setBackColor(unsigned long colorindex);
			void setForeColor(unsigned short red,unsigned short green,unsigned short blue);
			void setForeColor(unsigned long colorindex);
      void setBackground(unsigned short red,unsigned short green,unsigned short blue);
      void setBackground(unsigned long colorindex);
      void setBackground(unsigned short red,unsigned short green,unsigned short blue,int index);
      void setBackground(unsigned long colorindex,int index);
      void setBackground();
      void setBackground(int index);
				
  	  void drawPoints(class MephGraphicParam * mephgraphicparam, int n,int index);
	    void drawLines(class MephGraphicParam * mephgraphicparam, int n,int index);
  	  void drawRectangles(class MephGraphicParam * mephgraphicparam, int n,int index);
	    void drawArcs(class MephGraphicParam * mephgraphicparam, int n,int index);
  	  void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode,int index);
	    void fillRectangles(class MephGraphicParam * mephgraphicparam, int n,int index);
	    void fillArcs(class MephGraphicParam * mephgraphicparam, int n,int index);

  	  void drawPoints(class MephGraphicParam * mephgraphicparam, int n);
	    void drawLines(class MephGraphicParam * mephgraphicparam, int n);
	    void drawRectangles(class MephGraphicParam * mephgraphicparam, int n);
  	  void drawArcs(class MephGraphicParam * mephgraphicparam, int n);
	    void fillPolygons(class MephGraphicParam * mephgraphicparam, int n,int shape,int mode);
	    void fillRectangles(class MephGraphicParam * mephgraphicparam, int n);
  	  void fillArcs(class MephGraphicParam * mephgraphicparam, int n);
	  	void setDrawMode(char mode);
		  char getDrawMode();

			/*METODOS QUE IRµN PARA EL PAQUETE IMAGE*/
			void refreshImage(void);
			void refreshImage(int index);
			void shape(char *path);
			void shape(char *path,int indexImage,int indexWindow);
			void setBackground(char * image);
			void setBackground(char * image,unsigned char imagemode);
			void setBackground(char * image,unsigned char imagemode,int indexImage,int indexWindow);
      char showImage();
      char showImage(int indexImage,int indexWindow);
      unsigned int getImageWidth();
      unsigned int getImageWidth(int index,char *result);
			unsigned int getImageHeight();
			unsigned int getImageHeight(int index,char *result);
			char setImageWidth(int width);
			char setImageWidth(int width,int index);
			char setImageHeight(int height);			
			char setImageHeight(int height,int index);			
			const char * getImageData();
			const char * getImageData(int index,char *result);
			const char * getImagePath();
			const char * getImagePath(int index,char *result);
			void getImageShapeColor (int *red,int *green,int *blue);
			void getImageShapeColor (int *red,int *green,int *blue,int index,char *result);
			
			char getBackMode();
			char getImageMode();
			char getImageMode(int index,char *result);
			
			/*TABINDEX*/
			MephTabIndex getTabIndex();
			char getTabIndexEnabled ();
			virtual char setTabIndex (MephTabIndex tabindex){};
			void putTabIndex (MephTabIndex tabindex);
			char getFocused();
			void setFocused(char focused);
		
			
			
  protected:
      char *name;
      map <int,int> x;
      map <int,int> y;
      map <int,int> width;
      map <int,int> height;
			map <int,unsigned long> backcolor;
			map <int,char> imagemode;

			char visible;
			MephTabIndex tabindex;
			char focused;

			class MephImage * mephimage;
			class MephDraw * mephdraw;
			class MephTextRaw * mephtextraw;
			char ispanel;
			char decorated;

};
#endif
