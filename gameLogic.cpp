#include "drawPieces.cpp"

vector <Piece*> pieces, backup;
map <pair <int, int>, Piece*> boardMap, boardBackup;
vector <pair <int, int>> availables;
vector <pair <int, int>> attacks;
pair <int, int> selected = {-1,-1};
vector <pair <int, int>> previous = {{-1, -1}, {-1,-1}};
bool currentCheck = false;
extern int current;


Piece* findPiece(pair <int, int> p){
	auto it = boardMap.find({p});
	if (it != boardMap.end()){
		return it->second;
	}
	return nullptr;
}

Piece* findBackup(pair <int, int> p){
	auto it = boardBackup.find({p});
	if (it != boardBackup.end()){
		return it->second;
	}
	return nullptr;
}

void movePieceBackup(Piece* p, int i, int j){
    pair <int, int> current = p->getPosition();
    
    auto iterator = boardBackup.find({i,j});
    if (iterator != boardBackup.end()){
        boardBackup.erase({i,j});
        cout << "erased from " << i << j << " prev one..\n";
    }
        

    auto it = boardBackup.find(current);
    if (it != boardBackup.end()){
        boardBackup.erase(current);
        cout << "erased from " << current.first << current.second << " next\n";
    }
        
    
    boardBackup.insert({{i, j}, p});
    cout << boardBackup[{i,j}]->getName() << endl;
}

bool kingCheckRook(int color, int i, int j){
    for (int a=1; i+a < 8; a++){
        Piece* p = findBackup({i+a, j});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "rook" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }

    for (int a=1; i-a >=0; a++){
        Piece* p = findBackup({i-a, j});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "rook" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }

    for (int a=1; j+a < 8; a++){
        Piece* p = findBackup({i, j+a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "rook" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }

    for (int a=1; j-a >= 0; a++){
        Piece* p = findBackup({i, j-a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "rook" || p->getName() == "queen")){
                return true;
            }
            break; // not check by rook or queen acting as rook
        }
    }
    return false;
}

bool kingCheckBishop (int color, int i, int j){
    for (int a=1; i+a < 8 && j+a < 8; a++){
        Piece* p = findBackup({i+a, j+a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "bishop" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }
    for (int a=1; i-a >= 0 && j-a >= 0; a++){
        Piece* p = findBackup({i-a, j-a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "bishop" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }
    for (int a=1; i+a < 8 && j-a >=0; a++){
        Piece* p = findBackup({i+a, j-a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "bishop" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }
    for (int a=1; i-a >= 0 && j+a < 8; a++){
        Piece* p = findBackup({i-a, j+a});
        if (p != nullptr){
            if (p->getColor() != color && (p->getName()== "bishop" || p->getName() == "queen")){
                return true;
            }
            break; // check other options for check...
        }
    }
    return false;
}

bool kingCheckPawn(int color, int i,int j){
    int next = j-1;
    if (color == 1) {
        next = j+1;
    }
    if (i+1 < 8){
        Piece* p = findBackup({i+1, next});
        if (p != nullptr){
            if (p->getColor() != color && p->getName()== "pawn"){
                return true;
            }
        }
    }
    if (i-1 >= 0){
        Piece* p = findBackup({i-1, next});
        if (p != nullptr){
            if (p->getColor() != color && p->getName()== "pawn"){
                return true;
            }
        }
    }
    return false;
    
}

bool kingCheckKnight(int color, int i,int j){
    //all possible attacking positions of the knight
    int x[] = {i+2, i+2, i-2, i-2, i+1, i+1, i-1, i-1};
    int y[] = {j+1, j-1, j+1, j-1, j+2, j-2, j+2, j-2};
    for (int k=0; k<8; k++){
        if (x[k] >= 8 || x[k] <0 ||y[k] >= 8 || y[k] <0 ){
            continue;
        } 
        Piece* p = findBackup({x[k], y[k]});
        if (p!= nullptr) {
            if (p->getColor() != color && p->getName() == "knight" ){
                return true;
            }
        }
    }
    return false;
}


bool kingCheck (int color){
    Piece* king = nullptr;
    for (auto x: pieces){
        if (x->getColor() == color && x->getName()=="king"){
            king = x;
            break;
        }
    }

    pair <int, int> pos;
    //traverse map to find king's position
    for (auto x: boardBackup){
        if (x.second == king){
            pos = x.first;
            break;
        }
    }
    int i = pos.first;
    int j = pos.second;
    // cout << "King position established at " << i << ", " << j << endl; 

    // then check if any attacking piece in positions to attack...
    // if any rook or queen next piece in column or row, check
    bool rookCheck = kingCheckRook(color, i, j);
    if (rookCheck) return true;
    bool bishopCheck = kingCheckBishop(color, i, j);
    if (bishopCheck) return true;
 
    bool pawnCheck = kingCheckPawn(color, i, j);
    if (pawnCheck) return true;

    bool knightCheck = kingCheckKnight(color, i, j);
    if (knightCheck) return true;

    // add Knight check logic

    return false;

}

bool checkMate(int color){
    vector <vector <pair <int, int>>> moves;
    for (auto x: pieces){
        if (x->getColor() == color){
            moves = x->moves();
            // at least one move available which removes the check
            if (moves[0].size() > 0 || moves[1].size()>0){
                return false;
            }
        }
    }
    return true;
}

// t = this, p = piece on (i,j)
//true if need to traverse more
//t = this
bool updateVectors (Piece* t, Piece* p, int i, int j, vector <pair <int, int>>& availables, vector <pair <int, int>>& attacks){
    // cout << "entered update funct" << i << j << endl;
    boardBackup = boardMap;
    // Store original position for restoration
    pair<int, int> originalPos = t->getPosition();
    

    if (p != nullptr){
        if (p->getColor() != t->getColor()){
            //checking if making this move (in the backup) results in check for my king.
            movePieceBackup(t, i, j);
            if (kingCheck(t->getColor()) == false ){
                cout << "checking for update for attack " << t->getName() << i << j << endl; 
                attacks.push_back({i, j});
            }
            t->setIndex(originalPos.first, originalPos.second);
        }
        boardBackup = boardMap;
        //updated attacks, or same color piece at first, so no need to traverse ahead.
        return false;
    } else{
        movePieceBackup(t, i, j);
        if (kingCheck(t->getColor()) == false ){
            availables.push_back({i, j});
        }
        t->setIndex(originalPos.first, originalPos.second);
    }
    boardBackup = boardMap;
    return true;
}

pair <int, int> findKingPosition (){
    Piece* king = nullptr;
    for (auto x: pieces){
        if (x->getColor() == current && x->getName()=="king"){
            king = x;
            break;
        }
    }

    //traverse map to find king's position
    for (auto x: boardMap){
        if (x.second == king){
            return x.first;
        }
    }
    return {-1,-1};
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
    pair <int, int> kingPosition = {-1,-1}; // if check, red..

    if (currentCheck == true) {
        kingPosition = findKingPosition();
        cout << kingPosition.first << kingPosition.second << endl;
    }

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
                else if (currentCheck && i == kingPosition.first && j == kingPosition.second){
                    double clr[] = {1,0.15,0.15};
                    highlight(clr);
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
                        double clr[] = {1, 0.5, 0};
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
        // cout << "trying to draw at " << x << y << " green" << endl;
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
                    boardMap.insert({{i,j}, p});
                    
                }
                if (i==1 || i==6){
                    Piece* p = new Knight (i, j, color, "knight");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);

                }
                if (i==2 || i==5){
                    Piece* p = new Bishop (i, j, color, "bishop");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);

                }
                
                if (i==4){
                    Piece* p = new King (i, j, color, "king");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);

                }
                if (i==3){
                    Piece* p = new Queen (i, j, color, "queen");
                    pieces.push_back(p);
                    boardMap.insert({{i,j}, p});
                    backup.push_back(p);

                }
            }
        }
        
    }
    boardBackup = boardMap;
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

    Piece* p = findPiece({i,next});

    if (p==nullptr){
        updateVectors(this, p, i, next, availables, attacks);

        p = findPiece({i,next+1});
        if (p == nullptr && color == 1 && j == 1){ // first move for white
            updateVectors(this, p, i, next+1, availables, attacks);
        }
        p = findPiece({i,next-1});
        if (p == nullptr && color == 0 && j == 6){ // first move for black
            updateVectors(this, p, i, next-1, availables, attacks);
        }
    }
        

    if (i+1 < 8 && findPiece({i+1, next}) != nullptr) {
        p = findPiece({i+1, next});
        updateVectors(this, p, i+1, next, availables, attacks);
    }

    if (i-1 >=0 && findPiece({i-1, next}) != nullptr) {
        p = findPiece({i-1, next});
        updateVectors(this, p, i-1, next, availables, attacks);
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
            Piece* p = findPiece({x,y});
            updateVectors(this, p, x,y, availables, attacks);
        }
    }

    rt[0] = availables;
    rt[1] = attacks;

    return rt;
    
}

