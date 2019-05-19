#ifndef MephappImp_X11_h
#define MephappImp_X11_h 1

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map.h>
#include <multimap.h>

#include "MephAppImp.h"
#include "MephVisObjImp.h"
#include "MephVisObjImp_X11.h"
#include "MephGen.h"

struct TabIndex
{
	Window window;
	char enabled;
};

class MephAppImp_X11: public MephAppImp
{

  public:
      MephAppImp_X11();
      MephAppImp_X11(const MephAppImp_X11 &right);
      ~MephAppImp_X11();
      const MephAppImp_X11 & operator=(const MephAppImp_X11 &right);
      int operator==(const MephAppImp_X11 &right) const;
      int operator!=(const MephAppImp_X11 &right) const;

	    void eventLoop (void);

      int getScreen()
      {
        return (this->screen);
      }

      int getNscreen()
      {
        return (this->nscreen);
      }

      Display const * getDisplay() const
      {
        return (this->disp);
      }
			
			Window getRootWindow()
			{
				return (this->rootwindow);
			}

      void initValues (int argc,char *argv[],const Display *disp);
      int getSWidth();
      int getSHeight();
			void contain (const class MephVisObjImp *mephvisobjimp);
			void contain (const class MephVisObjImp *mephvisobjimp,int index);
			void contain(const class MephVisObjImp * mephvisobjimp,const class MephVisObjImp * mephfloatingwindow);
			char setTabIndex(Window window,MephTabIndex tabindex,char enabled);

  private:
      void checkDispName (int argc,char *argv[],char dispname[]);

  private:
			char seekTabIndex(Window window,MephTabIndex tabindex);
      static int screen;
      static int nscreen;
      static Display *disp;
      static Window rootwindow;
      friend class MephVisObjImp_X11;
      /*ESTA ÈLTIMA RELACI”N ESTµ POR CONFIRMAR PUES NO ES MUY ELEGANTE ESTE TIPO DE
			RELACIONES Y SIEMPRE HAN DE SER EVITADAS EN LA MEDIDA DE LO POSIBLE, PERO EN UN
			PRINCIPIO ESTA SOLUCI”N SE VEÕA COMO LA ÈNICA POSIBLE PARA QUE LA CLASE MEPHCOLORIMP_X11
			OBTUVIESE DE ALGUNA FORMA EL PUNTERO A DISPLAY QUE NECESITA PARA FUNCIONAR*/
			friend class MephColorImp_X11;
			
			/******************************************************************************/
		  map<Window,class MephVisObjImp *> mephvisobjimps;
		  map<Window,MephTabIndex> mephztabindex;
		  map<MephTabIndex,struct TabIndex> mephntabindex;
		  multimap<Window,Window> mephfloatingwindows;
      /*****************************************************************************/
};
#endif
