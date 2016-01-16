

/*

// Computer Graphics course VUA 2008 Project

// Made by: Klaas Andries de Graaf


Controls:
- Mouse and Numpad (+ and - keys also) are used for camera en character movement
- space bar for starting and pausing animations


Game Objectives:
- Collect the transparant cube as fast as possible with the cat character. 
- The cube is hidden near the cats
- Results are displayed in SToud/console window

*/



#include <GL/glut.h>

#include <stdio.h>

#include <util/glutil.h>

#include <math.h>

#include <string.h> 

#include <project/modelloader.h> 

#include <project/textureloader.h> 


int sub_menu2; //reshape

int sub_menu3; //shading


int i;



float theta = 0.00;


double currentTimeWalk = 0.0;
double elapsedTimeWalk = 0.0;
double storedTimeWalk = 0.0;

float currentGameTime = 0.0;
float elapsedGameTime = 0.0;
float storedGameTime = 0.0;

int level = 0;


double currentTime = 0.0;
double storedTime = 0.0;
double elapsedTime = 0.0;


double currentTimeCharacter = 0.0;
double elapsedTimeCharacter = 0.0;
double storedTimeCharacter = 0.0;
float thetaCharacter = 0.00; //theta for main character

int hideCube = 1;

int reshape = 1; //aspect ratio is default 4:3 (800*600/1024*768)

