# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

class PlanetCamera { //moving camera for ship attachment
  
	private:
		GLfloat view[16];
		GLfloat tempMatrix[16];
		GLfloat yOffset;
  		
		

  public:


	PlanetCamera (GLfloat planetMatrix[16], int planetNumber){
		//printf("Planet camera initialized!\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		switch(planetNumber){
			case 1:
				yOffset = 2000.0;
				break;
			case 5:
				yOffset = 2000.0;
				break;
			case 6:
				yOffset = 5000.0;
				break;
			case 12:
				yOffset = 3000.0;
				break;
			default:
				yOffset=0.0;
				break;
		}
		gluLookAt(
			planetMatrix[Tx], planetMatrix[Ty]+yOffset, planetMatrix[Tz],
			planetMatrix[Tx],planetMatrix[Ty],planetMatrix[Tz],
			0.0,0.0,1.0);
			//planetMatrix[Ux],planetMatrix[Uy],planetMatrix[Uz]); //or 0,0,+/-1.0?
		glGetFloatv(GL_MODELVIEW_MATRIX, view);
		glPopMatrix();
	}

  void updateView(GLfloat planetMatrix[16]) {
		//printf("camera->updateView()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(planetMatrix);
		glTranslatef(0.0,yOffset,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glLoadIdentity();
		gluLookAt(
			tempMatrix[Tx], tempMatrix[Ty], tempMatrix[Tz], // camera pos
			planetMatrix[Tx], planetMatrix[Ty], planetMatrix[Tz], // looking at
			0.0,0.0,1.0);
			//tempMatrix[Ux], tempMatrix[Uy], tempMatrix[Uz]); //up vector
			glGetFloatv(GL_MODELVIEW_MATRIX,view);
		//printview();
		glPopMatrix();

  }

  	void printview(){ //for debugging
		printf("Planet Camera View Matrix after update:\n");
		printf("%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n",view[0],view[4],view[8],view[12],view[1],view[5],view[9],view[13],view[2],view[6],view[10],view[14],view[3],view[7],view[11],view[15]);
		printf("\n"); 
	}

	void setView(){
		//printf("planetcamera->setView()\n");
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); 
		glMultMatrixf(view); //set camera
	}

	

 
};