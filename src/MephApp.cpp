#include "MephApp.h"
#include <stdio.h>

int MephApp::swidth=0;
int MephApp::sheight=0;
char * MephApp::name=NULL;


MephApp::MephApp()
{
  mephappsingleton=mephappsingleton->getMephAppSingleton();
  mephappimp=mephappsingleton->getMephAppImp();

  mephappimp->initValues(0,0,NULL);

  swidth=mephappimp->getSWidth();
  sheight=mephappimp->getSHeight();
}

MephApp::MephApp(int argc,char *argv[])
{
  mephappsingleton=mephappsingleton->getMephAppSingleton();
  mephappimp=mephappsingleton->getMephAppImp();

  mephappimp->initValues(argc,argv,NULL);

  swidth=mephappimp->getSWidth();
  sheight=mephappimp->getSHeight();
}

class MephAppImp * MephApp::getMephAppImp() const
{
	return (this->mephappimp);
}

MephApp::MephApp(const MephApp &right)
{
}


MephApp::~MephApp()
{
	delete this->name;
	delete this->mephappimp;
//  delete this->mephappsingleton;
}


const MephApp & MephApp::operator=(const MephApp &right)
{
}


int MephApp::operator==(const MephApp &right) const
{
}

int MephApp::operator!=(const MephApp &right) const
{
}

void MephApp::eventLoop(void)
{
  this->mephappimp->eventLoop();
}

/*void MephApp::contain(const class MephEventImp *mepheventimp)
{
  this->mephappimp->contain(mepheventimp);
}*/

void MephApp::contain(const class MephVisObjImp *mephvisobjimp)
{
  this->mephappimp->contain(mephvisobjimp);
}
