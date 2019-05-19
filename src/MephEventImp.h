#ifndef MephEventImp_h
#define MephEventImp_h 1

#if defined (linux)
  #include <X11/Xlib.h>
#endif

/*POR AHORA ESTA CLASE SOLO TIENE UN SENTIDO, CONTENER EL M�TODO recieveEvent QUE SER� EL QUE TENDR�N TODOS LOS MEPH*IMP_X11
(O CUALQUIEN IMPLEMENTACI�N DEPENDIENTE DE PLANTAFORMA) PARA RECIBIR LOS EVENTOS. LO �NICO QUE TIENE LA CLASE ES LA 
DEFINICI�N DEL M�TODO ANTES COMENTADO PARA QUE QUEDE REDEFINIDO POR LAS CLASES CONCRETAS, PORQUE, SI ALGUIEN A�N NO SE HA DADO
CUENTA, ESTA CLASE ES UN PEL�N ABSTRACTA*/

class MephEventImp
{
  public:
	
	
    #if defined (linux)
	    virtual void recieveEvent(XEvent xevent){};
			virtual Window getWindow(){};
    #endif
};
#endif