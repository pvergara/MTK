#include <MephApp.h>
#include <MephWindow.h>
#include <MephRadioButton.h>
#include <MephCheckButton.h>
#include <MephCommandButton.h>
#include <MephListBox.h>
#include <MephFloatingWindow.h>
#include <MephMenu.h>
#include <MephComboBox.h>

/*************************************Recepcion de eventos******************************************/
void eventoMouseDownMW(class MephWindow *mephwindow,int x,int y,unsigned int
boton);
void eventoMouseDownMCB1(class MephCommandButton *mephcommandbutton,int x,int y,unsigned int
boton);
void eventoMouseDownMCB2(class MephCommandButton *mephcommandbutton,int x,int y,unsigned int
boton);
void eventoPaintMCB2(class MephCommandButton *mephcommandbutton,int x,int y,int width,int height,int count);
void eventoChangeMM(class MephItem *mephitem);
void eventoChangeMFW(class MephItem *mephitem);
void eventoChangeMFW1(class MephItem *mephitem);
void eventoChangeMSB(class MephScrollBar *mephscrollbar);

/*******************************Clases definidas de forma global************************************/
/*	ESA ES LA CLASE MAS IMPORTANTE DE TODAS PUES SIEMPRE QUE CREEMOS UNA APLICACIÓN HEMOS DE       */
/*    								TENER UN OBJETO SUYO                                           */
class MephApp ma;
class MephWindow mw(&ma);
class MephRadioButton mr1(&ma),mr2(&ma);
class MephCheckButton mchb(&ma);
class MephCommandButton mcb1(&ma),mcb2(&ma);
class MephListBox mlb(&ma);
class MephFloatingWindow mfw(&ma),mfw1(&ma);
class MephMenu mm(&ma);
class MephScrollBar msb1(&ma),msb2(&ma),msb3(&ma);
class MephItem mi(&ma);
class MephComboBox mcB(&ma);

main()
{
	/*VENTANAS*/
	mw.initImageValues(mw.getMephWindowImp());
	mw.setTitle("<--OBJETOS VISIBLES DEL MTK-->");
	mw.moveResize(100,100,400,400);
	mw.catchEventMouseDown(eventoMouseDownMW);
	mw.show();

	/*MENU*/
	mm.addTo(mw.getMephWindowImp());
	mm.addItem("Archivo");
	  mm.addSubOption("Salir","1");

	mm.addItem("Edicion");
	  mm.addSubOption("Cortar","2");
	  mm.addSubOption("Copiar","2");
	  mm.addSubOption("Pegar","2");

	mm.catchEventChange(eventoChangeMM);
	mm.show();


	/*BOTONES DE COMANDO*/
	mcb1.addTo(mw.getMephWindowImp());
	mcb1.moveResize(20,115,150,30);
	mcb1.setText("Aceptar");
	mcb1.catchEventMouseDown(eventoMouseDownMCB1);
	mcb1.show();

	mcb2.addTo(mw.getMephWindowImp());
	mcb2.moveResize(250,115,150,30);
	mcb2.setText("Aceptar");
	mcb2.catchEventMouseDown(eventoMouseDownMCB2);
	mcb2.show();

	/*BOTONES DE RADIO*/
	mr1.addTo(mw.getMephWindowImp());
	mr1.setText("Ventana sin forma");
	mr1.setGroup(0);
	mr1.check();
	mr1.moveResize(20,50,150,20);
	mr1.show();

	mr2.addTo(mw.getMephWindowImp());
	mr2.setText("Ventana con forma");
	mr2.setGroup(0);
	mr2.moveResize(20,80,150,20);
	mr2.show();

	/*CAJAS DE LISTAS*/
	mlb.addTo(mw.getMephWindowImp());
	mlb.moveResize(250,50,125,45);
	mlb.addDoubleItem("Fondo con color","negroblancoIZDE.jpg");
	mlb.addDoubleItem("Fondo con imagen","negroblancoIZDE.jpg");
	mlb.show();

	/*BARRAS DE DESPLAZAMIENTO*/
	msb1.addTo(mw.getMephWindowImp());
	msb1.moveResize(20,150,100,15);
	msb1.setMin(1);
	msb1.setMax(0xFFFF);
	msb1.show();
	msb1.catchEventChange(eventoChangeMSB);

	msb2.addTo(mw.getMephWindowImp());
	msb2.moveResize(20,175,100,15);
	msb2.setMin(1);
	msb2.setMax(0xFFFF);
	msb2.show();
	msb2.catchEventChange(eventoChangeMSB);

	msb3.addTo(mw.getMephWindowImp());
	msb3.moveResize(20,200,100,15);
	msb3.setMin(1);
	msb3.setMax(0xFFFF);
	msb3.show();
  msb3.catchEventChange(eventoChangeMSB);

	/*VENTANAS "ITEM"*/
	mi.addTo(mw.getMephWindowImp());
	mi.moveResize(140,160,50,25);
	mi.setBackground(msb1.getScrollPosition(),msb2.getScrollPosition(),msb3.getScrollPosition());
	mi.show();

	/*CAJA DE "COMBO"*/
	mcB.addTo(mw.getMephWindowImp());
	mcB.moveResize(250,200,130,15);
	mcB.addDoubleItem("Johan.jpg","negroblancoIZDE.jpg");
	mcB.addDoubleItem("window.gif","negroblancoIZDE.jpg");
	mcB.show();

	/*BOTÓN DE CHEQUEO*/
	mchb.addTo(mw.getMephWindowImp());
	mchb.moveResize(250,300,140,15);
	mchb.setText("Tamaño de ventana");
	mchb.show();


	/*VENTANAS "FLOTANTES" PERFECTAS PARA, POR EJEMPLO, MENUS CONTEXTUALES*/
	mfw.addTo(mw.getMephWindowImp());
	mfw.resize(200,100);
	mfw.addDoubleItem("Ventana con decoracion","negroblancoIZDE.jpg");
	mfw.addDoubleItem("Ventana sin decoracion","negroblancoIZDE.jpg");
	mfw.catchEventChange(eventoChangeMFW);

	mfw1.addTo(mcb2.getMephCommandButtonImp());
	mfw1.resize(200,75);
	mfw1.addDoubleItem("Decoracion estandar","negroblancoIZDE.jpg");
	mfw1.addDoubleItem("Decoracion alternativa","negroblancoIZDE.jpg");
	mfw1.catchEventChange(eventoChangeMFW1);


	ma.eventLoop();
}

