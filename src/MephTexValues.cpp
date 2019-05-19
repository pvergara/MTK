#include "MephTextValues.h"
	

MephTextValues::MephTextValues(Display const * const disp,Window const id)
{
  MephTextValues::disp=disp;
	MephTextValues::id=id;
}


Display * MephTextValues::getDisplay() 
{
  return((Display *) MephTextValues::disp);
}

Window MephTextValues::getWindow()
{
  return (MephTextValues::id);
}