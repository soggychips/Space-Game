# include <stdio.h> 
# include <string.h>
# include <cmath>
# include <cstdlib>

# ifndef __CONSTANTS3D__ 
# include "constants3D.h" 
# define __CONSTANTS3D__
# endif

#include "Planet.cpp"
#include "Warbird.cpp"
#include "MissileSite.cpp"
#include "drawTriModel.cpp"
//#include "shipModel.cpp"

// Function prototypes 
void resize(int, int);
void draw();
void KeyPressFunc(unsigned char, int, int);
bool smoothShading = true; 
void freeTexture(GLuint);
GLuint loadRawTexture(const char *, int, int);

//texture variables
int width = 41000, height = 41000;   // set texture's width and height values here
char * fileName = "star_texture.raw";  // set the texture file's name here
GLuint texture;


//set planet locations
GLfloat shipLocation[3] = {5000,1000,-5000};	

static GLfloat missileSiteLocation[2][3] = {{325.0f,0.0f,0.0f},		//------------------------------//U.Missile
											{0.0f,0.0f,105.0f}};	//------------------------------//T.Missile

static GLfloat missileSiteSize = 50.0f;
static GLfloat missileSiteColor[3] = {1.0f,0.0f,0.0f};

static GLfloat planetLocation[14][3] = {{0.0f,0.0f,0.0f},		//------------------------------//Ruber
										{4000.0f,0.0f,0.0f},	//------------------------------//Unum
										{325.0f,0.0f,0.0f},		//------------------------------//U.Missile
										{800.0f,0.0f,0.0f},		//------------------------------//U.1
										{1000.0f,0.0f,0.0f},	//------------------------------//U.2
										{-7000.0f,0.0f,0.0f},	//------------------------------//Duo
										{0.0f,0.0f,12000.0f},	//------------------------------//Tres
										{0.0f,0.0f,1800.0f},	//------------------------------//T.1
										{0.0f,0.0f,2000.0f},	//------------------------------//T.2
										{0.0f,0.0f,2300.0f},	//------------------------------//T.3
										{0.0f,0.0f,105.0f},		//------------------------------//T.Missile
										{0.0f,0.0f,2700.0f},	//------------------------------//T.4
										{0.0f,0.0f,-20000.0f},	//------------------------------//Quattuor
										{0.0f,0.0f,-1000.0f}};	//------------------------------//Q.1

//set radius for the planets															//**PLANET RADIUS**//
static GLfloat planetRadius[14] =		{2000.0f,											//Ruber
										300.0f, 50.0f, 50.0f, 50.0f,						//Unum,U.m,U.1-2
										400.0f,												//Duo
										800.0f, 50.0f, 50.0f, 80.0f, 50.0f, 100.0f,			//Tres,T.1-3,T.m,T.4
										500.0f, 100.0f};									//Quattuor,Q.1
//set color for the planets
static GLfloat red[3] = {1.0f,0.1f,0.1f};
static GLfloat green[3] = {0.0f,1.0f,0.0f};
static GLfloat blue[3] = {0.0f,0.0f,1.0f};
static GLfloat yellow[3] = {1.0f,0.84f,0.0f};
static GLfloat grey[3] = {0.5f,0.5f,0.5f};
static GLfloat purple[3] = {0.58f,0.0f,0.83f};
static GLfloat pink[3] = {1.0f,0.4f,0.7f};																										//**PLANET COLORS**//
static GLfloat planetColor[14][3] = {{1.0f,0.84f,0.0f},																							//Ruber
										{1.0f,0.5f,0.0f},{1.0f,0.0f,0.0f},{1.0f,0.4f,0.7f},{1.0f,0.4f,0.7f},									//Unum,U.m,U.1-2
										{0.0f,0.0f,1.0f},																						//Duo
										{0.0f,1.0f,0.0f},{1.0f,0.4f,0.7f},{1.0f,0.4f,0.7f},{1.0f,0.4f,0.7f},{1.0f,0.0f,0.0f},{1.0f,0.4f,0.7f},	//Tres,T.1-3,T.m,T.4
										{0.58f,0.0f,0.83f},{1.0f,0.4f,0.7f}};																	//Quattuor,Q.1

