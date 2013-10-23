# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

class ShipCamera { //moving camera for ship attachment
  
	private:
		GLfloat view[16];
		GLfloat tempMatrix[16];
  		
		

  public:


	ShipCamera (GLfloat shipMatrix[16]){
		printf("Ship camera initialized!\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(
			shipMatrix[Tx], shipMatrix[Ty]+500.0, shipMatrix[Tz]-1000.0,
			shipMatrix[Tx]+shipMatrix[Ax],shipMatrix[Ty]+shipMatrix[Ay],shipMatrix[Tz]+shipMatrix[Az],
			shipMatrix[Ux],shipMatrix[Uy],shipMatrix[Uz]);
		glGetFloatv(GL_MODELVIEW_MATRIX, view);
		glPopMatrix();
	}

  void updateView(GLfloat shipMatrix[16]) {
		//printf("camera->updateView()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(shipMatrix);
		glTranslatef(0.0,500.0,-1000.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glLoadIdentity();
		gluLookAt(
			tempMatrix[Tx], tempMatrix[Ty], tempMatrix[Tz], // camera pos
			shipMatrix[Tx]+shipMatrix[Ax], shipMatrix[Ty]+shipMatrix[Ay], shipMatrix[Tz]+shipMatrix[Az], // looking at
			tempMatrix[Ux], tempMatrix[Uy], tempMatrix[Uz]); //up vector
			glGetFloatv(GL_MODELVIEW_MATRIX,view);
		//printview();
		glPopMatrix();

  }

  	void printview(){ //for debugging
		printf("Camera View Matrix after update:\n");
		printf("%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n",view[0],view[4],view[8],view[12],view[1],view[5],view[9],view[13],view[2],view[6],view[10],view[14],view[3],view[7],view[11],view[15]);
		printf("\n"); 
	}

	void setView(){
		//printf("camera->setView()\n");
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); 
		glMultMatrixf(view); //set camera
	}

	

 
};