vector <vector <pair <int, int>>> knightHelper (Piece* t, int i, int j){

    vector <vector <pair <int, int>>> rt (2);
    vector <pair <int, int>> availables;
    vector <pair <int, int>> attacks;

    if (i<8 && i>=0){
        if (j >= 0 && j <8){
            Piece *p;
            p = findPiece({i,j});
            updateVectors(t, p, i, j, availables, attacks);
        
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

    for (int a =0; a<8; a++){
        temp = knightHelper(this, iArray[a], jArray[a]);
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
        if (updateVectors(t, p, i+a, j+a, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (i-a <0 || j -a < 0) break;
        Piece *p = findPiece({i-a, j-a});
        if (updateVectors(t, p, i-a, j-a, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (i+a > 7 || j -a < 0) break;
        Piece *p = findPiece({i+a, j-a});
        if (updateVectors(t, p, i+a, j-a, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (i-a < 0 || j +a > 7) break;
        Piece *p = findPiece({i-a, j+a});
        if (updateVectors(t, p, i-a, j+a, availables, attacks) == false){
            break;
        }
    }
    rt[0] = availables;
    rt[1] = attacks;

    return rt;
}

vector <vector <pair <int, int>>> Bishop :: moves (){
    
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
        if (updateVectors(t, p, i+a, j, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (i-a <0) break;
        Piece *p = findPiece({i-a, j});
        if (updateVectors(t, p, i-a, j, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (j -a < 0) break;
        Piece *p = findPiece({i, j-a});
        if (updateVectors(t, p, i, j-a, availables, attacks) == false){
            break;
        }
    }

    for (int a = 1; a<8; a++){
        if (j +a > 7) break;
        Piece *p = findPiece({i, j+a});
        if (updateVectors(t, p, i, j+a, availables, attacks) == false){
            break;
        }
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

Piece* checkPawn(Piece* p, pair <int, int> pos){
    if (p->getName() != "pawn") return nullptr;
    int color = p->getColor();
    if ((color == 1 && pos.second == 7) || (color == 0 && pos.second == 0) ) { // white pawn reached 7th row
        Piece *queen = new Queen (pos.first, pos.second, color, "queen");
        return queen;
    }
    return nullptr; 
}

