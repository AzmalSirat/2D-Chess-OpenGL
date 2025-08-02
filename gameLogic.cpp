#include "drawPieces.cpp"

vector <Piece*> pieces;
map <pair <int, int>, Piece*> boardMap;

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
            }
            glPopMatrix();
            
            current = 1 - current;  // Alternate color for next square
        }
        glPopMatrix();
    }

    glColor3f(1.0, 1.0, 1.0);  // Reset color to white
}


void King:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawKing();
        glPopMatrix();

}

void Queen:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawQueen();
        glPopMatrix();

}

void Knight:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawKnight();
        glPopMatrix();

}

void Bishop:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawBishop();
        glPopMatrix();

}

void Rook:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawRook();
        glPopMatrix();

}

void Pawn:: draw () {

        glPushMatrix();
        glTranslatef(x,y,0);
        drawHelper();
        drawPawn();
        glPopMatrix();

}

