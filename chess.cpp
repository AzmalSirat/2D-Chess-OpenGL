#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>


#include <GL/glut.h>

#define pi (2*acos(0.0))

struct point
{
	double x,y,z;
};


void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

// ...existing code...

void drawCircle(double radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 2);
    for (int i = 0; i <= segments; i++) {
        double angle = 2.0 * pi * i / segments;
        glVertex3f(radius * cos(angle), radius * sin(angle), 2);
    }
    glEnd();
}

void drawTriangle(double size) {
    glBegin(GL_TRIANGLES);
    glVertex3f(0, size, 2);
    glVertex3f(-size * 0.5, -size * 0.5, 2);
    glVertex3f(size * 0.5, -size * 0.5, 2);
    glEnd();
}

void drawRectangle(double width, double height) {
    glBegin(GL_QUADS);
    glVertex3f(-width/2, height/2, 2);
    glVertex3f(width/2, height/2, 2);
    glVertex3f(width/2, -height/2, 2);
    glVertex3f(-width/2, -height/2, 2);
    glEnd();
}

void drawPawn() {
    // Draw base
    drawRectangle(1.0, 0.3);
    
    // Draw body
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    drawRectangle(0.6, 0.8);
    glPopMatrix();
    
    // Draw head
    glPushMatrix();
    glTranslatef(0, 1.2, 0);
    drawCircle(0.3, 16);
    glPopMatrix();
}

void drawRook() {
    // Draw base
    drawRectangle(1.2, 0.3);
    
    // Draw main body
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
    drawRectangle(0.8, 1.1);
    glPopMatrix();
    
    // Draw top crenellations
    glPushMatrix();
    glTranslatef(-0.3, 1.4, 0);
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 1.4, 0);
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 1.4, 0);
    drawRectangle(0.15, 0.3);
    glPopMatrix();
}

void drawKnight() {
    // Draw base
    drawRectangle(1.2, 0.3);
    
    // Draw main body/neck
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
    drawRectangle(0.8, 0.8);
    glPopMatrix();
    
    // Draw horse head - main part
    glPushMatrix();
    glTranslatef(0.2, 1.3, 0);
    drawRectangle(0.8, 0.6);
    glPopMatrix();
    
    // Draw horse snout/nose
    glPushMatrix();
    glTranslatef(0.5, 1.1, 0);
    drawRectangle(0.4, 0.3);
    glPopMatrix();
    
    // Draw horse ears
    glPushMatrix();
    glTranslatef(0.1, 1.7, 0);
    drawTriangle(0.25);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 1.7, 0);
    drawTriangle(0.25);
    glPopMatrix();
    
    // Draw mane - multiple segments for better look
    glPushMatrix();
    glTranslatef(-0.2, 1.5, 0);
    drawRectangle(0.15, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.3, 1.2, 0);
    drawRectangle(0.15, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.25, 0.9, 0);
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    // Draw eye
    glPushMatrix();
    glTranslatef(0.3, 1.4, 0);
    drawCircle(0.08, 8);
    glPopMatrix();
    
    // Draw nostril
    glPushMatrix();
    glTranslatef(0.6, 1.0, 0);
    drawCircle(0.05, 6);
    glPopMatrix();
}

void drawBishop() {
    // Draw base with rounded corners effect
    drawRectangle(1.2, 0.3);
    
    // Draw base ring
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
    drawRectangle(1.0, 0.1);
    glPopMatrix();
    
    // Draw lower body (tapered)
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    drawRectangle(0.8, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.8, 0);
    drawRectangle(0.7, 0.3);
    glPopMatrix();
    
    // Draw middle section
    glPushMatrix();
    glTranslatef(0, 1.05, 0);
    drawRectangle(0.6, 0.25);
    glPopMatrix();
    
    // Draw upper body (more elegant taper)
    glPushMatrix();
    glTranslatef(0, 1.3, 0);
    drawRectangle(0.5, 0.3);
    glPopMatrix();
    
    // Draw mitre base
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    drawRectangle(0.7, 0.15);
    glPopMatrix();
    
    // Draw mitre (bishop's hat) - more elegant shape
    glPushMatrix();
    glTranslatef(0, 1.7, 0);
    glScalef(0.8, 1.0, 1);
    drawTriangle(0.5);
    glPopMatrix();
    
    // Draw mitre decoration
    glPushMatrix();
    glTranslatef(0, 1.6, 0);
    drawRectangle(0.6, 0.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 1.65, 0);
    drawRectangle(0.5, 0.05);
    glPopMatrix();
    
    // Draw cross on top - more proportional
    glPushMatrix();
    glTranslatef(0, 1.95, 0);
    drawRectangle(0.06, 0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 2.0, 0);
    drawRectangle(0.18, 0.06);
    glPopMatrix();
    
    // Add small decorative elements
    glPushMatrix();
    glTranslatef(0, 1.25, 0);
    drawCircle(0.08, 8);
    glPopMatrix();
}

