#ifndef MephImageSingleton_h
#define MephImageSingleton_h 1

#if defined (linux)
  #include "MephImageImp_X11.h"
  #include "MephWindowImp_X11.h"
#endif

class MephImageSingleton 
{

  public:
      MephImageSingleton();

      MephImageSingleton(const MephImageSingleton &right);

      ~MephImageSingleton();

      const MephImageSingleton & operator=(const MephImageSingleton &right);

      int operator==(const MephImageSingleton &right) const;

      int operator!=(const MephImageSingleton &right) const;

      class MephImageImp * getMephImageImp ();
	    #if defined (linux)
      class MephImageImp * getMephImageImp (const class MephImage & mephimage,const class MephWindowImp_X11 & mephwindowimp_x11);
	    #endif
      static MephImageSingleton * getMephImageSingleton ();


  private:
      static MephImageSingleton  * mephimagesingleton;
      friend class MephImage;
};

inline MephImageSingleton * MephImageSingleton::getMephImageSingleton ()
{
  if (mephimagesingleton==0)
    mephimagesingleton=new MephImageSingleton;

  return(mephimagesingleton);
}

inline class MephImageImp * MephImageSingleton::getMephImageImp()
{
  #if defined (linux)
    return(new class MephImageImp_X11);
  #endif
}

#if defined (linux)
inline class MephImageImp * MephImageSingleton::getMephImageImp (const class MephImage & mephimage,const class MephWindowImp_X11 & mephwindowimp_x11)
{
    return(new class MephImageImp_X11(mephimage,mephwindowimp_x11));
}
#endif

#endif