void eventoMouseDownMW(class MephWindow *mephwindow,int x,int y,unsigned int
boton)
{
	if (boton==3)
		mfw.show(x,y);
}

void eventoChangeMM(class MephItem *mephitem)
{
	if (!strcmp(mephitem->getText(),"Salir"))
		mw.end();
}

void eventoMouseDownMCB1(class MephCommandButton *mephcommandbutton,int x,int y,unsigned int boton)
{
	if (mr1.getState())
	{
		mw.hide();
    mw.unshape();
		mw.show();
	}
	if (mr2.getState())
	{
		mw.hide();
		mw.shape("shape1.png");
		mw.show();
	}
}

void eventoMouseDownMCB2(class MephCommandButton *mephcommandbutton,int x,int y,unsigned int boton)
{
	MephItem *mephitem;
	char aux[100];
	if (boton==3)
		mfw1.show(x,y);
	if (boton==1)
	{
		mephitem=(class MephItem *) mlb.getSelected();
		if (!(strcmp(mephitem->getText(),"Fondo con color")))
		{
			mw.setBackground(msb1.getScrollPosition(),msb2.getScrollPosition(),msb3.getScrollPosition());
		}
		else
		{
	  		sprintf(aux,"%s","./");
  			strcat(aux,mcB.getText());
  		  if (mchb.getState())
  		  {
  			  mw.setBackground(aux,MEPHWINDOWED|MEPHIMAGE);
  		  }
	  	  else
		    {
			    mw.setBackground(aux,MEPHIMAGED|MEPHIMAGE);
 	     }
		}
	}
}

void eventoChangeMFW1(class MephItem *mephitem)
{
	if (!strcmp(mephitem->getText(),"Decoracion estandar"))
	{
		mcb2.setDecorated(1);
  	mcb2.setBold(1);
	  mcb2.setHighlight(0);
  	mcb2.setBackground(0xEFFF,0xEFFF,0xEFFF);
		mcb2.catchEventPaint(NULL);
	}
	else
	{
		mcb2.setDecorated(0);
		mcb2.catchEventPaint(eventoPaintMCB2);
	}
}

void eventoPaintMCB2(class MephCommandButton *mephcommandbutton,int x,int y,int width,int height,int count)
{
	mcb2.setBackground(0,0xFFFF,0xFFFF);
	mcb2.setBold(0);
	mcb2.setHighlight(1);
	mcb2.showText();
}

void eventoChangeMFW(class MephItem *mephitem)
{
	if (!(strcmp(mephitem->getText(),"Ventana con decoracion")))
	{
		mw.hide();
		mw.setDecoration(255);
		mw.show();
	}
	else
	{
		mw.hide();
		mw.setDecoration(0);
		mw.show();
	}
}

void eventoChangeMSB(class MephScrollBar *mephscrollbar)
{
	mi.setBackground(msb1.getScrollPosition(),msb2.getScrollPosition(),msb3.getScrollPosition());
}
