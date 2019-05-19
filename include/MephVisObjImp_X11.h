#ifndef MephVisObj_X11_h
#define MephVisObj_X11_h 1

#include "MephAppImp_X11.h"
#include <X11/keysym.h>

class MephVisObjImp_X11
{

  public:
      MephVisObjImp_X11();
      MephVisObjImp_X11(const MephVisObjImp_X11 &right);
      ~MephVisObjImp_X11();
      const MephVisObjImp_X11 & operator=(const MephVisObjImp_X11 &right);
      int operator==(const MephVisObjImp_X11 &right) const;
      int operator!=(const MephVisObjImp_X11 &right) const;

//      void initValues(int x,int y,int width,int height);
//	    virtual void recieveEvent(XEvent event){};

  protected:
      /*ESTAS FUNCIONES EST�S HECHAS APROBECHANDO QUE LOS ATRIBUTOS DE
      MEPHAPPIMP_X11 SON EST�TICOS Y DE ESA FORMA NO HACE FALTA CREAR UN OBJETO
      DE DICHA CLASE PARA OBTENER SUS VALORES...PERO...�A ESTO NO SE LE LLAMA
      VIOLACI�N DEL ENCAPSULAMIENTO EN TOOOODAAA REGLA?...PERO CLARO... MI ALMA
      ESTRUCTURADA SE PELEA CON LA ORIENTADA A OBJETOS Y LE DICE A ESTA �LTIMA
      !CARAJO� �PORQUE VAMOS A GASTAR MAS MEMORIA CREANDO OTRO OBJETO DE LA CLASE
      MEPHAPPIMP_X11 CUANDO PODEMOS OBTENER LA INFORMACI�N CON ESTE OTRO PEQUE�O
      TRUCO? (snniff reflexiones que... si este pobre narrador trabajase a las 3
      de la tarde en vez de a las tres de la ma�ana...pues seguro que no habr�a
      problema :-( )*/

      int getScreen ();
      int getNScreen ();
			const Display *getDisplay();
      Window getRootWindow();
			GC getGC();

  protected:
      map <int,Drawable> id;
      Window parent;
			GC gc;

      class MephAppImp *mephappimp;
};

#endif
