## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES =\
	 -I../../../include -I/usr/X11R6/include

CXXFLAGS =\
	 -w -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wuninitialized -Wparentheses -Wtraditional -Wpointer-arith -Wmissing-prototypes\
	 -O1\
	 -g

bin_PROGRAMS = ejemplowindow

ejemplowindow_SOURCES = \
	main.cc

ejemplowindow_LDFLAGS = \
	../../../lib/MephApp.o ../../../lib/MephAppSingleton.o ../../../lib/MephAppImp.o ../../../lib/MephAppImp_X11.o ../../../lib/MephWindow.o ../../../lib/MephWindowSingleton.o ../../../lib/MephWindowImp.o ../../../lib/MephWindowImp_X11.o ../../../lib/MephVisObj.o ../../../lib/MephVisObjImp_X11.o ../../../lib/MephTextRaw.o  ../../../lib/MephTextRawSingleton.o ../../../lib/MephTextRawImp_X11.o ../../../lib/MephImage.o ../../../lib/MephImageImp.o ../../../lib/MephImageSingleton.o ../../../lib/MephImageImp_X11.o ../../../lib/MephDraw.o ../../../lib/MephDrawSingleton.o ../../../lib/MephDrawImp_X11.o ../../../lib/MephGraphicParam.o ../../../lib/MephColor.o ../../../lib/MephColorImp_X11.o ../../../lib/MephColorSingleton.o ../../../lib/MephRadioButton.o ../../../lib/MephRadioButtonSingleton.o ../../../lib/MephRadioButtonImp_X11.o ../../../lib/MephCommandButton.o ../../../lib/MephCommandButtonSingleton.o ../../../lib/MephCommandButtonImp_X11.o ../../../lib/MephListBox.o ../../../lib/MephListBoxSingleton.o  ../../../lib/MephListBoxImp_X11.o ../../../lib/MephItem.o ../../../lib/MephItemSingleton.o ../../../lib/MephItemImp_X11.o ../../../lib/MephScrollBar.o ../../../lib/MephScrollBarImp_X11.o ../../../lib/MephScrollBarSingleton.o ../../../lib/MephButton.o ../../../lib/MephFloatingWindow.o ../../../lib/MephFloatingWindowSingleton.o ../../../lib/MephFloatingWindowImp_X11.o ../../../lib/MephMenu.o ../../../lib/MephMenuSingleton.o ../../../lib/MephMenuImp_X11.o ../../../lib/MephCheckButton.o ../../../lib/MephCheckButtonSingleton.o ../../../lib/MephCheckButtonImp_X11.o ../../../lib/MephComboBox.o ../../../lib/MephComboBoxSingleton.o ../../../lib/MephComboBoxImp_X11.o\
	 -L/usr/X11R6/lib -L../../../lib

ejemplowindow_LDADD = \
	 -lX11 -lImlib -lXext

