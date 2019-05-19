	#include "MephPanelContainer.h"

MephPanelContainer::MephPanelContainer()
{
	this->mephpanel=NULL;
}

MephPanelContainer::~MephPanelContainer()
{
	if (this->mephpanel!=NULL)
	  delete this->mephpanel;
}

/*void MephPanelContainer::setBackground(unsigned short red,unsigned short green,unsigned short blue)
{
	if (this->mephpanel)
		this->mephpanel->setBackground(red,green,blue);
}

void MephPanelContainer::setBackground(unsigned long colorindex)
{
	if (this->mephpanel)
		this->mephpanel->setBackground(colorindex);
}

void MephPanelContainer::setBackground(char * image)
{
	if (this->mephpanel)
  	this->mephpanel->setBackground(image);
}

void MephPanelContainer::setBackground(char * image,unsigned char imagemode)
{
	if (this->mephpanel)
		this->mephpanel->setBackground(image,imagemode);
}*/


void MephPanelContainer::refreshPanel()
{
	if (this->mephpanel)
		this->mephpanel->refresh();
}

void MephPanelContainer::refreshPanel(int x,int y,unsigned int width,unsigned int height)
{
	if (this->mephpanel)
		this->mephpanel->refresh();
}

const class MephPanelImp * MephPanelContainer::getMephPanelImp()
{
	if (this->mephpanel)
		return(this->mephpanel->getMephPanelImp());
	else
		return (NULL);
}

/*const char * MephPanelContainer::getImagePath()
{
	if (this->mephpanel)
		return(this->mephpanel->getImagePath());
	else
		return (NULL);
}*/
