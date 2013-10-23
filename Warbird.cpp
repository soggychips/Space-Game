# ifndef __CONSTANTS3D__ 
# include "constants3D.h"
# define __CONSTANTS3D__
# endif

#include "ShipCamera.cpp"

extern void drawTriModel(int, float);
//extern void drawShipModel(int, float);

class Warbird { 

private:
	GLfloat TM[16];
	GLfloat viewMatrix[16];
	GLfloat location[3];
	GLfloat tempMatrix[16];
	ShipCamera * camera;
	int torpedoCount;
		
public:
	
	int modelListID;
	
	Warbird (GLfloat warbirdLocation[3]) { 
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(5000,1000,-5000);
		glRotatef(-45.0,0.0,1.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		glPopMatrix();
		resetTemp();
		camera = new ShipCamera(TM);
		//static GLfloat warpLocations[4][3] = {{0.0f,1500.0f,0.0f},{0.0f,1500.0f,0.0f},{0.0f,4500.0f,0.0f},{0.0f,2500.0f,0.0f}};
		torpedoCount = 30;
		modelListID=256;
		/*//drawShipModel(modelListID, 10.0f);    // create model's display list, scale it
		if(glIsList(modelListID))
			printf("list exists\n");
		else
			printf("List does not exist\n"); */
	}
	

	void draw(){
		//printf("warbird->draw()\n");
		glPushMatrix();
		glMultMatrixf(TM);
		/*glColor3f(1.0,0.0,0.0);
		glutSolidCone(60,160,30,30);
		glTranslatef(0,30,40);
		glColor3f(0.5,1.0,0.0);
		glutSolidSphere(40,20,20);*/
		//glCallList(modelListID);
		drawTriModel(modelListID,100.0f);
		glPopMatrix();
	}
	
	void update(){
		//printf("warbird->update()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(TM);
		glMultMatrixf(tempMatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		glPopMatrix();
		camera->updateView(TM);
		resetTemp();
	}

	
	void useShipCamera(){
		//printf("warbird->useShipCamera\n");
		camera->setView();
	}

	bool isTorpedoActive(){

	}

	void fire(){ //torpedo moves in the direction of the ship for the first 50 frames

	}

	void warp(GLfloat planetX, GLfloat planetY, GLfloat planetZ){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(planetX,planetY+1500.0,planetZ);
		glRotatef(90.0,1.0,0.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,TM);
		printTM();
		glPopMatrix();

	}
	
	void printTM(){ //for debugging
		printf("TM of ship after warp:\n");
		printf("%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n",TM[0],TM[4],TM[8],TM[12],TM[1],TM[5],TM[9],TM[13],TM[2],TM[6],TM[10],TM[14],TM[3],TM[7],TM[11],TM[15]);
		printf("\n"); 
	}

	
	void move(float direction){ //forward or backwards
		//printf("warbird->move()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(tempMatrix);
		glTranslatef(0.0,0.0,direction);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glPopMatrix();
	}
	
	void yaw(float direction){
		//printf("warbird->yaw()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(tempMatrix);
		glRotatef(direction,0.0,1.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glPopMatrix();
	}

	void roll(float direction){
		//printf("warbird->roll()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(tempMatrix);
		glRotatef(direction,0.0,0.0,1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glPopMatrix();
	}

	void pitch(float direction){
		//printf("warbird->pitch()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(tempMatrix);
		glRotatef(direction,1.0,0.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glPopMatrix();
	}

	void resetTemp(){
		//printf("warbird->resetTemp()\n");
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
		glPopMatrix();
	}



	GLfloat getX(){
		return TM[12];
	}

	GLfloat getY(){
		return TM[13];
	}

	GLfloat getZ(){
		return TM[14];
	}

};