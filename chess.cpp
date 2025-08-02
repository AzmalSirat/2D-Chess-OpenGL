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

double xt[] = {1.4,1,0.5,0.2,-0.2,-0.6,-1,-1.4};
double yt[] = {1.3,0.9,0.4,0,-0.3,-0.7,-1.2,-1.7};

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
    color.push_back({0.85, 0.85, 0.65});
    color.push_back({0.66, 0.78, 0.3});

    int current = 0;
    vector<float> currentColor;

    for (int i=0; i<8; i++){
        double x = -7 + i*2;  // Position from -7 to 7 in steps of 2
        current = i % 2;  // Alternate starting color for each row

        glPushMatrix();
        
        for (int j=0; j<8; j++){
            double y = -7 + j*2;  // Position from -7 to 7 in steps of 2
            currentColor = color[current];

            glPushMatrix();
            {
                glTranslatef(x, y, 0);
                glColor3f(currentColor[0],currentColor[1],currentColor[2]);
                drawSquare(1);
                
                // Draw piece on top of square, centered
                glColor3f(0,0,0);  // Dark pieces
                glPushMatrix();
                glTranslatef(xt[i], yt[j], 0.1);  // Move piece slightly above the square
                // glScalef(0.8, 0.8, 1);    // Scale the piece to fit nicely in square
                if ((i+j)%2 == 0) {
                    glScalef(-1,-1,1);
                    glTranslatef(0,-0.25,0.001);
                }
                drawBishop();
                glPopMatrix();
            }
            glPopMatrix();
            
            current = 1 - current;  // Alternate color for next square
        }
        glPopMatrix();
    }

    glColor3f(1.0, 1.0, 1.0);  // Reset color to white
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
	

    glPushMatrix();
    drawCheckerBoard();
    glPopMatrix();





    // Place some pieces on the board for testing
    
    // 
    
    // glPushMatrix();
    // glTranslatef(-5, -7, 0);  // Next square
    // glScalef(0.6, 0.6, 1);
    // drawKnight();
    // glPopMatrix();
    glColor3f(1.0,1.0,1.0);
	
	
	
    
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(int value){

	//codes for any changes in Models, Camera
	glutPostRedisplay();
	glutTimerFunc(5000, animate, 0);
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
	gluPerspective(90,	1,	1,	1000.0);
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
