#ifndef _MephGen_h_
#define _MephGen_h_ 1

typedef unsigned int MephUpdateParam;
typedef int MephTabIndex;

#define MephUVisible  							1<<0L
#define MephUCoord		 							1<<1L
#define MephUSize    								1<<2L
#define MephUDecoration							1<<3L
#define MephUDecorationFunction			1<<4L
#define MephUMouseIcon							1<<5L
#define MephUMouseCoord  						1<<6L
#define MephUTitle    							1<<7L
#define MephUPressed    						1<<8L
#define MephUMoused    							1<<9L
#define MephUOrientation     				1<<10L
#define MephUPositionUp  			    	1<<11L
#define MephUPositionDown			    	1<<12L

#define MEPHFUNCTIONCLEAR 				0x0
#define MEPHFUNCTIONAND   				0x1
#define MEPHFUNCTIONANDREVERSE 		0x2
#define MEPHFUNCTIONCOPY 					0x3
#define MEPHFUNCTIONANDINVERTED 	0x4
#define MEPHFUNCTIONNOOP  				0x5
#define MEPHFUNCTIONXOR   				0x6
#define MEPHFUNCTIONOR    				0x7
#define MEPHFUNCTIONNOR   				0x8
#define MEPHFUNCTIONEQUIV 				0x9
#define MEPHFUNCTIONINVERT 				0xa
#define MEPHFUNCTIONORREVERSE 		0xb
#define MEPHFUNCTIONCOPYINVERTED 	0xc
#define MEPHFUNCTIONORINVERTED 		0xd
#define MEPHFUNCTIONNAND  				0xe
#define MEPHFUNCTIONSET   				0xf


#define MEPHWINDOWED    0<<0L
#define MEPHIMAGED      1<<0L
#define MEPHSOLID       0<<1L
#define MEPHIMAGE       1<<1L

#endif