GLfloat cubeVertices[25][3] = 
{{-0.5,-0.5,-0.5}, {-0.5,0.5,-0.5}, {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, //back side
{0.5,0.5,-0.5}, {-0.5,0.5,-0.5}, {-0.5,0.5,0.5}, {0.5,0.5,0.5}, //top side
{-0.5,-0.5,-0.5}, {-0.5,-0.5,0.5}, {-0.5,0.5,0.5}, {-0.5,0.5,-0.5},  //left side
{0.5,-0.5,-0.5}, {0.5,0.5,-0.5}, {0.5,0.5,0.5}, {0.5,-0.5,0.5}, //right side
{-0.5,-0.5,0.5}, {0.5,-0.5,0.5}, {0.5,0.5,0.5}, {-0.5,0.5,0.5}, //front side
{-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}}; //bottom side

GLfloat cubeColors[24][4] = {{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},
{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, 
{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0},
{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0},
{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0},
{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}};

 //transparant cube
GLfloat TransparantCubeColors[24][4] = {{0.0,0.0,0.0,0.4}, {0.0,1.0,0.0,0.4}, {1.0,1.0,0.0,0.4},{1.0,0.0,0.0,0.4},
{1.0,1.0,0.0,0.4}, {0.0,1.0,0.0,0.4}, {0.0,1.0,1.0,0.4}, {1.0,1.0,1.0,0.4}, 
{0.0,0.0,0.0,0.4}, {0.0,0.0,1.0,0.4}, {0.0,1.0,1.0,0.4}, {0.0,1.0,0.0,0.4},
{1.0,0.0,0.0,0.4}, {1.0,1.0,0.0,0.4}, {1.0,1.0,1.0,0.4}, {1.0,0.0,1.0,0.4},
{0.0,0.0,1.0,0.4}, {1.0,0.0,1.0,0.4}, {1.0,1.0,1.0,0.4}, {0.0,1.0,1.0,0.4},
{0.0,0.0,0.0,0.4}, {1.0,0.0,0.0,0.4}, {0.0,0.0,1.0,0.4}, {1.0,0.0,1.0,0.4}};

GLfloat cubeNormals[24][3] = 
{{0.0,0.0,-1.0},{0.0,0.0,-1.0},{0.0,0.0,-1.0},{0.0,0.0,-1.0}, //back side
{0.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,1.0,0.0}, //top side
{-1.0,0.0,0.0},{-1.0,0.0,0.0},{-1.0,0.0,0.0},{-1.0,0.0,0.0}, //left side
{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,0.0,0.0}, //right side
{0.0,0.0,1.0},{0.0,0.0,1.0},{0.0,0.0,1.0},{0.0,0.0,1.0}, //front side
{0.0,-1.0,0.0},{0.0,-1.0,0.0},{0.0,-1.0,0.0},{0.0,-1.0,0.0}};//bottom side


GLubyte cubeIndices[]={
0,1,2,3, 4,5,6,7, 8,9,10,11,
12,13,14,15, 16,17,18,19, 20,21,22,23
};

//light0 properties
GLfloat light0_pos[] = {1.0, 2.0, -3.0, 1.0};
GLfloat light0_dir[] = {0.0, 0.5, -1.0, 0.0};
GLfloat diffuse0[] = {0.5, 0.5, 0.5, 1.0};
GLfloat ambient0[] = {0.4, 0.4, 0.4, 1.0};
GLfloat specular0[] = {0.5, 0.5	, 0.5, 1.0};

//light1 properties (red)
GLfloat light1_pos[] = {-3.0, 0.5, -0.5, 1.0};
GLfloat specular1[] = {1.0, 0.0	, 0.0, 1.0};
GLfloat light1_dir[] = {1.0, 2.0, 3.0, 0.0};
GLfloat diffuse1[] = {1.0, 0.0, 0.0, 1.0};
GLfloat ambient1[] = {0.0, 0.0, 0.0, 0.0};


//light2 properties
GLfloat light2_pos[] = {1.0, 0.05, 0.0, 1.0};
GLfloat specular2[] = {0.0, 1.0	, 0.0, 1.0};
GLfloat light2_dir[] = {1.0, 2.0, 3.0, 0.0};
GLfloat diffuse2[] = {0.0, 1.0, 0.0, 1.0};
GLfloat ambient2[] = {0.0, 0.0, 0.0, 0.0};


//material properties
GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat diffuse[] = {0.2, 0.2, 0.2, 1.0};
GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};
GLfloat shininess = 10.0;
GLfloat emission[]={0.0, 0.0, 0.0, 1.0};


//variables for locust movement
float locustMovementX = 0.00, locustMovementZ = 0.00, locustTheta = 0.00;
int locustDirection = 0;

double currentTimeLocust = 0.0;
double storedTimeLocust = 0.0;
double elapsedTimeLocust = 0.0;

//define integer names for cat model parts in display lists
#define CAT_BODY 1
#define CAT_EYE_LEFT 2
#define CAT_EYE_RIGHT 3
#define CAT_HAND_LEFT 4
#define CAT_HAND_RIGHT 5
#define CAT_LEG_LEFT 6
#define CAT_LEG_RIGHT 7
#define CAT_NOSE 8
#define CAT_TAIL 9
#define CAT_TEETH 10
#define CAT_WHISKERS 11


//define integer names for locust model parts in display lists
#define LOCUST_ANTENNAE 12
#define LOCUST_BODY 13
#define LOCUST_EYES 14
#define LOCUST_HEAD 15
#define LOCUST_LEG_BACK_LEFT_LOWER 16
#define LOCUST_LEG_BACK_LEFT_UPPER 17
#define LOCUST_LEG_BACK_RIGHT_LOWER 18
#define LOCUST_LEG_BACK_RIGHT_UPPER 19
#define LOCUST_LEG_FRONT_LEFT 21
#define LOCUST_LEG_FRONT_RIGHT 22
#define LOCUST_LEG_MIDDLE_LEFT 23
#define LOCUST_LEG_MIDDLE_RIGHT 24
#define LOCUST_MOUTH 25
 
//define integer names for other models in display lists
#define GROUND_ID 26
#define CUBE_ID 27



//define integer names for textured cat model parts in display lists
#define TEX_CAT_BODY 29
#define TEX_CAT_EYE_LEFT 30
#define TEX_CAT_EYE_RIGHT 31
#define TEX_CAT_HAND_LEFT 32
#define TEX_CAT_HAND_RIGHT 33
#define TEX_CAT_LEG_LEFT 34
#define TEX_CAT_LEG_RIGHT 35
#define TEX_CAT_NOSE 36
#define TEX_CAT_TAIL 37
#define TEX_CAT_TEETH 38
#define TEX_CAT_WHISKERS 39


#define FLAT1 40
#define FLAT2 41
#define FLAT3 42
#define FLAT4 43


//define integer names for textures
#define TEXTURE_GROUND 1
#define TEXTURE_BRICKLOGOS 2
#define TEXTURE_BRICKWINDOW 3
#define TEXTURE_SKYSCRAPER 4
#define TEXTURE_SKYSCRAPER2 5

int spacestop = 0; //used for assignement evaluation


int mousemoveInitx = 0;
int mousemoveInity = 0;
int mousemovex = 0;
int mousemovey = 0;
int mousemove = 1; //variable for checking if to move mouse with left mouse butten (instead of left and middle)

int mainCharacterRotate = 0;


GLfloat viewer[3] = {
0.0 , 0.5, 5.0
};

GLfloat lookat[3] = {
0.0 , -0.95, 0.5
};

int walk = 0;

void game()
{
		//game data
		currentGameTime = Wallclock(); // from glutil.h (VU-made)

		elapsedGameTime = currentGameTime - storedGameTime;
		
		storedGameTime = currentGameTime;

		if (level == 0)
		{
			printf("Controls: \n");
			printf("- Mouse and Numpad (+ and - keys also) are used for camera en character movement \n");
			printf("- space bar for starting and pausing animations \n \n");
			printf("Game Objectives: \n");
			printf("- Collect the transparant cube as fast as possible.  \n");
			printf("- The cube is hidden near the cats \n");

			storedGameTime = Wallclock();
			level++;
		}
		
		if (level == 1)
		{
			if ((lookat[0] < -5.75 && lookat[2] < -8.25) && (lookat[0] > -6.75))
			{
					printf("LEVEL 1 COMLETED IN : %f  seconds\n", +elapsedGameTime );
					level++;
					printf("LEVEL %i BEGIN \n", level );
			}
		}

		if (level == 2)
		{
			if ((lookat[0] > 8.0 && lookat[2] > 8.6) && (lookat[0] < 9.00))
			{
					printf("LEVEL 2 COMLETED IN : %f  seconds\n", +elapsedGameTime );
					printf("GAME COMPLETED \n", level );
					level = 1;

					elapsedGameTime = 0.0;
					
			}
		}
}



void keyboard(unsigned char key, int x, int y)
{

	if( key == 'q' || key == 'Q' || key == 27  )
		{
			exit(0);
		}


	if(!(key == 'q' ||	key == 'Q'  ||	key == 27   ||	key == ' '  ))
		{
		}
	if(key == ' ')
		{
			spacestop++;

			if(fmod(spacestop, 2) == 1)
			{
				printf("====>Hammertime!!<==== \t \n");
			}

			//store new time for cube rotation axis calculation
			storedTime = Wallclock(); // from glutil.h (VU-made)

			//store new time for locust movement
			storedTimeLocust = Wallclock(); // from glutil.h (VU-made)

			storedTimeCharacter = Wallclock();

			
		
		}

	if(fmod(spacestop, 2) == 1)
	{
		if(key == '4') if (viewer[0] > -9.90) {viewer[0] -= 0.1; lookat[0] -= 0.1; mainCharacterRotate = 90; walk = 1; elapsedTimeWalk = 0;} //move camera and lookat left
		if(key == '6') if (viewer[0] < 9.90) {viewer[0] += 0.1; lookat[0] += 0.1; mainCharacterRotate = 270; walk = 1; elapsedTimeWalk = 0;} //move camera and lookat right
 
		if(key == '8') if (viewer[2] > -4.80) {viewer[2] -= 0.1; lookat[2] -= 0.1; mainCharacterRotate = 0; walk = 1; elapsedTimeWalk = 0;} //move camera and lookat forward
		if(key == '2') if (viewer[2] < 14.40) {viewer[2] += 0.1; lookat[2] += 0.1; mainCharacterRotate = 180; walk = 1; elapsedTimeWalk = 0;} //move camera and lookat backward


		if(key == '+') if(viewer[1] < 15.00) {viewer[1] += 0.1;} //move camera and lookat up
		if(key == '-') if(viewer[1] > -0.30) {viewer[1] -= 0.1;} //move camera and lookat down

		//timer functie bouwen!


		if(key == '5') { viewer[0] = 0.0 ;viewer[1] = 0.5; viewer[2] =  5.0; lookat[0] = 0.0 ; lookat[1] =  -0.95; lookat[2] =  0.5;} //reset camera and lookat
		if(key == 'r') { viewer[0] = 0.0 ;viewer[1] = 0.5; viewer[2] =  5.0; lookat[0] = 0.0 ; lookat[1] =  -0.95; lookat[2] =  0.5;} //reset camera and lookat
	}
}



void mouse(int btn,int btn_state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON&&btn_state==GLUT_DOWN)
	{
		mousemoveInitx = x;
		mousemoveInity = y;

		mousemove = 1;
	} 



	if(btn==GLUT_MIDDLE_BUTTON&&btn_state==GLUT_DOWN)
	{
		
		mousemove = 0; //dont move camera by mouse
	} 

	glutPostRedisplay(); 

}


