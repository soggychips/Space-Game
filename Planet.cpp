# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

#include "PlanetCamera.cpp"

class Planet { 
  
	private:
  		GLfloat orbitIncrement; 
		GLfloat currentAngle;
  		GLfloat pColor[3], pLocation[3];
  		GLfloat pRadius;
  		GLfloat TM[16]; //transformation matrix
		GLfloat viewMatrix[16], inverseMatrix[16];
		PlanetCamera * camera;
		

  public:

	Planet (GLdouble planetRadius, GLfloat planetColor[3], GLfloat planetLocation[3], GLfloat orbitAngle) {
		for(int i = 0; i<3; i++) {
			pColor[i] = planetColor[i];
			pLocation[i] = planetLocation[i];
			}
		orbitIncrement = orbitAngle;
		pRadius = planetRadius;
		currentAngle = 0.0;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(planetLocation[0],planetLocation[1],planetLocation[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
	}

  void draw() {
	glColor3fv(pColor);
	glRotatef(currentAngle,0.0,1.0,0.0);
	glTranslatef(pLocation[0],pLocation[1],pLocation[2]);
	glutSolidSphere(pRadius,pRadius,pRadius);
  }

  void update(){
	//printf("planet->update()\n");
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(currentAngle,0.0,1.0,0.0);
	glTranslatef(pLocation[0],pLocation[1],pLocation[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX,TM);
	glPopMatrix();
	camera->updateView(TM);
  }

  void orbit(){

  }

  void usePlanetCamera(){
		printf("warbird->usePlanetCamera\n");
		camera->setView();
	}

	void setTM(GLfloat planetMatrix[16]){
		for(int i=0;i<16;i++){
			TM[i] = planetMatrix[i];
		}
	}

	void createCamera(int pNumber){
		camera = new PlanetCamera(TM, pNumber);
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

GLfloat getOrbitAngle(){
	return orbitIncrement;
}

GLfloat getCurrentAngle(){
	return currentAngle;
}

void setAngle(GLfloat newAngle){
	currentAngle = newAngle;
}

 
};