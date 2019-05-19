#ifndef MephVisObjSingleton_h
#define MephVisObjSingleton_h 1

#include "iostream.h"
#if defined (linux)
#include "MephVisObjImp_X11.h"
#endif

class MephVisObjSingleton 
{
  public:
      MephVisObjSingleton();

      MephVisObjSingleton(const MephVisObjSingleton &right);

      ~MephVisObjSingleton();

      const MephVisObjSingleton & operator=(const MephVisObjSingleton &right);

      int operator==(const MephVisObjSingleton &right) const;

      int operator!=(const MephVisObjSingleton &right) const;

      /**********************************************************/
      class MephVisObjImp * getMephVisObjImp ();


  private:
      static MephVisObjSingleton * getMephVisObjSingleton ();

  private:
      static MephVisObjSingleton *mephvisobjsingleton;
      friend class MephVisObj;
};

inline MephVisObjSingleton * MephVisObjSingleton::getMephVisObjSingleton ()
{
  if (mephvisobjsingleton==0)
    mephvisobjsingleton=new MephVisObjSingleton;

  return (mephvisobjsingleton);
}


inline class MephVisObjImp *MephVisObjSingleton::getMephVisObjImp ()
{
  #if defined (linux)
    return (new class MephVisObjImp_X11);
  #endif
}

#endif