void mouse_move(int x,int y)

{
	

	if (mousemove == 1)
	{
		mousemovex = (mousemovex + (x - mousemoveInitx) / 30);
		mousemovey = (mousemovey + (mousemoveInity - y) / 30);
	}


}


void top_menu(int id)
{
	if (id==1) hideCube++;
	if (id==2) exit(0);
	
}

void reshape_menu(int id)
{
	if (id==1) reshape = 1;
	if (id==2) reshape = 2;
	if (id==3) reshape = 3;
	if (id==4) reshape = 4;
}

void shade_menu(int id)

{

	if (id==1) glShadeModel(GL_SMOOTH);

	if (id==2) glShadeModel(GL_FLAT);

}


void drawLocust()

{
	
	glCallList(LOCUST_ANTENNAE);
	glCallList(LOCUST_BODY);
	glCallList(LOCUST_EYES);
	glCallList(LOCUST_HEAD);
	glCallList(LOCUST_LEG_BACK_LEFT_LOWER);
	glCallList(LOCUST_LEG_BACK_LEFT_UPPER);
	glCallList(LOCUST_LEG_BACK_RIGHT_LOWER);
	glCallList(LOCUST_LEG_BACK_RIGHT_UPPER);
	glCallList(LOCUST_LEG_FRONT_LEFT);
	glCallList(LOCUST_LEG_FRONT_RIGHT);
	glCallList(LOCUST_LEG_MIDDLE_LEFT);
	glCallList(LOCUST_LEG_MIDDLE_RIGHT);
	glCallList(LOCUST_MOUTH);

}
float walktheta = 0.00;

void drawTextureCat()
{
			glCallList(TEX_CAT_BODY);
			glCallList(TEX_CAT_EYE_LEFT);
			glCallList(TEX_CAT_EYE_RIGHT);
			glCallList(TEX_CAT_HAND_LEFT);
			glCallList(TEX_CAT_HAND_RIGHT);
			glCallList(TEX_CAT_LEG_RIGHT);
			glCallList(TEX_CAT_LEG_LEFT);
			glCallList(TEX_CAT_NOSE);
			glCallList(TEX_CAT_TAIL);
			glCallList(TEX_CAT_TEETH);
			glCallList(TEX_CAT_WHISKERS);

}

