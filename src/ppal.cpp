#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include "MephApp.h"
#include "MephWindow.h"
#include "MephCheckButton.h"
#include "MephDraw.h"
#include "MephGraphicParam.h"
#include "MephGen.h"
#include "MephRadioButton.h"
#include "MephCommandButton.h"
#include "MephScrollBar.h"
#include "MephComboBox.h"
#include "MephListBox.h"
#include "MephFloatingWindow.h"
#include "MephMenu.h"
#include "MephTextBox.h"

MephApp ma;
MephFloatingWindow mfw(&ma);
MephWindow mw(&ma);

void lerele (class MephCommandButton *,int x,int y,unsigned int button);
void eventocambioMFW (class MephItem *mephitem);
void eventocambioMLB (class MephItem *mephitem);
void eventocambioMM (class MephItem *mephitem);
void eventopaintMW(class MephWindow * mephwindow,int x,int y,int width,int height,int count);

int main(int argc, char *argv[])
{	
  MephCommandButton mcb(&ma);
	MephCheckButton mchb (&ma);
	MephRadioButton mrb (&ma),mrb1 (&ma);
	MephListBox mlb(&ma);
	MephComboBox mcB(&ma);
	MephMenu mm(&ma);
	MephTextBox mtb(&ma);
		
  mw.setTitle("IMAGENES CON MEPHYSTO TOOLKIT");
	mw.moveResize(0,0,400,400);
	mw.initImageValues(mw.getMephWindowImp());
	mw.initTextValues(mw.getMephWindowImp());
	mw.setBackground("/mandrake/root/Johan.jpg",MEPHWINDOWED|MEPHIMAGE);
  mw.show();
  mw.catchEventPaint (eventopaintMW);
	
	mtb.addTo(mw.getMephWindowImp());
	mtb.moveResize(100,240,100,20);
	mtb.setTabIndex(5);
	mtb.show();
	
	mcb.addTo(mw.getMephWindowImp());
	mcb.moveResize(100,10,100,50);
	mcb.setTabIndex(1);
	mcb.setText("HOLA MUNDO");
	mcb.show();
	mcb.catchEventMouseDown(lerele);
	
	mchb.addTo(mw.getMephWindowImp());
	mchb.setTabIndex(2);
	mchb.moveResize(10,110,100,20);
	mchb.setText("CHEQUEO");
	mchb.show();

	mrb.addTo(mw.getMephWindowImp());
	mrb.setTabIndex(3);
	mrb.setGroup(0);
	mrb.moveResize(10,140,100,20);
	mrb.setText("RADIO");
	mrb.show();

	mrb1.addTo(mw.getMephWindowImp());
	mrb1.setTabIndex(4);
	mrb1.setGroup(0);
	mrb1.setText("BOTÓN DE RADIO");
	mrb1.moveResize(10,180,100,20);
	mrb1.show();
	
	mlb.addTo(mw.getMephWindowImp());
// ////////////////////////////////////////////////	mlb.setTabIndex(5);
	mlb.addItem("1");
	mlb.addItem(0xFFFF,0,0);
	mlb.addItem("2");
	mlb.addDoubleItem("3","/root/imagen.jpg");
	mlb.addItem("4");
	mlb.addDoubleItem("5","/root/imagen.jpg");
	mlb.addItem("6");
	mlb.addDoubleItem("7","/root/imagen.jpg");
	mlb.addItem("8");
	mlb.addItem("9");
	mlb.addItem("10");
	mlb.addItem("11");
	mlb.moveResize(100,100,100,105);
	mlb.show();
	
	mfw.addTo(mcb.getMephCommandButtonImp());
	mfw.resize(150,45);
	mfw.addItem("1");
	mfw.addDoubleItem("2","/root/imagen.jpg");
	mfw.addItem(0,0xFFFF,0xFFFF);
	mfw.addItem("4");
	
/*  mfw.catchEventChange(eventocambioMFW);
  mlb.catchEventChange(eventocambioMLB);*/
	
	mcB.addTo(mw.getMephWindowImp());
	mcB.moveResize(200,200,150,15);
	mcB.addItem("1");
	mcB.addDoubleItem("2","/root/imagen.jpg");
	mcB.addItem(0,0xFFFF,0xFFFF);
	mcB.addItem("4");
	mcB.show();
	
	mm.addTo(mw.getMephWindowImp());
	mm.addItem("Archivo");
	mm.addItem("Edición");
	mm.catchEventChange(eventocambioMM);

  mm.addSubOption("HOLA","1");
	mm.addSubOption(0x0,0xFFFF,0xFFF,"1");
	mm.addDoubleSubOption("HOLA","/root/imagen.jpg","1");
	mm.addSubOption("Salir","1");

  mm.addSubOption("Cortar","2");
	mm.addSubOption("Copiar","2");
	mm.addSubOption("Pegar","2");
	mm.show();
	
  ma.eventLoop();

  return 1;
}

void lerele (class MephCommandButton *,int x,int y,unsigned int button)
{
	if (button==Button1)
	{
		mw.end();
	}
	if (button==Button3)
	  mfw.show();
}

void eventocambioMFW (class MephItem *mephitem)
{
	printf ("VALOR RECIBIDO: %s\n",mephitem->getText());
	fflush(stdout);
}

void eventocambioMLB (class MephItem *mephitem)
{
	printf ("VALOR Perdicibo y aperdibido: %s\n",mephitem->getText());
	fflush(stdout);
}

void eventocambioMM (class MephItem *mephitem)
{
	if (!strcmp("Salir",mephitem->getText()))
	  mw.end();
}

void eventopaintMW(class MephWindow * mephwindow,int x,int y,int width,int height,int count)
{
//	mephwindow->setText(mephwindow->getText());
	mephwindow->showText();
}
