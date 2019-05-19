#include "MephButton.h"

MephButton::MephButton():caption(NULL),state(1)
{
}

MephButton::~MephButton()
{
	delete this->caption;
}
