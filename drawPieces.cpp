#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>
#include <bits/stdc++.h>


#include <GL/glut.h>
#define pi (2*acos(0.0))

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
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw base - scaled to Rook size and moved down 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);  // Match Rook base width
    glPopMatrix();
    
    // Draw body - scaled proportionally
    glPushMatrix();
    glTranslatef(0, -0.3 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 1.0);  // Scale to match Rook proportions
    glPopMatrix();
    
    // Draw head - scaled proportionally
    glPushMatrix();
    glTranslatef(0, 0.4 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.35, 16);  // Scale up to match Rook height
    glPopMatrix();
}

void drawRook() {
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw base - moved down by 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);
    glPopMatrix();
    
    // Draw main body
    glPushMatrix();
    glTranslatef(0, -0.1 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 1.0);
    glPopMatrix();
    
    // Draw top crenellations
    glPushMatrix();
    glTranslatef(-0.3, 0.6 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.6 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 0.6 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.15, 0.3);
    glPopMatrix();
}

void drawKnight() {
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw base - scaled to Rook size and moved down 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);  // Match Rook base
    glPopMatrix();
    
    // Draw main body/neck - scaled proportionally
    glPushMatrix();
    glTranslatef(0, -0.25 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.65);  // Scale to fit Rook height
    glPopMatrix();
    
    // Draw horse head - main part
    glPushMatrix();
    glTranslatef(0.15, 0.25 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1, scale proportionally
    drawRectangle(0.6, 0.4);
    glPopMatrix();
    
    // Draw horse snout/nose
    glPushMatrix();
    glTranslatef(0.35, 0.1 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.3, 0.2);
    glPopMatrix();
    
    // Draw horse ears
    glPushMatrix();
    glTranslatef(0.07, 0.55 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawTriangle(0.15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.23, 0.55 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawTriangle(0.15);
    glPopMatrix();
    
    // Draw mane - multiple segments for better look
    glPushMatrix();
    glTranslatef(-0.15, 0.4 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.1, 0.25);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.22, 0.15 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.1, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.18, -0.07 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.1, 0.18);
    glPopMatrix();
    
    // Draw eye
    glPushMatrix();
    glTranslatef(0.22, 0.33 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.045, 8);
    glPopMatrix();
    
    // Draw nostril
    glPushMatrix();
    glTranslatef(0.42, 0.03 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.03, 6);
    glPopMatrix();
}

void drawBishop() {
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw base - scaled to Rook size and moved down 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);  // Match Rook base
    glPopMatrix();
    
    // Draw base ring
    glPushMatrix();
    glTranslatef(0, -0.7 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.0, 0.08);
    glPopMatrix();
    
    // Draw lower body (tapered) - scaled down
    glPushMatrix();
    glTranslatef(0, -0.35 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.0 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.7, 0.23);
    glPopMatrix();
    
    // Draw middle section
    glPushMatrix();
    glTranslatef(0, 0.2 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.6, 0.19);
    glPopMatrix();
    
    // Draw upper body (more elegant taper)
    glPushMatrix();
    glTranslatef(0, 0.4 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.5, 0.23);
    glPopMatrix();
    
    // Draw mitre base
    glPushMatrix();
    glTranslatef(0, 0.6 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.7, 0.12);
    glPopMatrix();
    
    // Draw mitre (bishop's hat) - scaled down
    glPushMatrix();
    glTranslatef(0, 0.75 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    glScalef(0.8, 1.0, 1);
    drawTriangle(0.25);  // Scale down triangle
    glPopMatrix();
    
    // Draw mitre decoration
    glPushMatrix();
    glTranslatef(0, 0.68 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.6, 0.04);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.72 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.5, 0.04);
    glPopMatrix();
    
    // Draw cross on top - smaller to fit Rook height
    glPushMatrix();
    glTranslatef(0, 0.82 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.05, 0.12);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.85 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.12, 0.05);
    glPopMatrix();
    
    // Add small decorative elements
    glPushMatrix();
    glTranslatef(0, 0.35 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.06, 8);
    glPopMatrix();
}

