#ifndef MephEventImp_h
#define MephEventImp_h 1

#if defined (linux)
  #include <X11/Xlib.h>
#endif

/*POR AHORA ESTA CLASE SOLO TIENE UN SENTIDO, CONTENER EL MÉTODO recieveEvent QUE SERÁ EL QUE TENDRÁN TODOS LOS MEPH*IMP_X11
(O CUALQUIEN IMPLEMENTACIÓN DEPENDIENTE DE PLANTAFORMA) PARA RECIBIR LOS EVENTOS. LO ÚNICO QUE TIENE LA CLASE ES LA 
DEFINICIÓN DEL MÉTODO ANTES COMENTADO PARA QUE QUEDE REDEFINIDO POR LAS CLASES CONCRETAS, PORQUE, SI ALGUIEN AÚN NO SE HA DADO
CUENTA, ESTA CLASE ES UN PELÍN ABSTRACTA*/

class MephEventImp
{
  public:
	
	
    #if defined (linux)
	    virtual void recieveEvent(XEvent xevent){};
			virtual Window getWindow(){};
    #endif
};
#endif