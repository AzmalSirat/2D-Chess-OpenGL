#include "drawPieces.cpp"

vector <Piece*> pieces, backup;
map <pair <int, int>, Piece*> boardMap, boardBackup;
vector <pair <int, int>> availables;
vector <pair <int, int>> attacks;
pair <int, int> selected = {-1,-1};
vector <pair <int, int>> previous = {{-1, -1}, {-1,-1}};


Piece* findPiece(pair <int, int> p){
	auto it = boardMap.find({p});
	if (it != boardMap.end()){
		return it->second;
	}
	return nullptr;
}


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

void drawCircle(string color) {

    if (color == "red"){
        glColor3f (0.8,0.1,0.1);
    }
    else glColor3f (0.1,0.5,0.2);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0.5);  // Center of the circle at origin
    
    int segments = 32;  // Number of segments for smooth circle
    double radius = 0.4;
    
    for (int i = 0; i <= segments; i++) {
        double angle = 2.0 * 3.14159 * i / segments;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex3f(x, y, 0.5);
    }

    // cout << "circle drawn." << endl;
    
    glEnd();
}

void highlight(double color[]){
    glColor3f(color[0],color[1],color[2]);
	glBegin(GL_QUADS);{
		glVertex3f( -1, -1,0.01);
		glVertex3f( 1,-1,0.01);
		glVertex3f(1,-0.8,0.01);
        glVertex3f(-1, -0.8,0.01);
	}glEnd();
    glBegin(GL_QUADS);{
		glVertex3f( 1, -1,0.01);
		glVertex3f( 1,1,0.01);
		glVertex3f(0.8,1,0.01);
        glVertex3f(0.8, -1,0.01);
	}glEnd();
    glBegin(GL_QUADS);{
		glVertex3f( -1, 1,0.01);
		glVertex3f( -1,-1,0.01);
		glVertex3f(-0.8,-1,0.01);
        glVertex3f(-0.8, 1,0.01);
	}glEnd();
    glBegin(GL_QUADS);{
		glVertex3f( 1, 1,0.01);
		glVertex3f( -1,1,0.01);
		glVertex3f(-1,0.8,0.01);
        glVertex3f(1, 0.8,0.01);
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
                if (i == selected.first && j == selected.second){
                    double clr[] = {0.1, 0.9, 0.1};
                    highlight(clr);
                    // continue;
                }
                // if ((i == previous[0].first && j == previous[0].second) ){
                //     double clr[] = {0.9,0.9,0.1};
                //     highlight(clr);
                // }
                for (auto p: availables){
                    if (p.first == i && p.second == j){
                        glTranslatef(0.1*(4-i),0.1*(4-j),0);
                        drawCircle("green");
                        
                        continue;
                    }
                }
                for (auto p: attacks){
                    if (p.first == i && p.second == j){
                        double clr[] = {0.8, 0.1, 0.1};
                        highlight(clr);
                        continue;
                    }
                }
                // ;
            }
            
            glPopMatrix();
            
            current = 1 - current;  // Alternate color for next square
        }
        glPopMatrix();
    }

    glColor3f(1.0, 1.0, 1.0);  // Reset color to white
}

void drawAvailables(vector <pair <int, int>> availables){
    for (auto p: availables){
        glPushMatrix();
        int x = -7 + 2* p.first; // x = -7 + 2i
        int y = -7 + 2* p.second; // y = -7 + 2j
        glTranslatef(x, y, 0.5);
        cout << "trying to draw at " << x << y << " green" << endl;
        // glColor3f(0.1, 0.8, 0.1);  // Set color to green
    
        drawCircle("green");
        glPopMatrix();
    }
}

