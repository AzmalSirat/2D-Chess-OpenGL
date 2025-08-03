#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>
#include <bits/stdc++.h>


#include <GL/glut.h>

using namespace std;

double xt[] = {1.4,1,0.5,0.2,-0.2,-0.6,-1,-1.4};
double yt[] = {1.3,0.9,0.4,0,-0.3,-0.7,-1.2,-1.7};


class Piece {
    protected:
    int x, y; // which position in the board it is in
    int i, j; // relative position
    int color; // 0 for black, 1 for white;
    string name; // name of the piece

    public:
    Piece() : x(0), y(0), color(0), name("") {}

    Piece(int i, int j, int color, string name){
        this->i = i;
        this->j = j;
        this->color = color;
        this->name = name;
        this->x = -7 + 2*i;
        this->y = -7 + 2*j;
    }
    void setPosition (int x, int y){
        this->x = x;
        this->y = y;
    }

    pair <int, int> getPosition(){
        return {i,j};
    }

    void print(){
        cout << name << " selected at pos " << i << j << endl;
    }

    void setIndex (int i, int j){
        this->i = i;
        this->j = j;
        updatePosition();
    }
    void updatePosition(){
        this->x = -7 + 2*i;
        this->y = -7 + 2*j;
    }
    int getColor () {
        return color;
    }
    virtual void draw() = 0;
    virtual vector <vector <pair <int, int>>> moves () = 0;

    void drawHelper(){
        glColor3f(color, color, color);
        // glPushMatrix();
        glTranslatef(xt[i], yt[j], 0.1);  // Move piece slightly above the square
              
    }
};

class King : public Piece {
    public:
    
    King(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};

class Queen : public Piece {
    public:
    
    Queen(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};

class Bishop : public Piece {
    public:
    
    Bishop(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};

class Rook : public Piece {
    public:
    
    Rook(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};

class Knight : public Piece {
    public:
    
    Knight(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};

class Pawn : public Piece {
    public:
    
    Pawn(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
    vector <vector <pair <int, int>>> moves () override;
};