//set orbit angles for planets											//**PLANET ORBIT ANGLES**//
static GLfloat planetOrbitAngle[14] = {0.0,									//Ruber
										0.45,0.0,1.125,0.75,				//Unum,U.m,U.1-2
										0.225,								//Duo
										0.1125,0.75,0.5625,0.45,0.0,0.3214,	//Tres,T.1-3,T.m,T.4
										0.0750,0.45};						//Quattuor,Q.1

GLfloat warbirdLocation[3] = {5000,1000,-5000};
const int  windowWidth = 800, windowHeight = 600;
const int windowX = 50, windowY = 50;  
Planet * planet[14];
MissileSite * missileSite[2];
Warbird * warbird;
float view[3][16];
int currentView = 0;
int base = 0;
bool firstUpdate = 1;
int parentWindow, playWindow, topWindow, dataWindow;
int timerDelay = 40, frameCount = 0, intervalTimerCalls = 0, timer=0;
int dataWindowHeight, dataWindowWidth;
// strings for information data display
const int nMsg = 14, messageLength = 22;
char message[nMsg][messageLength];
float x = 6000.0f;
float z = -6000.0f;
float lx = -6000.0f;
float lz = 6000.0f;
float angle = 0.0f;
char levelName[10];
int currentWarp = 0;
int currentPlanetView = 0;
bool warpView = false;
bool keyDown[256] = {false};
bool keyMod[256] = {false};




