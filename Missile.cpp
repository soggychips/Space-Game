# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

#include <math.h>
#define _USE_MATH_DEFINES

class Missile{

private:
	GLfloat TM[16];
	int frames, totalFrames, totalDistance;
	GLfloat tempMatrix[16];
	GLfloat currentVector[3], desiredVector[3], normCurrentVect[3], normDesiredVect[3], currentMag, desiredMag, dotProduct, dotOverMag, tempAngle, axisOR[3], axisORDirection;
	GLfloat orientToAngle;
	bool alive;



public:

	Missile(GLfloat siteX,GLfloat siteY,GLfloat siteZ, int planetNumber){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(siteX,siteY,siteZ);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		glPopMatrix();
		frames=0;
		if(planetNumber=1){ //1 or 2
			totalFrames=600;
			totalDistance = 9000;
		}else{
			totalFrames=1200;
			totalDistance = 18000;
		}
		alive=true;
	}

	void draw(){
		//printf("Missile drawn\n");
		glPushMatrix();
		glLoadMatrixf(TM);
		glColor3f(1.0,0.0,0.0);
		glutSolidSphere(25,20,20);
		glPopMatrix();
	}

	bool isMissileAlive(){
		return alive;
	}


	void update(GLfloat targetX, GLfloat targetY, GLfloat targetZ){
		if(frames>=50){
			if(frames>=totalFrames){
				//detonate
				alive=false;
			}else{
			//smart
				axisOR[0] = (TM[Ay]*targetZ)-(TM[Az]*targetY); //cross product gives axis of rotation
				axisOR[1] = (TM[Ax]*targetZ)-(TM[Az]*targetX);
				axisOR[2] = (TM[Ax]*targetY)-(TM[Ay]*targetX);
				axisORDirection = axisOR[0]+axisOR[1]+axisOR[2];
				currentVector[0]=TM[Ax];
				currentVector[1]=TM[Ay];
				currentVector[2]=TM[Az];
				currentMag = sqrt((currentVector[0]*currentVector[0])+(currentVector[1]*currentVector[1])+(currentVector[2]*currentVector[2]));
				normCurrentVect[0] = currentVector[0]/currentMag;
				normCurrentVect[1] = currentVector[1]/currentMag;
				normCurrentVect[2] = currentVector[2]/currentMag;
				desiredVector[0]=targetX-TM[Tx];
				desiredVector[1]=targetY-TM[Ty];
				desiredVector[2]=targetZ-TM[Tz];
				desiredMag = sqrt((desiredVector[0]*desiredVector[0])+(desiredVector[1]*desiredVector[1])+(desiredVector[2]*desiredVector[2]));
				normDesiredVect[0] = desiredVector[0]/desiredMag;
				normDesiredVect[1] = desiredVector[1]/desiredMag;
				normDesiredVect[2] = desiredVector[2]/desiredMag;
				//dot product of normCurrentVect and normDesiredVect
				dotProduct = (normCurrentVect[0]*normDesiredVect[0])+(normCurrentVect[1]*normDesiredVect[1])+(normCurrentVect[2]*normDesiredVect[2]);
				//magnitudes of unit vectors
				currentMag = sqrt((normCurrentVect[0]*normCurrentVect[0])+(normCurrentVect[1]*normCurrentVect[1])+(normCurrentVect[2]*normCurrentVect[2]));
				desiredMag = sqrt((normDesiredVect[0]*normDesiredVect[0])+(normDesiredVect[1]*normDesiredVect[1])+(normDesiredVect[2]*normDesiredVect[2]));
				dotOverMag = dotProduct/(currentMag*desiredMag);
				orientToAngle = acos(dotOverMag)*(180/3.14159265358979323846);//3.14159265358979323846
				if(axisORDirection<0)
					orientToAngle = (2*(3.14159265358979323846))-orientToAngle;
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glLoadMatrixf(TM);
				glRotatef(orientToAngle,axisOR[0],axisOR[1],axisOR[2]);
				glGetFloatv(GL_MODELVIEW_MATRIX,TM);
				glPopMatrix();
			}
		}else{ //frames<50
			//move forward
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadMatrixf(TM);
			glTranslatef(0.0,0.0,10.0);
			glGetFloatv(GL_MODELVIEW_MATRIX,TM);
			glPopMatrix();
		}
		frames++;
	}


};