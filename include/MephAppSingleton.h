#ifndef MephAppSingleton_h
#define MephAppSingleton_h 1

#include <iostream.h>

#include "MephApp.h"

#if defined (linux)
  #include "MephAppImp_X11.h"
#endif

class MephAppSingleton 
{

  public:
      MephAppSingleton();

      MephAppSingleton(const MephAppSingleton &right);

      ~MephAppSingleton();

      const MephAppSingleton & operator=(const MephAppSingleton &right);

      int operator==(const MephAppSingleton &right) const;

      int operator!=(const MephAppSingleton &right) const;

      class MephAppImp * getMephAppImp ();

  private:
      static MephAppSingleton * getMephAppSingleton ();

  private:
      static MephAppSingleton *mephappsingleton;
      friend class MephApp;
};

inline MephAppSingleton * MephAppSingleton::getMephAppSingleton ()
{
  if (mephappsingleton==0)
    mephappsingleton=new MephAppSingleton;

  return(mephappsingleton);
}

inline class MephAppImp * MephAppSingleton::getMephAppImp()
{
  #if defined (linux)
    return(new class MephAppImp_X11);
  #endif
}

#endif
