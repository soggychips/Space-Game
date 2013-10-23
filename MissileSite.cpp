# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

#include <math.h>
#include "Missile.cpp"

class MissileSite { 
  
	private:
  		GLfloat siteColor[3], siteLocation[3];
  		GLfloat siteSize;
  		GLfloat TM[16]; //transformation matrix
		GLfloat viewMatrix[16], inverseMatrix[16];
		int missileCount;
		GLfloat detectionDistance;
		GLfloat currentShipDistance;
		Missile * missile;
		bool missileUp;
		
		

  public:

	MissileSite (GLfloat sSize, GLfloat sColor[3], GLfloat sLocation[3]) {
		for(int i = 0; i<3; i++) {
			siteColor[i] = sColor[i];
			siteLocation[i] = sLocation[i];
			}
		siteSize = sSize;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(sLocation[0],sLocation[1],sLocation[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		missileCount = 10;
		missileUp=false;
	}

  void draw() {
	glColor3fv(siteColor);
	glTranslatef(siteLocation[0],siteLocation[1],siteLocation[2]);
	glutSolidCube(siteSize); //debug
	//glutSolidSphere(siteSize,siteSize,siteSize);
	if(missileUp)
		missile->draw();
  }

  void update(){
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glLoadIdentity();
	  glTranslatef(siteLocation[0],siteLocation[1],siteLocation[2]);
	  glGetFloatv(GL_MODELVIEW_MATRIX,TM);
	  glPopMatrix();
  }

  void checkForShip(GLfloat shipx, GLfloat shipy, GLfloat shipz, int siteNumber){ //siteNumber=0 => U.Missile else T.Missile
	  if(siteNumber==0)
		  detectionDistance = 3000.0;
	  else
		  detectionDistance = 6000.0;
	  currentShipDistance = sqrt(pow(shipx-TM[Tx],2)+pow(shipy-TM[Ty],2)+pow(shipz-TM[Tz],2));
	  if(currentShipDistance<=detectionDistance && missileCount!=0 && missileUp==false){
		  printf("FIRE ZE MISSILES!\n");
		  //fire missile
		  missile = new Missile(TM[Tx],TM[Ty],TM[Tz],siteNumber);
		  missileUp=true;
		  missileCount--;
	  }
	  if(missileUp)
		  missile->update(shipx,shipy,shipz);
  }

  int getMissileCount(){
	  return missileCount;
  }

	

GLfloat getX(){
	return TM[Tx];
}

GLfloat getY(){
	return TM[Ty];
}

GLfloat getZ(){
	return TM[Tz];
}

 
};