void init(void) {
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void initView() {
   glMatrixMode(GL_MODELVIEW);
   // create a view
   glPushMatrix();
   glLoadIdentity();
   gluLookAt(
      0.0, 0.0, 40000.0,    // eye location
      0.0, 0.0,   0.0,    // center location
      0.0, 1.0,   0.0);   // up vector
   glGetFloatv(GL_MODELVIEW_MATRIX, view[0]); //front view
   glLoadIdentity();
   gluLookAt(
      0.0, 40000.0, 0.0,    // eye location
      0.0, 0.0,   0.0,    // center location
      0.0, 0.0,  -1.0);   // up vector
   glGetFloatv(GL_MODELVIEW_MATRIX, view[2]); //top view
   glPopMatrix();
}

// Create character display lists for text display.
void initTextList() {
   for(int i = 0; i < 256; i++) {  
	   glNewList(base + i, GL_COMPILE);
	   glutBitmapCharacter(GLUT_BITMAP_8_BY_13, i);
	   glEndList(); }
   glListBase(base);
   for(int i = 0; i < nMsg; i++) sprintf(message[i]," ");
   sprintf(levelName,"Ace");
   sprintf(message[0],"Level %s     25 fps",levelName);
   sprintf(message[2], "Camera:");
   sprintf(message[13], "Jake Cohen");
   }

// Show text information.
void showText(int x, int y, int z) {
   glDisable(GL_LIGHTING);
   glColor3f(0.0f,0.0f,0.0f); 
   int yOffset = dataWindowHeight;  
   for(int i = 0; i < nMsg; i++) {
      yOffset -= 40;
      glRasterPos3i(x, yOffset, z);  
      glCallLists(strlen((char *) message[i]), GL_BYTE, (char *) message[i]);
      }
   glEnable(GL_LIGHTING);
   }

//free texture
void freeTexture( GLuint texture ) {  glDeleteTextures( 1, &texture ); }

//load texture
GLuint loadRawTexture( const char * filename, int width, int height){
	unsigned char * data;
	short * color;
	FILE * file;
	int readResult;

	// open texture data
	file = fopen( filename, "rb" );
	if ( file == NULL ) {
		printf("File %s can't be opened\n");
		return 0;
	}
  // allocate buffer -- 3 bytes / texel -- rgb
	data = (unsigned char *) malloc( width * height * 3 );
  // read texture data
	readResult = fread( data, width * height * 3, 1, file );
	if (readResult != 1) {
		printf("File %s was not read correctly\n");
		return 0; 
	}
	fclose( file );
  
	glGenTextures( 1, &texture ); // generate the texture with the loaded data
	glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture  
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
	// set texture parameters
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	// generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data ); //free the texture
	return texture; //return whether it was successfull
}


// set and redraw all the subWindows
 void redisplayAll() {
  glutSetWindow(parentWindow);  
  glutPostRedisplay();
  glutSetWindow(topWindow);
  glutPostRedisplay();
  glutSetWindow(dataWindow);   
  glutPostRedisplay(); 
  glutSetWindow(playWindow);
  glutPostRedisplay();
  }


void updateAngle(void){ //update function
	for(int j=0;j<14;j++){
		GLfloat currentAngle = 0.0, orbitAngle = 0.0;
		currentAngle = planet[j]->getCurrentAngle();
		orbitAngle = currentAngle + planetOrbitAngle[j];
		if (orbitAngle >= 360.0) 
			orbitAngle = 0.0;
		planet[j]->setAngle(orbitAngle);
		planet[j]->update();
	}
	warbird->update();
	missileSite[0]->checkForShip(warbird->getX(),warbird->getY(),warbird->getZ(),0);
	missileSite[1]->checkForShip(warbird->getX(),warbird->getY(),warbird->getZ(),1);
	missileSite[0]->update();
	missileSite[1]->update();
	redisplayAll();
 }
  
   
// Estimate FPS, use for fixed interval timer driven animation
void intervalTimer (int i) { 
   glutTimerFunc(timerDelay, intervalTimer, 1);
   // compute frames / second
   intervalTimerCalls++;
   if (intervalTimerCalls * timerDelay >= 1000) { 
	  sprintf(message[0],"Level %s  %5d fps",levelName, frameCount);
      intervalTimerCalls = frameCount = 0; 
	  if (currentView == 0)
		sprintf(message[2], "Camera: Front");
	  else	
		sprintf(message[2], "Camera: Ship");
      sprintf(message[5], "Warbird");
	  sprintf(message[6],  "%4.1f %4.1f %4.1f", warbird->getX(), warbird->getY(), warbird->getZ());
	  sprintf(message[8], "U. Missile");
	  sprintf(message[9],  "%4.1f %4.1f %4.1f", planet[1]->getX(), planet[1]->getY(), planet[1]->getZ());
	  sprintf(message[11], "T. Missile");
	  sprintf(message[12],  "%4.1f %4.1f %4.1f", planet[9]->getX(), planet[9]->getY(), planet[9]->getZ());
      glutSetWindow(dataWindow);
      glutPostRedisplay(); 
    }
   if(keyMod[GLUT_ACTIVE_CTRL]){
	   if(keyDown[GLUT_KEY_UP]){
		   warbird->pitch(1.0);
	   }
	   if(keyDown[GLUT_KEY_DOWN]){
		   warbird->pitch(-1.0);
	   }
	   if(keyDown[GLUT_KEY_LEFT]){
		   warbird->roll(1.0);
	   }
	   if(keyDown[GLUT_KEY_RIGHT]){
		   warbird->roll(-1.0);
	   }
   }
   if(!keyMod[GLUT_ACTIVE_CTRL]){
	   if(keyDown[GLUT_KEY_UP]){
		   warbird->move(10.0);
	   }
	   if(keyDown[GLUT_KEY_DOWN]){
		   warbird->move(-10.0);
	   }
	   if(keyDown[GLUT_KEY_LEFT]){
		   warbird->yaw(1.0);
	   }
	   if(keyDown[GLUT_KEY_RIGHT]){
		   warbird->yaw(-1.0);
	   }
   }
			
	updateAngle();  // fixed interval timer
}

void drawScene(){
	warbird->draw();
	//draw the Planets:
	glPushMatrix(); //create a "copy" of the original modelview
		planet[0]->draw();
		planet[1]->draw();
		glPushMatrix(); //missile + moons
			missileSite[0] ->draw();
			//planet[2]->draw(); ^ replaced with missileSite
			glPopMatrix();
		glPushMatrix();
			planet[3]->draw();
			glPopMatrix();
		glPushMatrix();
			planet[4]->draw();
			glPopMatrix();
		glPopMatrix();
	glPushMatrix(); //planets
		planet[5]->draw();
		glPopMatrix();
	glPushMatrix();
		planet[6]->draw();
		glPushMatrix(); //moons + missile
			planet[7]->draw();
			glPopMatrix();
		glPushMatrix();
			planet[8]->draw();
			glPopMatrix();
		glPushMatrix();
			planet[9]->draw();
			missileSite[1]->draw();
			//planet[10]->draw(); ^ replaced with missileSite
			glPopMatrix();
		glPushMatrix();
			planet[11]->draw();
			glPopMatrix();
		glPopMatrix();
	glPushMatrix();
		planet[12]->draw();
		glPushMatrix();
			planet[13]->draw();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	// draw a texture on a quad
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texture );
	glColor3f(1.0, 1.0, 1.0);  // set white color, want texture colors
	// texture coordinates counter-clockwise from (0,1) to (1,1) 
	// vertices are changed to make texture appear right side up.
	glBegin( GL_QUADS );
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-width/2, -height/2, -width);
	glTexCoord2d(0.0,0.0); glVertex3d(-width/2,  height/2, -width);
	glTexCoord2d(1.0,0.0); glVertex3d( width/2,  height/2, -width);
	glTexCoord2d(1.0,1.0); glVertex3d( width/2, -height/2, -width);
	glEnd();
	glDisable(GL_TEXTURE_2D );
	
	glutSwapBuffers();
}


