#include "MephPanelContainerImp_X11.h"
#include "MephPanelImp_X11.h"

MephPanelContainerImp_X11::MephPanelContainerImp_X11():mephpanelimp(NULL)
{
}


void MephPanelContainerImp_X11::initValues (const class MephPanelImp * mephpanelimp)
{
	if (this->mephpanelimp)
		this->mephpanelimp=(class MephPanelImp *)mephpanelimp;
}
