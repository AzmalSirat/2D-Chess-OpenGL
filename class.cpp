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

    Piece(int x, int y, int color, string name){
        this->x = x;
        this->y = y;
        this->color = color;
        this->name = name;
        this->i = (x+7)/2;
        this->j = (y+7)/2;
    }
    void setPosition (int x, int y){
        this->x = x;
        this->y = y;
    }
    virtual void draw() = 0;

    void drawHelper(){
        glColor3f(color, color, color);
        // glPushMatrix();
        glTranslatef(xt[i], yt[j], 0.1);  // Move piece slightly above the square
        if (color == 0) {
            glScalef(-1,-1,1);
            glTranslatef(0,-0.25,0.001);
        }        
    }
};

class King : public Piece {
    public:
    
    King(int x, int y, int color, string name) : Piece(x, y, color, name) {
        // Constructor body can be empty since base constructor handles everything
    }
    void draw() override;
};

               
        // glPushMatrix();
        // glTranslatef(x,y,0.01);
        // drawHelper();
        // drawKing();
        // glPopMatrix();