// callback, responds to window resize events
void resizeParent(int width, int height) {
    // don't let window resize -- restore postion and size
    if (width != windowWidth && height != windowHeight) {
      glutPositionWindow(windowX, windowY);
      glutReshapeWindow(windowWidth, windowHeight);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width, -height/2, height, -1000, 1000.0);
}
    
// Respond to window resize events
void resizePlay(int width, int height) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (float)width / (float)height, 1.0, 80000.0);
   }
   
void resizeTop(int width, int height) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (float)width / (float)height, 1.0, 80000.0);
   }   

void resizeData(int width, int height) {
   dataWindowHeight = height;
   dataWindowWidth = width;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-width/2, width, -height/2, height, -100, 1000.0);
   }
 

void initWindow(float r, float g, float b, float a) {
   // light values
   static GLfloat diffuse[4] = { 0.0, 0.3, 0.3, 1.0 };
   static GLfloat ambient[4] = { 0.6, 0.6, 0.6, 1.0 };
   static GLfloat lightPos[4] ={ 1.0, 1.0, 1.0, 0.0 };  // ambient light
    // Clear the color and depth buffers
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
    // set light materials
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    }
  
void drawParent(void) {
   glClearColor(0.5, 0.5, 0.5, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSwapBuffers();
   }      


void drawPlay(void) { 
	glutSetWindow(playWindow);
	frameCount++;  // for fps estimation
	initWindow(0.0f, 0.0f, 0.0f, 1.0f);
	if(warpView==true){
		printf("warpView on");
		switch(currentWarp){
			case 0:
				planet[12]->usePlanetCamera();
				break;
			case 1:
				planet[1]->usePlanetCamera();
				break;
			case 2:
				planet[5]->usePlanetCamera();
				break;
			case 3:
				planet[6]->usePlanetCamera();
				break;
		}
	}else if(currentView==0){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); 
		glMultMatrixf(view[currentView]); //set camera
	}else if(currentView==1){
		warbird->useShipCamera();
	}
	drawScene(); 
}

void drawTop(void) {   
	glutSetWindow(topWindow);
	initWindow(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
	glLoadMatrixf(view[2]); //set camera
	drawScene();
}

void drawData(void) {
  glutSetWindow(dataWindow);
  initWindow(0.6f, 0.6f, 0.9f, 0.0f);  
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();
  showText(-80, 40, 0);  
  glutSwapBuffers();
  }

void reshape(int w, int h) {
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 80000.0);
}