void drawAttacks(vector <pair <int, int>> attacks){
    for (auto p: attacks){
        glPushMatrix();
        int x = -7 + 2* p.first; // x = -7 + 2i
        int y = -7 + 2* p.second; // y = -7 + 2j
        // glTranslatef(x, y, 0);
        // glColor3f(0.8, 0.1, 0.1);  // Set color to green
    
        drawCircle("red");
        glPopMatrix();
    }
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

void initBoard(){

    for (int j=0; j<8; j++){
        if (j>1 && j<6) continue;
        if (j==1 || j==6) {
            int color = 1;
            if (j==6) color = 0;
            for (int i=0; i<8; i++){
                Piece* p = new Pawn (i, j, color, "pawn");
                pieces.push_back(p);
                backup.push_back(p);
                boardMap.insert({{i,j}, p});
                boardBackup.insert({{i,j}, p});
            }
            continue;
        }
        if (j==0 || j==7){
            int color = (j<=0);
            for (int i=0; i<8; i++){
                if (i==0 || i==7){
                    Piece* p = new Rook (i, j, color, "rook");
                    pieces.push_back(p);
                    backup.push_back(p);
                    boardBackup.insert({{i,j}, p});
                    boardMap.insert({{i,j}, p});
                    
                }
                if (i==1 || i==6){
                    Piece* p = new Knight (i, j, color, "knight");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);
                    boardBackup.insert({{i,j}, p});

                }
                if (i==2 || i==5){
                    Piece* p = new Bishop (i, j, color, "bishop");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);
                    boardBackup.insert({{i,j}, p});

                }
                
                if (i==4){
                    Piece* p = new King (i, j, color, "king");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);
                    boardBackup.insert({{i,j}, p});

                }
                if (i==3){
                    Piece* p = new Queen (i, j, color, "queen");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);
                    boardBackup.insert({{i,j}, p});

                }
            }
        }
        
    }
}

//find moves method
//vector has two vector entries, first available moves with blue (no attack)
// next available moves with red, which can attack others.

vector <vector <pair <int, int>>> Pawn :: moves (){
    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;

    pair <int, int> currentPosition = {i, j};
    int next = j-1;
    if (color == 1) {
        next = j+1;
    }

    if (findPiece({i, next}) == nullptr){
        availables.push_back({i, next});
    }

    if (i+1 < 8 && findPiece({i+1, next}) != nullptr) {
        Piece* p = findPiece({i+1, next});
        if (p->getColor() != color){ // different color piece, can be attacked
            attacks.push_back({i+1, next});
        }
    }

    if (i-1 >=0 && findPiece({i-1, next}) != nullptr) {
        Piece* p = findPiece({i-1, next});
        if (p->getColor() != color){ // different color piece, can be attacked
            attacks.push_back({i-1, next});
        }
    }

    for (auto x: availables){
        cout << x.first << " " << x.second << endl;
    }
    for (auto x: attacks){
        cout << x.first << " " << x.second << endl;
    }

    rt[0] = availables;
    rt[1] = attacks;

    return rt;
    
}


vector <vector <pair <int, int>>> King :: moves (){
    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;

    pair <int, int> currentPosition = {i, j};
    
    for (int x = i-1; x<=i+1; x++){
        if (x < 0 || x>7) continue;
        for (int y = j-1; y<=j+1; y++){
            if (y<0 || y>7) continue;
            if (x == i && y == j) continue;
            Piece* n = findPiece({x,y});
            if (n == nullptr){
                availables.push_back({x,y});
            
            } else {
                if (n->getColor() != color){
                    attacks.push_back({x,y});
                }
            }
        }
    }


    for (auto x: availables){
        cout << x.first << " " << x.second << endl;
    }
    for (auto x: attacks){
        cout << x.first << " " << x.second << endl;
    }

    rt[0] = availables;
    rt[1] = attacks;

    return rt;
    
}

vector <vector <pair <int, int>>> knightHelper (Piece* t, int i, int j, bool isUp){
    int a=j, b=i;
    if (isUp){
        a = i;
        b = j;
    }

    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;

    if (a<8 && a>=0){

        if (b >= 0 && b <8){
            Piece *p;
            if (isUp) p = findPiece({a,b});
            else p = findPiece({b,a});
            if (p != nullptr){
                if (p->getColor() != t->getColor()){
                    if (isUp)  attacks.push_back({a,b});
                    else attacks.push_back({b,a});
                }
            } else {
                if (isUp)  availables.push_back({a,b});
                    else availables.push_back({b,a});
            }
        }
    }

    rt[0] = availables;
    rt[1] = attacks;

    return rt;


}

