#include <MephApp.h>
#include <MephWindow.h>

main()
{
	MephApp ma;
	MephWindow mw(&ma);
	
	mw.show();
	ma.loopback();
}
