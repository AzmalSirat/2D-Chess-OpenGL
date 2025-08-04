#include "gameLogic.cpp"

using namespace std;

extern vector <Piece*> pieces, backup;
extern map <pair <int, int>, Piece*> boardMap, boardBackup;
extern vector <pair <int, int>> availables;
extern vector <pair <int, int>> attacks;
pair <int, int> position;
const int high_pos = 575, low_pos = 64;
int current = 1; //starting from white
extern pair <int, int> selected;
extern vector <pair <int, int>> previous;
Piece* selectedPiece = nullptr;


pair <int, int> findPosition (int x, int y) {
	int i = (x-low_pos)*8 / (high_pos-low_pos);
	int j = 7- (y-low_pos)*8 / (high_pos-low_pos);
	return {i,j};
}

int state = 0;

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			// drawgrid=1-drawgrid;
			break;
		
		case 27:
			for (auto x: pieces) delete x;
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
				
				pair <int, int> p = findPosition(x,y);
				cout << "clicked in " << p.first << ", " << p.second << endl;
				
				
				//update map for all case

				auto it = find(availables.begin(), availables.end(), p);
				if (selectedPiece && it != availables.end()){
					pair <int, int> prevPos = selectedPiece->getPosition();
					selectedPiece->setIndex(p.first, p.second);
					cout << "piece moved in " << p.first << ", " << p.second << endl;
					availables.clear();
					attacks.clear();
					//check queen for pawn
					Piece* checkQueen = checkPawn(selectedPiece, p);
					boardMap.erase(prevPos);
					if (checkQueen == nullptr){
						boardMap.insert({p, selectedPiece});
					} else{
						auto iter = find(pieces.begin(), pieces.end(), selectedPiece);
						if (iter != pieces.end()) {
							pieces.erase(iter);
						}
						pieces.push_back(checkQueen);
						boardMap.insert({p, checkQueen});
					}

					selectedPiece = nullptr;
					selected = {-1,-1};
					current = 1-current;
					
					return;
				}

				auto it1 = find(attacks.begin(), attacks.end(), p);
				if (selectedPiece && it1 != attacks.end()){

					pair <int, int> pr = findPosition(x,y);
					Piece* pos = findPiece(pr);
					pair <int, int> prevPos = selectedPiece->getPosition();
					
					auto iter = find(pieces.begin(), pieces.end(), pos);
					if (iter != pieces.end()) {
						pieces.erase(iter);
					}

					delete pos;

					selectedPiece->setIndex(p.first, p.second);
					availables.clear();
					attacks.clear();
					boardMap.erase(prevPos);
					boardMap.erase(p); // also the current one as well
					
					Piece* checkQueen = checkPawn(selectedPiece, p);
					if (checkQueen == nullptr){
						boardMap.insert({p, selectedPiece});
					} else{
						auto iter = find(pieces.begin(), pieces.end(), selectedPiece);
						if (iter != pieces.end()) {
							pieces.erase(iter);
						}
						boardMap.insert({p, checkQueen});
						pieces.push_back(checkQueen);
					}
					
					selectedPiece = nullptr;
					selected = {-1,-1};
					current = 1-current;
					return;
				}

				availables.clear();
				attacks.clear();
				
				Piece* pos = findPiece(p);

				if (pos != nullptr && pos->getColor() == current) {
					cout << "piece found in " << p.first << " " <<p.second << endl;
					pos->print();
					auto x = pos->moves();
					availables = x[0];
					attacks = x[1];
					selectedPiece = pos;
					selected= p;
				}


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

    for (auto& p: pieces){
		p->draw();
	}

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

	initBoard();
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
