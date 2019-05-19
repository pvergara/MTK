#ifndef MephTextRaw_h
#define MephTextRaw_h 1

#include "MephColor.h"
#include "MephVisObjImp.h"

#include "MephTextRawImp.h"
#include "MephTextRawSingleton.h"

class MephTextRaw
{
  public:
		MephTextRaw();
	  void initValues (const class MephVisObjImp *mephvisobjimp);
	
	  /*MÉTODOS ESPECÍFICOS (vamos los importantes...leches para los que se creó esta claasee...mas claro?...EL AGUA!!!!)*/
	
//  	char loadFont();
	  void show();
//	  void hide();
	
	  /*MÉTODOS DE ATRIBUTOS*/
	  char setFontName(char fontname[256]);
		void putFontName(char fontname[256]);
	  char *getFontName();
	  char getBold();
	  char setBold(char bold);
	  void putBold(char bold);
	  char getItalic();
	  char setItalic(char italic);
	  void putItalic(char italic);
		char getTwoBytesChar();
	  void setTwoBytesChar(char twobyteschar);
	  char getHighlight();
	  void setHighlight(int highlight);
	  char getSize();
	  char setSize(char size);
	  void putSize(char size);
    void setText(char *text);
	  char *getText();
	  /*DEVUELVE 0 SI NO HA PODIDO CAMBIAR EL TAMAÑO Y 1 SI SI HA PODIDO (es que hay peñita que se pasa pelín asignando memoria
	  a una cadena de caracteres...que nooo???)*/
	  char setMaxLength(unsigned long maxlength);
	  char getMaxLength();

	  /*POOOSIIICIIIOONNAAAMMMIIIEENNTOOO DEEEELL TEEEXXTOOO!!!!!*/
	  void setX(int x);
	  int getX();
	  void setY(int y);
		int getY();
	  void setWidth(unsigned int width);
	  int getWidth();
	  void setHeight(unsigned int height);
		int getHeight();
		int getLineSpace();
		void setLineSpace(int linespace);
	  /***********************************************************/
	
	  /*CCCCCCCCCOOOOOLLLLLLLOOOOORRRRRRR DEEEELL TEEEXXTOOO!!!!!*/
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
	  char fontname[256];
	  char bold;
	  char italic;
		char highlight;
	  char size;
	  char *text;
	  unsigned long maxlength;
	  int x;
	  int y;
	  unsigned int width;
	  unsigned int height;
		int linespace;
		char twobyteschar;
	  class MephColor forecolor,backcolor;
		
		class MephTextRawImp *mephtextrawimp;
		class MephTextRawSingleton *mephtextrawsingleton;
};

#endif