void drawQueen() {
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw ornate base - scaled to Rook size and moved down 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);  // Match Rook base
    glPopMatrix();
    
    // Draw base rings for elegance
    glPushMatrix();
    glTranslatef(0, -0.65 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.0, 0.08);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -0.55 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.9, 0.06);
    glPopMatrix();
    
    // Draw lower body with elegant taper - scaled down
    glPushMatrix();
    glTranslatef(0, -0.25 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.05 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.7, 0.22);
    glPopMatrix();
    
    // Draw waist
    glPushMatrix();
    glTranslatef(0, 0.25 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.55, 0.15);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 0.4 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.6, 0.18);
    glPopMatrix();
    
    // Draw crown base with ornate design
    glPushMatrix();
    glTranslatef(0, 0.55 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.11);
    glPopMatrix();
    
    // Draw crown band
    glPushMatrix();
    glTranslatef(0, 0.63 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.75, 0.07);
    glPopMatrix();
    
    // Draw crown points with varied heights for elegance - scaled down
    for (int i = -3; i <= 3; i++) {
        glPushMatrix();
        glTranslatef(i * 0.09, 0.7 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
        double height;
        if (i == 0) height = 0.18;          // Center tallest
        else if (abs(i) == 1) height = 0.15;  // Next to center
        else if (abs(i) == 2) height = 0.12;  // Sides
        else height = 0.09;                    // Outer edges
        
        drawRectangle(0.04, height);
        glPopMatrix();
        
        // Add small circles on top of crown points
        if (abs(i) <= 2) {
            glPushMatrix();
            glTranslatef(i * 0.09, 0.7 + 0.875 - 0.5 - 0.1 + height/2 + 0.03, 0);  // Move down by 0.5 + 0.1
            drawCircle(0.025, 6);
            glPopMatrix();
        }
    }
    
    // Add decorative elements on the body
    glPushMatrix();
    glTranslatef(0, 0.35 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.07, 8);
    glPopMatrix();
    
    // Add side decorations
    glPushMatrix();
    glTranslatef(-0.18, 0.35 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.04, 6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.18, 0.35 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawCircle(0.04, 6);
    glPopMatrix();
    
    // Add decorative band around waist
    glPushMatrix();
    glTranslatef(0, 0.25 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.6, 0.03);
    glPopMatrix();
}

void drawKing() {
    // Scale and move down by additional 0.1
    glScalef(0.6, 0.6, 1);  // Scale to 60%
    
    // Draw base (tallest piece) - scaled to Rook size and moved down 0.5 + 0.1
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(1.2, 0.2);  // Match Rook base
    glPopMatrix();
    
    // Draw lower body - scaled down
    glPushMatrix();
    glTranslatef(0, -0.3 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.45);
    glPopMatrix();
    
    // Draw upper body - scaled down
    glPushMatrix();
    glTranslatef(0, 0.1 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.6, 0.35);
    glPopMatrix();
    
    // Draw crown base - scaled down
    glPushMatrix();
    glTranslatef(0, 0.4 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.8, 0.18);
    glPopMatrix();
    
    // Draw crown points - scaled down
    for (int i = -2; i <= 2; i++) {
        glPushMatrix();
        glTranslatef(i * 0.13, 0.6 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
        double height = (abs(i) <= 1) ? 0.18 : 0.12;
        drawRectangle(0.07, height);
        glPopMatrix();
    }
    
    // Draw cross on top - scaled down to fit Rook height
    glPushMatrix();
    glTranslatef(0, 0.78 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.04, 0.15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.82 + 0.875 - 0.5 - 0.1, 0);  // Move down by 0.5 + 0.1
    drawRectangle(0.12, 0.04);
    glPopMatrix();
}
