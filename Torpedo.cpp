# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

#include <math.h>

class Torpedo{

private:
	GLfloat TM[16];
	int frames, totalFrames;
	GLfloat tempMatrix[16];



public:

	Torpedo(GLfloat shipX,GLfloat shipY,GLfloat shipZ, int planetNumber){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(shipX,shipY,shipZ);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		glPopMatrix();
		frames=0;
		if(planetNumber=1)
			totalFrames=600;
		else
			totalFrames=1200;
	}

	void draw(){
		printf("warbird->draw()\n");
		glPushMatrix();
		glLoadMatrixf(TM);
		glColor3f(1.0,0.0,0.0);
		glutSolidSphere(25,20,20);
		glPopMatrix();
	}

	void update(){
		if(frames>=50){
			//smart

		}else if(frames<totalFrames){
			//move forward
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadMatrixf(TM);
			glTranslatef(0.0,0.0,15.0);
			glGetFloatv(GL_MODELVIEW_MATRIX,TM);
			glPopMatrix();
		}else{
			//explode
		}
		frames++;
	}


};