void drawQueen() {
    // Draw ornate base
    drawRectangle(1.4, 0.3);
    
    // Draw base rings for elegance
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
    drawRectangle(1.2, 0.1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.35, 0);
    drawRectangle(1.0, 0.08);
    glPopMatrix();
    
    // Draw lower body with elegant taper
    glPushMatrix();
    glTranslatef(0, 0.6, 0);
    drawRectangle(0.9, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.9, 0);
    drawRectangle(0.8, 0.3);
    glPopMatrix();
    
    // Draw waist
    glPushMatrix();
    glTranslatef(0, 1.15, 0);
    drawRectangle(0.65, 0.2);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 1.4, 0);
    drawRectangle(0.7, 0.3);
    glPopMatrix();
    
    // Draw crown base with ornate design
    glPushMatrix();
    glTranslatef(0, 1.6, 0);
    drawRectangle(0.9, 0.15);
    glPopMatrix();
    
    // Draw crown band
    glPushMatrix();
    glTranslatef(0, 1.7, 0);
    drawRectangle(0.85, 0.1);
    glPopMatrix();
    
    // Draw crown points with varied heights for elegance
    for (int i = -3; i <= 3; i++) {
        glPushMatrix();
        glTranslatef(i * 0.12, 1.8, 0);
        double height;
        if (i == 0) height = 0.4;          // Center tallest
        else if (abs(i) == 1) height = 0.35;  // Next to center
        else if (abs(i) == 2) height = 0.25;  // Sides
        else height = 0.15;                    // Outer edges
        
        drawRectangle(0.06, height);
        glPopMatrix();
        
        // Add small circles on top of crown points
        if (abs(i) <= 2) {
            glPushMatrix();
            glTranslatef(i * 0.12, 1.8 + height/2 + 0.05, 0);
            drawCircle(0.04, 6);
            glPopMatrix();
        }
    }
    
    // Add decorative elements on the body
    glPushMatrix();
    glTranslatef(0, 1.35, 0);
    drawCircle(0.1, 8);
    glPopMatrix();
    
    // Add side decorations
    glPushMatrix();
    glTranslatef(-0.25, 1.35, 0);
    drawCircle(0.06, 6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, 1.35, 0);
    drawCircle(0.06, 6);
    glPopMatrix();
    
    // Add decorative band around waist
    glPushMatrix();
    glTranslatef(0, 1.15, 0);
    drawRectangle(0.7, 0.04);
    glPopMatrix();
}

void drawKing() {
    // Draw base
    drawRectangle(1.4, 0.3);
    
    // Draw lower body
    glPushMatrix();
    glTranslatef(0, 0.6, 0);
    drawRectangle(0.9, 0.6);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 1.1, 0);
    drawRectangle(0.7, 0.5);
    glPopMatrix();
    
    // Draw crown base
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    drawRectangle(0.9, 0.25);
    glPopMatrix();
    
    // Draw crown points
    for (int i = -2; i <= 2; i++) {
        glPushMatrix();
        glTranslatef(i * 0.18, 1.75, 0);
        double height = (abs(i) <= 1) ? 0.3 : 0.2;
        drawRectangle(0.1, height);
        glPopMatrix();
    }
    
    // Draw cross on top
    glPushMatrix();
    glTranslatef(0, 2.1, 0);
    drawRectangle(0.06, 0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 2.15, 0);
    drawRectangle(0.2, 0.06);
    glPopMatrix();
}

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
	
	drawQueen();
	
	glTranslated(3,3,0);
	drawBishop();
	glTranslated(-3,0,0);
	drawRook();
	// drawPawn();

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