void drawCat(int animate)
{


			glCallList(CAT_BODY);
			glCallList(CAT_EYE_LEFT);
			glCallList(CAT_EYE_RIGHT);
			glCallList(CAT_HAND_LEFT);
			glCallList(CAT_HAND_RIGHT);

			//move feet

		if (animate == 1)
		{
			walktheta = theta;

			if (fmod(walktheta, 120) < 30)
			{
				glRotatef(fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_RIGHT);
				glRotatef(-fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}
			else if (fmod(walktheta, 120) < 60)
			{
				glRotatef(30 - fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_RIGHT);
				glRotatef(-(30 - fmod(walktheta, 30)), 1.0, 0.0, 0.0);
			}
			else if (fmod(walktheta, 120) < 90)
			{
				glRotatef(-fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_RIGHT);
				glRotatef(fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}
			else
			{
				glRotatef(-(30 - fmod(walktheta, 30)), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_RIGHT);
				glRotatef(30 - fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}



			if (fmod(walktheta, 120) < 30)
			{
				glRotatef(-fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_LEFT);
				glRotatef(fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}
			else if (fmod(walktheta, 120) < 60)
			{
				glRotatef(-(30 - fmod(walktheta, 30)), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_LEFT);
				glRotatef(30 - fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}
			else if (fmod(walktheta, 120) < 90)
			{
				glRotatef(fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_LEFT);
				glRotatef(-fmod(walktheta, 30), 1.0, 0.0, 0.0);
			}
			else
			{
				glRotatef(30 - fmod(walktheta, 30), 1.0, 0.0, 0.0);
					glCallList(CAT_LEG_LEFT);
				glRotatef(-(30 - fmod(walktheta, 30)), 1.0, 0.0, 0.0);
			}
		
		} 
		else
		{
					glCallList(CAT_LEG_RIGHT);
					glCallList(CAT_LEG_LEFT);

		}



			glCallList(CAT_NOSE);
			glCallList(CAT_TAIL);
			glCallList(CAT_TEETH);
			glCallList(CAT_WHISKERS);




}




void drawGroundSquare()

{
	glCallList(GROUND_ID);
}


void loadGroundSquare() //load ground vars for display list
{
	
	glNewList(GROUND_ID, GL_COMPILE); //create new display list for ground square

		glMatrixMode(GL_TEXTURE); //initialise texture matrix mode
		glEnable(GL_TEXTURE_2D);

		glColor4f(1.0, 1.0, 1.0, 1.0);

		glBindTexture(GL_TEXTURE_2D, TEXTURE_BRICKLOGOS); 

		glBegin(GL_POLYGON);

			glNormal3f(0.0f, 10.0f, 0.0f);

			glVertex3f(-10.0f, 0.0f, 10.0f);


			glTexCoord2f( 0.0 , 0.0 );


			glNormal3f(0.0f, 10.0f, 0.0f);

			glVertex3f(-10.0f, 0.0f, -10.0f);

			glTexCoord2f( 10.0 , 0.0 );


			glNormal3f(0.0f, 10.0f, 0.0f);

			glVertex3f(10.0f, 0.0f, -10.0f);

			glTexCoord2f( 10.0 , 10.0 );


			glNormal3f(0.0f, 10.0f, 0.0f);

			glVertex3f(10.0f, 0.0f, 10.0f);

			glTexCoord2f( 0.0 , 10.0 );



		glEnd();

		glDisable(GL_TEXTURE_2D);
		
		glMatrixMode(GL_MODELVIEW); //reset matrix mode

	glEndList();



}

void drawRotatingcube()
{
	glRotatef(theta, 0.0, 1.0, 0.0);

		glCallList(CUBE_ID);

	glRotatef(-theta, 0.0, 1.0, 0.0);

}

void drawcubeTextures(displayListInt)
{
		glCallList(displayListInt);
}



void loadRotatingcube()
{
	glNewList(CUBE_ID, GL_COMPILE);

		glNormalPointer(GL_FLOAT, 0, cubeNormals);

		glVertexPointer(3, GL_FLOAT, 0, cubeVertices);

		// 3-dim float values, no gaps

		glColorPointer(4, GL_FLOAT, 0, TransparantCubeColors);

		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	
	glEndList();

}

GLfloat Planes1[] = {1.0, 0.0, 1.0, 1.0 };
GLfloat Planet1[] = {0.0, 1.0, 0.0, 1.0 };

void loadcubeTextures(int displayListInt, int textureId, GLfloat multiplyer)
{
	Planes1[0] = multiplyer; //increase amount of textures on object
	Planes1[2] = multiplyer;
	Planes1[3] = multiplyer;
	Planet1[1] = multiplyer;
	Planet1[3] = multiplyer;

	glNewList(displayListInt, GL_COMPILE); //create new display list for cube

		glMatrixMode(GL_TEXTURE); //initialise texture matrix mode
		glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, textureId); 

			
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            glTexGenfv(GL_S, GL_OBJECT_PLANE, Planes1);
            glTexGenfv(GL_T, GL_OBJECT_PLANE, Planet1);

			//use textures for model
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			glNormalPointer(GL_FLOAT, 0, cubeNormals);

			glColorPointer(4, GL_FLOAT, 0, cubeColors);

			glVertexPointer(3, GL_FLOAT, 0, cubeVertices);




			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);


		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T); 

		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW); 

	
	glEndList();

}


void display(void)

{

	
	glutSwapBuffers();
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //nice effecten bij uit zetten clear :)
	
	/* Update viewer position in modelview matrix */
	glLoadIdentity(); 

	//gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);
	gluLookAt(viewer[0],viewer[1],viewer[2], lookat[0], lookat[1], lookat[2], 0.0, 1.0, 0.0);

	glTranslatef(lookat[0],lookat[1], lookat[2]); //translate to eye coordinates of lookat function
	//this is in order to make the plane rotate around the eye coordinates

	glRotatef(mousemovex, 0.0, 1.0, 0.0); //move plane according to x mouse movement
	glRotatef(mousemovey, 1.0, 0.0, 0.0); //move plane according to x mouse movement

	if (level == 2)
	{
		glRotatef(theta, 0.0, 1.0, 0.0); //move plane in a nasty way
		glRotatef(theta, 1.0, 0.0, 0.0); //move plane in a nasty way
	}

	
	glTranslatef(-lookat[0],-lookat[1], -lookat[2]); //translate to eye coordinates of lookat function
	
	glClearColor(0.7, 0.8 , 1.0, 1.0);

	//create light0 (white)
	glTranslatef(light0_pos[0],light0_pos[1], light0_pos[2]); 

		glColor4f(1.0, 1.0, 1.0, 1.0);

		glutSolidSphere(0.10, 32, 32);	
		
	glTranslatef(-light0_pos[0],-light0_pos[1], -light0_pos[2]); 

	//create light1 (red)
	glTranslatef(light1_pos[0],light1_pos[1], light1_pos[2]); 

		glColor4f(specular1[0], specular1[1], specular1[2], specular1[3]);

		glutSolidSphere(0.10, 32, 32);	
		
	glTranslatef(-light1_pos[0],-light1_pos[1], -light1_pos[2]); 

	//create light2 (green)
	glTranslatef(light2_pos[0],light2_pos[1], light2_pos[2]); 

		glColor4f(specular2[0], specular2[1], specular2[2], specular2[3]);

		glutSolidSphere(0.10, 32, 32);	
		
	glTranslatef(-light2_pos[0],-light2_pos[1], -light2_pos[2]); 


	glTranslatef(0.00, -1.51, 0.00); /*translate to get vars of ground 
										square to 'ground'/0 ((which is Y= -1.0
										because Y=0.00 is in the center of the view
										without translating because of the projection
										mode (and also with additional 0.01 
										because else the ground overlaps with the
										coordinate axes)*/
	
	glRotatef(180, 0.0, 1.0, 0.0);//draw other way around
	drawGroundSquare();
	glRotatef(-180, 0.0, 1.0, 0.0);//draw other way around

	//translate back z axis for ground
	glTranslatef(0.00, 1.51, 0.00);


	//show locust and cats
	glPushMatrix(); 

		glTranslatef(lookat[0],lookat[1], lookat[2]); 
			glRotatef(90, -1.0, 0.0, 0.0);//make cat stand up
				glRotatef(mainCharacterRotate, 0.0, 0.0, 1.0);//rotate cat by pressed keys
			
					drawCat(walk); //draw player/character

				glRotatef(-mainCharacterRotate, 0.0, 0.0, 1.0);//rotate cat by pressed keys
			glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(-lookat[0],-lookat[1], -lookat[2]); 

	glPopMatrix();

	//draw locust

	glPushMatrix(); 

		glTranslatef(locustMovementX, 0.0, locustMovementZ);
		glRotatef(locustTheta, 0.0, 2.0, 0.0);
			glTranslatef(0.0, -1.0, 0.0);

				drawLocust();		

			glTranslatef(0.0, 1.0, 0.0);
		glRotatef(locustTheta, 0.0, -2.0, 0.0);
		glTranslatef(-locustMovementX, 0.0, -locustMovementZ);


		//draw cats

		//translate for initial position

		glTranslatef(0.75, -1.00, -1.50);  //translate y and z up and back 

		

		//movement on plane

		glRotatef(180, 0.0, 1.0, 0.0);//make cat turn around
		glRotatef(90, -1.0, 0.0, 0.0);//make cat stand up


		

		if (level == 1)
		{
			glTranslatef(-1.5, -6.0, 0.0);
		}
		if (level == 2)
		{
			glTranslatef(-6.0, 10.0, 0.0);
		}

		  for(i = 0; i < 10; i ++)
		  {

			glTranslatef(0.7, 0.00, 0.0); 

			drawCat(1); //draw 10 cats

		  }
		if (level == 1)
		{
			glTranslatef(1.5, 6.0, 0.0);
		}
		if (level == 2)
		{
			glTranslatef(6.0, -10.0, 0.0);
		}



		  glTranslatef((-0.7 * 10), (-0.00 * 10), 0.0); //translate back


				
				glTranslatef(-2.0, 1.0, 0.0);

					drawTextureCat(); //green ground texture cat

				glTranslatef(2.0, -1.0, 0.0);



			glTranslatef(1.0, -1.05, 0.0); //translate back

			glTranslatef(-0.2, -0.05, 0.0);


		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(180, 0.0, -1.0, 0.0);

		
		glTranslatef(-0.75, -1.00, 1.50); //reset translation


	glPopMatrix();

	//show flats

	glPushMatrix(); 



		glTranslatef(2.0, -0.70, -1.50); 
			
		  for(i = 0; i < 3; i ++)
		  {
			glTranslatef(1.2, 0.0, 0.0); 
			drawcubeTextures(FLAT1); //draw 3 small flats
		  }

		  glTranslatef((-1.2 * 3), (-0.0 * 3), (-0.00* 3)); //translate back

			glTranslatef(6.0, 1.7, -3.0); 

				glScalef(2.0, 5.0, 2.0);


				  for(i = 0; i < 4; i ++)
				  {
					glTranslatef(0.0, 0.0, 1.5); 
					drawcubeTextures(FLAT2); //draw 4 big flats
				  }

				  glTranslatef((-0.0 * 4), (-0.0 * 4), (-1.5 * 4)); //translate back


					glScalef(1.0, 2.0, 1.0);
						glTranslatef(-6.0, 0.25, 0.5); 

				  for(i = 0; i < 3; i ++)
				  {
					glTranslatef(0.0, 0.0, 2.0); 
					drawcubeTextures(FLAT3); //draw 3 skyscrapers
				  }

				  glTranslatef((-0.0 * 3), (-0.0 * 3), (-2.0 * 3)); //translate back
							

							glScalef(2.0, 1.0, 1.0);
								glTranslatef(-1.0, 0.0, -2.0); 
									drawcubeTextures(FLAT4);
								glTranslatef(1.0, 0.0, 2.0); 
							glScalef(-2.0, -1.0, -1.0);

						glTranslatef(6.0, -0.25, -0.5); 
					glScalef(-1.0, -2.0, -1.0);

				glScalef(-2.0, -5.0, -2.0);

			glTranslatef(-6.0, -1.7, 3.0); 

		glTranslatef(-2.0, 0.70, 1.50); //reset translation



	
		glPopMatrix();

		
		glPushMatrix(); 


		if (level == 1)
		{
			glTranslatef(-6.25, -0.98, -9.00);  //translate y and z up and back
		}
		if (level == 2)
		{
			glTranslatef(8.25, -0.98, 9.00);  //translate y and z up and back
		}

		
		//needs to be modelled at the end because of transparancy
			drawRotatingcube();
		
		if (level == 1)
		{
			glTranslatef(6.25, 0.98, 9.00); 
		}
		if (level == 2)
		{
			glTranslatef(-8.25, 0.98, -9.00); 
		}

		glPopMatrix();


		//process game data 
		game();

	glFlush(); //clear buffers

	


}


int ceilw;
int ceilh;

void reshapeWindow(GLsizei w, GLsizei h)
{
	

	if (reshape == 1) // 4:3 aspect ratio //default
	{
	
	ceilw = ceil( (w / 1.33333333) );  //give or take a pixel :-)
	ceilh = ceil( (h * 1.33333333) );

		if(w < ceilh)
		{
		
			glViewport(0,0,w, ceilw );

		}

		if(h < ceilw)
		{
		
			glViewport(0,0, ceilh , h);
		}



		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glFrustum(-1.00, 1.00,  -1.00,  1.00, 1.00, 20.50);

		


	glMatrixMode(GL_MODELVIEW);

	}
	if (reshape == 2) // 16:10 aspect ratio - TFT widescreen
	{
		
		//does not display "full sceen" because of the window bar. 
		// HDTV however does 
	
	ceilw = ceil( (w / 1.6) );  //give or take a pixel :-)
	ceilh = ceil( (h * 1.6) );
	// adjust viewport, clear and flush

		if(w < ceilh)

		{
			
			glViewport(0,0,w, ceilw );

		}

		if(h < ceilw)

		{
			
			glViewport(0,0, ceilh , h);

		}


		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glFrustum(-1.00, 1.00,  -1.00,  1.00, 1.00, 20.50);

		glMatrixMode(GL_MODELVIEW);





	}
	if (reshape == 3) // 16:9 aspect ratio - (HD)TV-widescreen
	{
	
	ceilw = ceil( (w / 1.7777777) );  //give or take a pixel :-)
	ceilh = ceil( (h * 1.7777777) );


	// adjust viewport, clear and flush

		if(w < ceilh)

		{
			
			glViewport(0,0,w, ceilw );

		}

		if(h < ceilw)

		{
			
			glViewport(0,0, ceilh , h);

		}


		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glFrustum(-1.00, 1.00,  -1.00,  1.00, 1.00, 20.50);

		glMatrixMode(GL_MODELVIEW);





	}
	if (reshape == 4) // 1 to 1 aspect ratio
	{

		// adjust viewport, clear and flush

		if(w < h)
		{
			glViewport(0,0,w,w);
		}

		if(h < w)
		{
			glViewport(0,0,h,h);
		}
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glFrustum(-1.00, 1.00,  -1.00,  1.00, 1.00, 20.50);

		glMatrixMode(GL_MODELVIEW);


	}

	glFlush(); 


}



void idle(void)

{


	if(fmod(spacestop, 2) == 1)
	{ //space bar stop function for project evaluation


		currentTimeLocust = Wallclock(); // from glutil.h (VU-made)

		elapsedTimeLocust = currentTimeLocust - storedTimeLocust;

		//start at bottom point to left side of screen

		if (locustDirection == 0)
		{//drive straight
			locustTheta = 0.0;
			locustMovementX = locustMovementX - elapsedTimeLocust;
			if (locustMovementX <= -1.00){ locustMovementX = -1.00;	locustDirection++;}

		}
		if (locustDirection == 1)
		{//turn right
			locustTheta = locustTheta - (elapsedTimeLocust * 470); //(1 seconds for a 90 degrees spin)
			locustMovementX = locustMovementX - elapsedTimeLocust;
			locustMovementZ = locustMovementZ - elapsedTimeLocust;

			if (locustMovementX <= -2.00 || locustMovementZ <= -1.00){ locustMovementX = -2.00; locustMovementZ = -1.00; locustDirection++; locustTheta = -90.0;}
		}

		if (locustDirection == 2)
		{//turn right
			locustTheta = locustTheta - (elapsedTimeLocust * 120); //(1 seconds for a 90 degrees spin)
			locustMovementX = locustMovementX + elapsedTimeLocust;
			locustMovementZ = locustMovementZ - elapsedTimeLocust;

			if (locustMovementX >= -1.00 || locustMovementZ <= -2.00){ locustMovementX = -1.00; locustMovementZ = -2.00;  locustDirection++; locustTheta = -180.0;}
		}

		if (locustDirection == 3)
		{//turn right
			locustMovementX = locustMovementX + elapsedTimeLocust;

			if (locustMovementX >= 0.00){locustMovementX = 0.00; locustDirection++;}
		}

		if (locustDirection == 4)
		{//turn right
			locustTheta = locustTheta - (elapsedTimeLocust * 90); //(1 seconds for a 90 degrees spin)
			locustMovementX = locustMovementX + elapsedTimeLocust;
			locustMovementZ = locustMovementZ + elapsedTimeLocust;

			if (locustMovementX >= 1.00 || locustMovementZ >= -1.00){locustMovementX = 1.00; locustMovementZ = -1.00;  locustDirection++; locustTheta = -270.0;}
		}
		if (locustDirection == 5)
		{//turn right
			locustTheta = locustTheta - (elapsedTimeLocust * 90); //(1 seconds for a 90 degrees spin)
			locustMovementX = locustMovementX - elapsedTimeLocust;
			locustMovementZ = locustMovementZ + elapsedTimeLocust;

			if (locustMovementX <= 0.00 || locustMovementZ >= 0.00){locustMovementX = 0.00; locustMovementZ = 0.00;  locustDirection = 0; locustTheta = 0.0;}
		}

		//update stored Time
		storedTimeLocust = currentTimeLocust; 

			currentTime = Wallclock(); // from glutil.h (VU-made)

			elapsedTime = currentTime - storedTime;
			//calculate cube rotation

			theta = theta + (elapsedTime * 120); //(3 seconds for a 360 degrees spin)

			

			if ( theta>=360.0) 

			{

				theta -= 360.0; //reset theta to 0 (+ remaining value) if higher than 360 (degrees)

			}

			storedTime = currentTime; 



			glutPostRedisplay();

	}
	else
	{ //also redisplay when pauze function is enabled because of resizing
		glutPostRedisplay();
	}


	//end walk animation if character stopped walking
	if (walk == 1)
	{
		currentTimeWalk = Wallclock(); // from glutil.h (VU-made)

		elapsedTimeWalk = elapsedTimeWalk + (currentTimeWalk - storedTimeWalk);

		storedTimeWalk = currentTimeWalk;

		if(elapsedTimeWalk > 0.05)
		{walk = 0; elapsedTimeWalk = 0;}
		
	}
	


}



void myInit()

{

	glEnable(GL_COLOR_MATERIAL);

	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	//setup lighting

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);

		glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	//try to create some opacity (the sgf-format.txt stated that it was not needed, but windows contained opacity parameter below 1.0)
	glEnable (GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //from http://www.opengl.org/resources/faq/technical/transparency.htm

	//Initialize models
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	//initialise viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//enable depth
	glEnable(GL_DEPTH_TEST);

	//load textures (needs to be in front of models to apply textures

	loadTextureRGB("../textures/ground1.rgb", TEXTURE_GROUND);
	loadTextureRGBA("../textures/bricklogos.rgba", TEXTURE_BRICKLOGOS);
	loadTextureRGBA("../textures/brickwindow256.rgba", TEXTURE_BRICKWINDOW);
	loadTextureRGBA("../textures/skyscraper.rgba", TEXTURE_SKYSCRAPER);
	loadTextureRGB("../textures/skyscraper2.rgb", TEXTURE_SKYSCRAPER2);

	//make display list for ground object (textures must be loaded beforehand)
	loadGroundSquare();


	//read model data and make display lists

	//loaderData("../models/cat/body.sgf", CAT_BODY);

	loaderDataWithRandomTextures("../models/cat/body.sgf", TEX_CAT_BODY, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/eye_left.sgf", TEX_CAT_EYE_LEFT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/eye_right.sgf", TEX_CAT_EYE_RIGHT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/hand_left.sgf", TEX_CAT_HAND_LEFT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/hand_right.sgf", TEX_CAT_HAND_RIGHT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/leg_left.sgf", TEX_CAT_LEG_LEFT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/leg_right.sgf", TEX_CAT_LEG_RIGHT, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/nose.sgf", TEX_CAT_NOSE, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/tail.sgf", TEX_CAT_TAIL, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/teeth.sgf", TEX_CAT_TEETH, TEXTURE_GROUND);
	loaderDataWithRandomTextures("../models/cat/whiskers.sgf", TEX_CAT_WHISKERS, TEXTURE_GROUND);
	
	
	loaderData("../models/cat/body.sgf", CAT_BODY);
	loaderData("../models/cat/eye_left.sgf", CAT_EYE_LEFT);
	loaderData("../models/cat/eye_right.sgf", CAT_EYE_RIGHT);
	loaderData("../models/cat/hand_left.sgf", CAT_HAND_LEFT);
	loaderData("../models/cat/hand_right.sgf", CAT_HAND_RIGHT);
	loaderData("../models/cat/leg_left.sgf", CAT_LEG_LEFT);
	loaderData("../models/cat/leg_right.sgf", CAT_LEG_RIGHT);
	loaderData("../models/cat/nose.sgf", CAT_NOSE);
	loaderData("../models/cat/tail.sgf", CAT_TAIL);
	loaderData("../models/cat/teeth.sgf", CAT_TEETH);
	loaderData("../models/cat/whiskers.sgf", CAT_WHISKERS);
	
	loaderData("../models/locust/ANTENNAE.sgf", LOCUST_ANTENNAE);
	loaderData("../models/locust/BODY.sgf", LOCUST_BODY);
	loaderData("../models/locust/EYES.sgf", LOCUST_EYES);
	loaderData("../models/locust/HEAD.sgf", LOCUST_HEAD);
	loaderData("../models/locust/LEG_BACK_LEFT_LOWER.sgf", LOCUST_LEG_BACK_LEFT_LOWER);
	loaderData("../models/locust/LEG_BACK_LEFT_UPPER.sgf", LOCUST_LEG_BACK_LEFT_UPPER);
	loaderData("../models/locust/LEG_BACK_RIGHT_LOWER.sgf", LOCUST_LEG_BACK_RIGHT_LOWER);
	loaderData("../models/locust/LEG_BACK_RIGHT_UPPER.sgf", LOCUST_LEG_BACK_RIGHT_UPPER);
	loaderData("../models/locust/LEG_FRONT_LEFT.sgf", LOCUST_LEG_FRONT_LEFT);
	loaderData("../models/locust/LEG_FRONT_RIGHT.sgf", LOCUST_LEG_FRONT_RIGHT);
	loaderData("../models/locust/LEG_MIDDLE_LEFT.sgf", LOCUST_LEG_MIDDLE_LEFT);
	loaderData("../models/locust/LEG_MIDDLE_RIGHT.sgf", LOCUST_LEG_MIDDLE_RIGHT);
	loaderData("../models/locust/MOUTH.sgf", LOCUST_MOUTH);

	loadRotatingcube();

	//create flats
	loadcubeTextures(FLAT1, TEXTURE_GROUND, 1.0);
	loadcubeTextures(FLAT2, TEXTURE_BRICKWINDOW, 2.3);
	loadcubeTextures(FLAT3, TEXTURE_SKYSCRAPER, 2.3);
	loadcubeTextures(FLAT4, TEXTURE_SKYSCRAPER2, 2.3);


	glEnable(GL_NORMALIZE); 

}





int main(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );

	glutInitWindowSize(800, 600);

	glutInitWindowPosition(0, 0);

    glutCreateWindow("Final Project");



	myInit();

	glMatrixMode(GL_MODELVIEW);



	//call I/O functions

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutMouseFunc(mouse);

	glutMotionFunc(mouse_move);

	glutReshapeFunc(reshapeWindow);

		

		//create menu

		sub_menu2 = glutCreateMenu(reshape_menu); // creates and selects ‘‘current’’ menu

		glutAddMenuEntry("aspect 4:3 (default)", 1); 

		glutAddMenuEntry("aspect 16:10 - TFT widescreen", 2);

		glutAddMenuEntry("aspect 16:9 - (HD)TV widescreen", 3);

		glutAddMenuEntry("aspect 1:1", 4);


		sub_menu3 = glutCreateMenu(shade_menu); // creates and selects ‘‘current’’ menu

		glutAddMenuEntry("Enable smooth shading", 1); 

		glutAddMenuEntry("Enable flat shading", 2);



		glutCreateMenu(top_menu); // create new ‘‘current’’ menu



			glutAddSubMenu("Aspect ratio", sub_menu2); // add sub menu to menu

			glutAddSubMenu("Shading", sub_menu3); // add sub menu to menu

		glutAddMenuEntry("quit",2);

		glutAttachMenu(GLUT_RIGHT_BUTTON); // attach current menu to mouse button

	

	glutIdleFunc(idle);



	glutMainLoop();

}

