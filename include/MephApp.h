#ifndef MephApp_h
#define MephApp_h 1

#include <alloc.h>
#include "MephAppSingleton.h"
#include "MephAppImp.h"
#include "MephVisObjImp.h"

class MephApp
{

  public:
      MephApp();
      MephApp(int argc,char *argv[]);
      MephApp(const MephApp &right);
      ~MephApp();
      const MephApp & operator=(const MephApp &right);
      int operator==(const MephApp &right) const;
      int operator!=(const MephApp &right) const;
	    class MephAppImp * getMephAppImp() const;

	     void eventLoop(void);
	
      /************************RETORNAR INFROMACIÓN**************************/
      static int getSWidth()
      {
        return (swidth);
      }

      static int getSHeight()
      {
        return (sheight);
      }

        /*CUIDADO INFORMACIÓN DEPENDIENTE DE PLATAFORMA (ver tamibén
        MephAppImp)*/
      #if defined (linux)
      int getScreen()
      {
        return(mephappimp->getScreen());
      }
      int getNScreen()
      {
        return(mephappimp->getNscreen());
      }
      Display const * getDisplay() const
      {
        return(mephappimp->getDisplay());
      }
      #endif
      /**********************************************************************/
			
//			void contain(const class MephEventImp *mepheventimp);
			void contain(const class MephVisObjImp *mephvisobjimp);

  private:
      static int swidth;
      static int sheight;
      static char *name;

      class MephAppSingleton *mephappsingleton;
      class MephAppImp * mephappimp;
      friend class MephVisObj;
};

#endif