vector <vector <pair <int, int>>> Knight :: moves (){
    vector <vector <pair <int, int>>> rt (2);
    vector <vector <pair <int, int>>> temp;

    int iArray[] = {i+2, i+2, i-2, i-2, i+1, i-1, i+1, i-1};
    int jArray[] = {j+1, j-1, j+1, j-1, j+2, j+2, j-2, j-2};
    bool bArray[] = {true, true, true, true, false, false, false, false};

    for (int a =0; a<8; a++){
        temp = knightHelper(this, iArray[a], jArray[a], bArray[a]);
        for (auto x: temp[0]) rt[0].push_back(x);
        for (auto x: temp[1]) rt[1].push_back(x);
    }
    
    return rt;
    
}

vector <vector <pair <int, int>>> bishopHelper(Piece* t, int i, int j){
    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;

    //four segments for up-right, up-left, down-right and down-left
    for (int a = 1; a<8; a++){
        if (i+a > 7 || j +a > 7) break;
        Piece *p = findPiece({i+a, j+a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i+a, j+a});
            }
            break;
        }
        availables.push_back({i+a, j+a});
    }

    for (int a = 1; a<8; a++){
        if (i-a <0 || j -a < 0) break;
        Piece *p = findPiece({i-a, j-a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i-a, j-a});
            }
            break;
        }
        availables.push_back({i-a, j-a});
    }

    for (int a = 1; a<8; a++){
        if (i+a > 7 || j -a < 0) break;
        Piece *p = findPiece({i+a, j-a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i+a, j-a});
            }
            break;
        }
        availables.push_back({i+a, j-a});
    }

    for (int a = 1; a<8; a++){
        if (i-a < 0 || j +a > 7) break;
        Piece *p = findPiece({i-a, j+a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i-a, j+a});
            }
            break;
        }
        availables.push_back({i-a, j+a});
    }


    rt[0] = availables;
    rt[1] = attacks;

    return rt;
    

}

vector <vector <pair <int, int>>> Bishop :: moves (){
    // vector <vector <pair <int, int>>> rt (2);

    // // pair <int, int> currentPosition = {i, j};
    
    // rt = bishopHelper(this, i, j);

    // return rt;
    return bishopHelper(this, i, j);
    
}

vector <vector <pair <int, int>>> rookHelper(Piece* t, int i, int j){
    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;
    

    //four segments for up-right, up-left, down-right and down-left
    for (int a = 1; a<8; a++){
        if (i+a > 7) break;
        Piece *p = findPiece({i+a, j});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i+a, j});
            }
            break;
        }
        availables.push_back({i+a, j});
    }

    for (int a = 1; a<8; a++){
        if (i-a <0) break;
        Piece *p = findPiece({i-a, j});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i-a, j});
            }
            break;
        }
        availables.push_back({i-a, j});
    }

    for (int a = 1; a<8; a++){
        if (j -a < 0) break;
        Piece *p = findPiece({i, j-a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i, j-a});
            }
            break;
        }
        availables.push_back({i, j-a});
    }

    for (int a = 1; a<8; a++){
        if (j +a > 7) break;
        Piece *p = findPiece({i, j+a});
        if (p != nullptr){
            if (p->getColor() != t->getColor()){
                attacks.push_back({i, j+a});
            }
            break;
        }
        availables.push_back({i, j+a});
    }

    rt[0] = availables;
    rt[1] = attacks;

    return rt;
}

vector <vector <pair <int, int>>> Rook :: moves (){
    return rookHelper(this, i, j);
    
}


vector <vector <pair <int, int>>> Queen :: moves (){

    vector <vector <pair <int, int>>> rt = rookHelper(this, i, j);
    vector <vector <pair <int, int>>> b = bishopHelper(this, i, j);
    for (auto x: b[0]){
        rt[0].push_back(x);
    }
    for (auto x: b[1]){
        rt[1].push_back(x);
    }

    return rt;
    
}
