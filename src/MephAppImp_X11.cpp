#include <stdio.h> 
#include "MephAppImp_X11.h"
#include "X11/keysym.h"

int MephAppImp_X11::screen=0;
int MephAppImp_X11::nscreen=0;
Display *MephAppImp_X11::disp=NULL;
Window MephAppImp_X11::rootwindow=0;

MephAppImp_X11::MephAppImp_X11()
{
}

/*MephAppImp_X11::MephAppImp_X11(const MephAppImp_X11 &right)
{
}*/


MephAppImp_X11::~MephAppImp_X11()
{
}


const MephAppImp_X11 & MephAppImp_X11::operator=(const MephAppImp_X11 &right)
{
}


int MephAppImp_X11::operator==(const MephAppImp_X11 &right) const
{
}

int MephAppImp_X11::operator!=(const MephAppImp_X11 &right) const
{
}

void MephAppImp_X11::initValues (int argc,char *argv[],const Display *disp)
{
  char *dispname=new char;

  if (disp==NULL)
  {
    checkDispName(argc,argv,dispname);

    if ((MephAppImp_X11::disp=XOpenDisplay(dispname))==NULL)
    {
      cerr << "Error: Could not open display.\n";
      exit(-1);
    }
  }

  screen=DefaultScreen(MephAppImp_X11::disp);
  rootwindow=RootWindow(MephAppImp_X11::disp,MephAppImp_X11::screen);

	delete dispname;
}

int MephAppImp_X11::getSWidth()
{
  return (DisplayWidth(disp,screen));
}

int MephAppImp_X11::getSHeight()
{
  return (DisplayHeight(disp,screen));
}

void MephAppImp_X11::checkDispName (int argc,char *argv[],char dispname[])
{
  int i;

  dispname[0]='\x0';
  for (i=1;i<argc;i++)
  {
    if (strncmp(argv[i],"-display",8)==0)
    {
      i++;
      if (i<argc)
        strcpy(dispname,argv[i]);
      else
      {
        cerr << "Error: usage is -display DisplayName\n";
        exit(-1);
      }
    }
  }
}

void MephAppImp_X11::eventLoop(void)
{
	char end=0;
	Window idmotioned=0;
	XEvent event;
  Atom WMProtocols,DestroyWindow;
	map <MephTabIndex,struct TabIndex>::iterator i;
	multimap <Window,Window>::iterator mmi;
	
  if (!(this->mephntabindex.empty()))
	{
		i=this->mephntabindex.begin();
		XSetInputFocus(this->disp,i->second.window,RevertToNone,CurrentTime);
	}
	
  
	while(!end)
	{
		XNextEvent(this->disp,&event);
		/*EN UN MOMENTO DETERMINADO EVENT.XANY.WINDOW LE DA POR HACERSE REFERENCIA A VENTANAS
		QUE NO HAN SIDO RECOGIDAS (BUENO DE ECHO NO SON VENTANAS SON PIXMAP, SIII DE ESOS QUE
		NO RECIBEN EVENTOS...) Y PARA SALVAGUARDAR EL BUEN FUNCIONAMIENTO DEL BUCLE DE EVENTOS
		ESTµ PUESTO ESTE IF*/
		if ((this->mephvisobjimps[event.xany.window])!=NULL)
		{
  	  class MephVisObjImp *mei=(class MephVisObjImp *) this->mephvisobjimps[event.xany.window];
			
			if (event.type==MotionNotify)
			{
				/*EL PRIMER MEPHVISOBJ QUE RECIBIRµ UN MOTION*/
				if (idmotioned==0)
					idmotioned=event.xany.window;
				else
				{
					if (idmotioned!=event.xany.window)
					{			
  					if ((this->mephvisobjimps[idmotioned])!=NULL)
	  				  this->mephvisobjimps[idmotioned]->recieveNoMotion();
					
		  			idmotioned=event.xany.window;
					}
				}
			}
			if (event.type==KeyPress)
			{
				KeySym keysym;
				char cadena[5];
				int n;
				
				XLookupString(&event.xkey,cadena,5,&keysym,NULL);
				if ((keysym==XK_Tab) && (!this->mephntabindex.empty()))
				{
      		if (++i==this->mephntabindex.end())
						i=this->mephntabindex.begin();
					
		      XSetInputFocus(this->disp,i->second.window,RevertToNone,CurrentTime);
				}
			}
			if ((event.type==ButtonPress) && (event.xbutton.button & Button1))
			{
				char found=0;
    		if (this->mephztabindex[event.xbutton.window]!=NULL)
		      XSetInputFocus(this->disp,event.xbutton.window,RevertToNone,CurrentTime);
				else
				{
    	  	for (i = this->mephntabindex.begin(); (i != this->mephntabindex.end()) && (!found);++i)
		    		if (i->second.window==event.xbutton.window)
						{
	    	      XSetInputFocus(this->disp,event.xbutton.window,RevertToNone,CurrentTime);
							found=1;
						}
				}
 		  }
			/****************************************************************************************/
			mei->recieveEvent(event);
			/****************************************************************************************/

			WMProtocols=XInternAtom(this->disp,"WM_PROTOCOLS",False);
		  DestroyWindow=XInternAtom(this->disp,"WM_DELETE_WINDOW",False);
			
			if ((event.type==DestroyNotify) || (event.type==ClientMessage) && (event.xclient.message_type=WMProtocols) && (event.xclient.data.l[0]==DestroyWindow))
			{
				/*DESTRUIR TODOS LOS FLOATING WINDOW DE UNA VENTANA*/
				if (this->mephfloatingwindows.count(event.xany.window)>0)
				{
					for (mmi=this->mephfloatingwindows.lower_bound(event.xany.window);mmi!=this->mephfloatingwindows.upper_bound(event.xany.window);mmi++)
						XDestroyWindow(this->disp,mmi->second);
				}
				this->mephvisobjimps.erase(event.xany.window);
				if (this->mephvisobjimps.empty())
					end=1;
			}
		}
		else
		{
			this->mephvisobjimps.erase(event.xany.window);
//			printf ("esta ventana no fu‚ almacenada");
//			fflush(stdout);
		}
	}
	XCloseDisplay(this->disp);
}