void keyboard(unsigned char key, int u2, int u3) {
	int mod = glutGetModifiers();
	switch(key) {
		case 'w':
			warpView = true;
			switch(currentWarp){
			case 0:
				warbird->warp(planet[1]->getX(),planet[1]->getY(),planet[1]->getZ());
				glutPostRedisplay();
				break;
			case 1:
				warbird->warp(planet[5]->getX(),planet[5]->getY(),planet[5]->getZ());
				glutPostRedisplay();
				break;
			case 2:
				warbird->warp(planet[6]->getX(),planet[6]->getY(),planet[6]->getZ());
				glutPostRedisplay();
				break;
			case 3:
				warbird->warp(planet[12]->getX(),planet[12]->getY(),planet[12]->getZ());
				glutPostRedisplay();
				break;
		}
			currentWarp++;
			if(currentWarp>3)
				currentWarp=0;
			currentView=0; 
			break;
		case 'p':
			warpView=true;
			currentWarp++;
			if(currentWarp>3)
				currentWarp=0;
			break;
		case 'v':
			warpView=false;
			currentView++;
			if(currentView>1)
				currentView=0;
			printf("view: %d\n",currentView);
			glutPostRedisplay();
			break;
		case 't':
			timer++;
			if(timer>=4)
				timer=0;
			if(timer==0){
				timerDelay=40;
				sprintf(levelName,"Ace");
			}else if(timer==1){	
				timerDelay = 100;
				sprintf(levelName,"Pilot");
			}else if(timer==2){
				timerDelay = 250;
				sprintf(levelName,"Trainee");
			}else if(timer == 3){
				timerDelay = 500;
				sprintf(levelName,"Debug");
			}
			break;
		case 'q':
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	keyDown[key] = true;
	int testMod = glutGetModifiers();
	if(testMod == GLUT_ACTIVE_CTRL){
		keyMod[GLUT_ACTIVE_CTRL] = true;
	}
}

void releaseKey(int key, int xxx, int yyy) {
	keyDown[key] = false;
	keyMod[GLUT_ACTIVE_CTRL] = false;;
}


// Program entry


int main(int  argc, char *argv[])  {
   printf("main \n");
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(windowWidth, windowHeight);
   printf("make parent window \n");
   parentWindow = glutCreateWindow("Ruber Solar System");
   glutPositionWindow(windowX, windowY);
   // set glut callback functions
   glutReshapeFunc(resizeParent);
   glutDisplayFunc(drawParent);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(processSpecialKeys);
   glutIgnoreKeyRepeat(1);
   glutSpecialUpFunc(releaseKey);
   glutIdleFunc(NULL);  
   glutTimerFunc(timerDelay, intervalTimer, 1);
   // make play window
   printf("make play window \n");
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   playWindow = glutCreateSubWindow(parentWindow, 10, 10, 580, 580);
   // set glut callback functions for playWindow
   printf("set callbacks \n");
   glutReshapeFunc(resizePlay);
   glutDisplayFunc(drawPlay); 
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(processSpecialKeys);
   glutIgnoreKeyRepeat(1);
   glutSpecialUpFunc(releaseKey);
   //make top down window
   printf("make top window \n");
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   topWindow = glutCreateSubWindow(parentWindow, 605, 10, 185, 185);
   glutReshapeFunc(resizeTop);
   glutDisplayFunc(drawTop);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(processSpecialKeys);
   glutIgnoreKeyRepeat(1);
   glutSpecialUpFunc(releaseKey);
   // make data window
   printf("make data window \n");
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   dataWindow = glutCreateSubWindow(parentWindow, 605, 205, 185, 385);
   glutReshapeFunc(resizeData);
   glutDisplayFunc(drawData); 
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(processSpecialKeys);
   glutIgnoreKeyRepeat(1);
   glutSpecialUpFunc(releaseKey);
   // create popup menu in data window
   printf("initTextList \n");
   initTextList();  // create character display list
   init();
   initView();
   //initialize planets
   for(int i=0;i<14;i++){
	   planet[i] = new Planet(planetRadius[i],planetColor[i],planetLocation[i],planetOrbitAngle[i]);
	   planet[i]->createCamera(i);
   }
   for(int i=0;i<2;i++){
	   missileSite[i] = new MissileSite(missileSiteSize,missileSiteColor,missileSiteLocation[i]);
   }
   warbird = new Warbird(warbirdLocation);
   printf("glutMainLoop \n");
   glutMainLoop();
   return (0);
   }