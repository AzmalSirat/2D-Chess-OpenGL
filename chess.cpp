#include "drawPieces.cpp"



using namespace std;

struct point
{
	double x,y,z;
};

// void changeColor(double color[]){
//     //  color (0.95, 0.95, 0.75) and (0.66, 0.78, 0.3).
//     color[0] = 0.95 + 0.66 - color[0];
//     color[1] = 0.95 + 0.78 - color[1];
//     color[2] = 0.75 + 0.3 - color[2];
// }

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void drawCheckerBoard(){
    vector <vector<float>> color;
    //checkeboard colors
    color.push_back({0.95, 0.95, 0.75});
    color.push_back({{0.66, 0.78, 0.3}});

    double x = -9, y = -9;
    int current = 0;
    vector<float> currentColor;

    for (int i=0; i<8; i++){
        x += 2;
        current = 1 - current;
        currentColor = color[current];

        for (int j=0, y=-9; j<8; j++){
            y+= 2;
            current = 1 - current;
            currentColor = color[current];

            glPushMatrix();
            {
                glTranslatef(x,y,0);
                glColor3f(currentColor[0], currentColor[1], currentColor[2]);
                // cout << "drawing square at " << x << ", " << y << endl;
                drawSquare(1);
            }
            glPopMatrix();
        }
    }

    glColor3f(0.5,0.5,0.5);


}



// ...existing code...


// ...existing code...


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			// drawgrid=1-drawgrid;
			break;
		
		case 27:
			exit(0);
			break; // ESC key: exit program
    

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				// drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,10,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	// drawAxes();
	glColor3f(1.0,1.0,1.0);
	
	drawCheckerBoard();
    // Test arrangement of pieces with proper spacing for 8x8 board
	// glPushMatrix();
	// glTranslatef(-3, -2, 0);
	// drawPawn();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(-2, -2, 0);
	// drawRook();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(-1, -2, 0);
	// drawKnight();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(0, -2, 0);
	// drawBishop();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(1, -2, 0);
	// drawQueen();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(2, -2, 0);
	// drawKing();
	// glPopMatrix();
	
	// glPushMatrix();
	// glTranslatef(3, -2, 0);
	// drawBishop();
	// glPopMatrix();

    //glColor3f(1,0,0);
    //drawSquare(10);

    // drawSS();

	//drawCone(20,50,24);

	//drawSphere(30,24,20);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(int value){

	//codes for any changes in Models, Camera
	glutPostRedisplay();
	glutTimerFunc(50, animate, 0);
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(200, 100);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("2D Chess Game");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	// glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutTimerFunc(100, animate, 0);
	// glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
