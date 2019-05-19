#include <MephApp.h>
#include <MephWindow.h>
#include <MephRadioButton.h>
#include <MephCommandButton.h>
#include <MephListBox.h>
#include <MephFloatingWindow.h>
#include <MephMenu.h>

/*Recepcion de eventos*/
void eventoMouseDownMW(class MephWindow *mephwindow,int x,int y,unsigned int boton);
void eventoChangeMM(class MephItem *mephitem);

/*Clases definidas de forma global*/
class MephApp ma;
class MephWindow mw(&ma);
class MephRadioButton mr1(&ma),mr2(&ma);
class MephCommandButton mcb1(&ma),mcb2(&ma);
class MephListBox mlb(&ma);
class MephFloatingWindow mfw(&ma);
class MephMenu mm(&ma);

main()
{
	/*VENTANAS*/
	mw.initImageValues(mw.getMephWindowImp());
	mw.setTitle("OBJETOS VISIBLES DEL MTK");
	mw.moveResize(100,100,400,400);
	mw.catchEventMouseDown(eventoMouseDownMW);
	mw.shape("../../../imagenes/shapewindow.png");
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
	mcb1.show();
	
	mcb2.addTo(mw.getMephWindowImp());
	mcb2.moveResize(250,115,150,30);
	mcb2.setText("Aceptar");
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
	mr2.moveResize(20,80,125,20);
	mr2.show();
	
	/*CAJAS DE LISTAS*/
	mlb.addTo(mw.getMephWindowImp());	
	mlb.moveResize(250,50,125,45);
	mlb.addItem("Fondo con color");
	mlb.addItem("Fondo con imagen");
	mlb.show();
	
	/*VENTANAS "FLOTANTES" PERFECTAS PARA, POR EJEMPLO, MENUS CONTEXTUALES*/
	mfw.addTo(mw.getMephWindowImp());
	mfw.resize(200,100);
	mfw.addDoubleItem("Ventana con decoracion","../../../imagenes/negroblancoIZDE.jpg");
	mfw.addDoubleItem("Ventana sin decoracion","../../../imagenes/negroblancoIZDE.jpg");
	
	
	ma.eventLoop();
}

void eventoMouseDownMW(class MephWindow *mephwindow,int x,int y,unsigned int boton)
{
	if (boton==3)
		mfw.show(x,y);
}

void eventoChangeMM(class MephItem *mephitem)
{
	if (!strcmp(mephitem->getText(),"Salir"))
		mw.end();
}