void MephAppImp_X11::contain (const class MephVisObjImp *mephvisobjimp)
{
  /*YAAAA LOO SEEE EESTO ES UNA CHAPUZA GIGANTESCA PERO... CARAJO LO HE INTENTADO DE MIL FORMAS Y SOLO ESTA FUNCIONA*/
	class MephVisObjImp *mei=(class MephVisObjImp *) mephvisobjimp;
	Window win=mei->getWindow();
	mephvisobjimps[win]=(class MephVisObjImp *) mephvisobjimp;
}

void MephAppImp_X11::contain (const class MephVisObjImp *mephvisobjimp,int index)
{
	int i;
	char e;
	
  /*YAAAA LOO SEEE EESTO ES UNA CHAPUZA GIGANTESCA PERO... CARAJO LO HE INTENTADO DE MIL FORMAS Y SOLO ESTA FUNCIONA*/
	class MephVisObjImp *mei=(class MephVisObjImp *) mephvisobjimp;
	for (i=0;i<index;i++)
	{
	  Window win=mei->getWindow(i,&e);
	  mephvisobjimps[win]=(class MephVisObjImp *) mephvisobjimp;
	}
}
void MephAppImp_X11::contain(const class MephVisObjImp * mephvisobjimp,const class MephVisObjImp * mephfloatingwindow)
{
	class MephVisObjImp *mei=(class MephVisObjImp *) mephvisobjimp;
	Window floatingwin,win=mei->getWindow();
	mei=(class MephVisObjImp *) mephfloatingwindow;
	floatingwin=mei->getWindow();
	
	mephvisobjimps[win]=(class MephVisObjImp *) mephvisobjimp;
	mephfloatingwindows.insert(make_pair(win,floatingwin));
}

char MephAppImp_X11::setTabIndex(Window window,MephTabIndex tabindex,char enabled)
{
  /*SI NO ESTµN VACIAS LAS LISTAS DE TABINDEX*/
	
	map <MephTabIndex,struct TabIndex>::iterator i;
  if (!(this->mephntabindex.empty())	|| (!(this->mephztabindex.empty())))
	{
		if (this->mephztabindex[window]!=NULL)
		{
			if (tabindex==0)
			{
			  this->mephztabindex[window]=enabled;
  		  return (1);
			}
			else
			{
				if (!this->seekTabIndex(window,tabindex))
				{
	  		  this->mephztabindex.erase(window);
					this->mephntabindex[tabindex].window=window;
					this->mephntabindex[tabindex].enabled=enabled;
					return(1);
				}
				else
					return(0);
			}
		}
		else
		{
			if (tabindex==0)
			{
			  this->mephztabindex[window]=enabled;
  		  return (1);
			}
			else /*la ventana a insertar no tiene tabindex 0 y tampoco estuvo incluída all */
			{
  	  	for (i = this->mephntabindex.begin(); i != this->mephntabindex.end();++i)
	  	  {
  	  		if (i->second.window==window)
	  	  	{
		  	  	if (i->first==tabindex)
			  	  {
      		  	this->mephntabindex[tabindex].enabled=enabled;
    					return (1);
	       		}
						else
						{
    		    	if (!this->seekTabIndex(window,tabindex))
  	    	    {
	 		          this->mephntabindex.erase(tabindex);
  				      if (tabindex==0)
  	  				    this->mephztabindex[window]=enabled;
	  	  		    else
		  	  	    {
			  	  	    if (tabindex>0)
				  	      {
     			  		    this->mephntabindex[tabindex].window=window;
	        	  	    this->mephntabindex[tabindex].enabled=enabled;
		  			      }
			  	      }
				        return(1);
			        }
			        else
				        return(0);
						}
  			  }
	  		}
  	    if (tabindex>0)
 	      {
   		    this->mephntabindex[tabindex].window=window;
	  	    this->mephntabindex[tabindex].enabled=enabled;
  				return(1);
	      }
			}
		}			
	}
	if (tabindex==0)
		this->mephztabindex[window]=enabled;
	else
	{
		if (tabindex>0)
		{
			this->mephntabindex[tabindex].window=window;
   		this->mephntabindex[tabindex].enabled=enabled;
		}
  }
	return(1);
}

char MephAppImp_X11::seekTabIndex(Window window,MephTabIndex tabindex)
{
	map <MephTabIndex,struct TabIndex>::iterator i;

  if ((this->mephntabindex.empty())	|| ((this->mephztabindex.empty())))
		return(0);
	else
	{
		if (this->mephztabindex[window]!=NULL)
			return(1);
		else
		{
	  	for (i = this->mephntabindex.begin(); i != this->mephntabindex.end();++i)
				if (i->first==tabindex)
					return(2);
		}
		return(0);
	}
}

