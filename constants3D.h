#ifndef __CONSTANTS3D__

// comment / uncomment for your operating system
//# define __Windows__    
# define __Xcode__     
//# define __Linux__      

# include <stdio.h>  

#ifdef __Windows__
#include <Windows.h>  
#include <GL/glut.h>  
#endif

#ifdef __Xcode__    
#include <GLUT/glut.h>
#endif

#ifdef __Linux__ 
#include <GL/glut.h>
#endif

// Constants

static const int Rx =  0, Ry =  1, Rz =  2, Rh = 3;
static const int Ux =  4, Uy =  5, Uz =  6, Uh = 7;
static const int Ax =  8, Ay =  9, Az = 10, Ah = 11;
static const int Tx = 12, Ty = 13, Tz = 14, Th = 15;


# define  __CONSTANTS3D__


# endif


/*
Name		#	radius	starting location
Ruber		0	1000	[0,0,0]
Unum		1	150		[4000,0,0]
U.Missile	2	25		[4325,0,0]
U.Primun	3	25		[4800,0,0]
U.Secundo	4	25		[5000,0,0]
Duo			5	200		[-7000,0,0]
Tres		6	400		[0,0,12000]
T.Primun	7	25		[0,0,13800]
T.Secundo	8	25		[0,0,14000]
T.Tertia	9	40		[0,0,14300]
T.Quartum	10	50		[0,0,14700]
T.Missile	11	25		[0,0,14825]
Quattuor	12	250		[0,0,-20000]
Q.Primun	13	50		[0,0,-21000]
*/

