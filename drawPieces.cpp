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
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 1.6 units, so shift up by 0.8 to center
    
    // Draw base (smallest piece) - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.8, 0);  // Move to center
    drawRectangle(1.0, 0.2);
    glPopMatrix();
    
    // Draw body
    glPushMatrix();
    glTranslatef(0, -0.3 + 0.8, 0);  // Move to center
    drawRectangle(0.6, 0.8);
    glPopMatrix();
    
    // Draw head
    glPushMatrix();
    glTranslatef(0, 0.4 + 0.8, 0);  // Move to center
    drawCircle(0.3, 16);
    glPopMatrix();
}

void drawRook() {
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 1.75 units, so shift up by appropriate amount to center
    
    // Draw base - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.875, 0);  // Move to center
    drawRectangle(1.2, 0.2);
    glPopMatrix();
    
    // Draw main body
    glPushMatrix();
    glTranslatef(0, -0.1 + 0.875, 0);  // Move to center
    drawRectangle(0.8, 1.0);
    glPopMatrix();
    
    // Draw top crenellations
    glPushMatrix();
    glTranslatef(-0.3, 0.6 + 0.875, 0);  // Move to center
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.6 + 0.875, 0);  // Move to center
    drawRectangle(0.15, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 0.6 + 0.875, 0);  // Move to center
    drawRectangle(0.15, 0.3);
    glPopMatrix();
}

void drawKnight() {
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 1.9 units, so shift up by 0.95 to center
    
    // Draw base - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 0.95, 0);  // Move to center
    drawRectangle(1.2, 0.2);
    glPopMatrix();
    
    // Draw main body/neck
    glPushMatrix();
    glTranslatef(0, -0.25 + 0.95, 0);  // Move to center
    drawRectangle(0.8, 0.7);
    glPopMatrix();
    
    // Draw horse head - main part
    glPushMatrix();
    glTranslatef(0.2, 0.35 + 0.95, 0);  // Move to center
    drawRectangle(0.8, 0.5);
    glPopMatrix();
    
    // Draw horse snout/nose
    glPushMatrix();
    glTranslatef(0.5, 0.15 + 0.95, 0);  // Move to center
    drawRectangle(0.4, 0.25);
    glPopMatrix();
    
    // Draw horse ears
    glPushMatrix();
    glTranslatef(0.1, 0.7 + 0.95, 0);  // Move to center
    drawTriangle(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 0.7 + 0.95, 0);  // Move to center
    drawTriangle(0.2);
    glPopMatrix();
    
    // Draw mane - multiple segments for better look
    glPushMatrix();
    glTranslatef(-0.2, 0.5 + 0.95, 0);  // Move to center
    drawRectangle(0.12, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.3, 0.2 + 0.95, 0);  // Move to center
    drawRectangle(0.12, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.25, -0.1 + 0.95, 0);  // Move to center
    drawRectangle(0.12, 0.25);
    glPopMatrix();
    
    // Draw eye
    glPushMatrix();
    glTranslatef(0.3, 0.45 + 0.95, 0);  // Move to center
    drawCircle(0.06, 8);
    glPopMatrix();
    
    // Draw nostril
    glPushMatrix();
    glTranslatef(0.6, 0.05 + 0.95, 0);  // Move to center
    drawCircle(0.04, 6);
    glPopMatrix();
}

void drawBishop() {
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 2.25 units (with cross), so shift up by 1.125 to center
    
    // Draw base - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 1.125, 0);  // Move to center
    drawRectangle(1.2, 0.2);
    glPopMatrix();
    
    // Draw base ring
    glPushMatrix();
    glTranslatef(0, -0.7 + 1.125, 0);  // Move to center
    drawRectangle(1.0, 0.1);
    glPopMatrix();
    
    // Draw lower body (tapered)
    glPushMatrix();
    glTranslatef(0, -0.35 + 1.125, 0);  // Move to center
    drawRectangle(0.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.0 + 1.125, 0);  // Move to center
    drawRectangle(0.7, 0.3);
    glPopMatrix();
    
    // Draw middle section
    glPushMatrix();
    glTranslatef(0, 0.2 + 1.125, 0);  // Move to center
    drawRectangle(0.6, 0.25);
    glPopMatrix();
    
    // Draw upper body (more elegant taper)
    glPushMatrix();
    glTranslatef(0, 0.4 + 1.125, 0);  // Move to center
    drawRectangle(0.5, 0.3);
    glPopMatrix();
    
    // Draw mitre base
    glPushMatrix();
    glTranslatef(0, 0.6 + 1.125, 0);  // Move to center
    drawRectangle(0.7, 0.15);
    glPopMatrix();
    
    // Draw mitre (bishop's hat) - more elegant shape
    glPushMatrix();
    glTranslatef(0, 0.8 + 1.125, 0);  // Move to center
    glScalef(0.8, 1.0, 1);
    drawTriangle(0.4);
    glPopMatrix();
    
    // Draw mitre decoration
    glPushMatrix();
    glTranslatef(0, 0.68 + 1.125, 0);  // Move to center
    drawRectangle(0.6, 0.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.75 + 1.125, 0);  // Move to center
    drawRectangle(0.5, 0.05);
    glPopMatrix();
    
    // Draw cross on top - more proportional
    glPushMatrix();
    glTranslatef(0, 1.0 + 1.125, 0);  // Move to center
    drawRectangle(0.06, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 1.05 + 1.125, 0);  // Move to center
    drawRectangle(0.15, 0.06);
    glPopMatrix();
    
    // Add small decorative elements
    glPushMatrix();
    glTranslatef(0, 0.35 + 1.125, 0);  // Move to center
    drawCircle(0.08, 8);
    glPopMatrix();
}

void drawQueen() {
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 2.4 units, so shift up by 1.2 to center
    
    // Draw ornate base - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 1.2, 0);  // Move to center
    drawRectangle(1.4, 0.2);
    glPopMatrix();
    
    // Draw base rings for elegance
    glPushMatrix();
    glTranslatef(0, -0.65 + 1.2, 0);  // Move to center
    drawRectangle(1.2, 0.1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -0.55 + 1.2, 0);  // Move to center
    drawRectangle(1.0, 0.08);
    glPopMatrix();
    
    // Draw lower body with elegant taper
    glPushMatrix();
    glTranslatef(0, -0.25 + 1.2, 0);  // Move to center
    drawRectangle(0.9, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.05 + 1.2, 0);  // Move to center
    drawRectangle(0.8, 0.3);
    glPopMatrix();
    
    // Draw waist
    glPushMatrix();
    glTranslatef(0, 0.25 + 1.2, 0);  // Move to center
    drawRectangle(0.65, 0.2);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 0.45 + 1.2, 0);  // Move to center
    drawRectangle(0.7, 0.25);
    glPopMatrix();
    
    // Draw crown base with ornate design
    glPushMatrix();
    glTranslatef(0, 0.65 + 1.2, 0);  // Move to center
    drawRectangle(0.9, 0.15);
    glPopMatrix();
    
    // Draw crown band
    glPushMatrix();
    glTranslatef(0, 0.75 + 1.2, 0);  // Move to center
    drawRectangle(0.85, 0.1);
    glPopMatrix();
    
    // Draw crown points with varied heights for elegance
    for (int i = -3; i <= 3; i++) {
        glPushMatrix();
        glTranslatef(i * 0.12, 0.85 + 1.2, 0);  // Move to center
        double height;
        if (i == 0) height = 0.3;          // Center tallest
        else if (abs(i) == 1) height = 0.25;  // Next to center
        else if (abs(i) == 2) height = 0.2;  // Sides
        else height = 0.15;                    // Outer edges
        
        drawRectangle(0.06, height);
        glPopMatrix();
        
        // Add small circles on top of crown points
        if (abs(i) <= 2) {
            glPushMatrix();
            glTranslatef(i * 0.12, 0.85 + 1.2 + height/2 + 0.05, 0);  // Move to center
            drawCircle(0.04, 6);
            glPopMatrix();
        }
    }
    
    // Add decorative elements on the body
    glPushMatrix();
    glTranslatef(0, 0.4 + 1.2, 0);  // Move to center
    drawCircle(0.1, 8);
    glPopMatrix();
    
    // Add side decorations
    glPushMatrix();
    glTranslatef(-0.25, 0.4 + 1.2, 0);  // Move to center
    drawCircle(0.06, 6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, 0.4 + 1.2, 0);  // Move to center
    drawCircle(0.06, 6);
    glPopMatrix();
    
    // Add decorative band around waist
    glPushMatrix();
    glTranslatef(0, 0.25 + 1.2, 0);  // Move to center
    drawRectangle(0.7, 0.04);
    glPopMatrix();
}

void drawKing() {
    // Center the piece vertically within (-1,-1) to (1,1) square
    // Total height is about 2.55 units (tallest piece), so shift up by 1.275 to center
    
    // Draw base (tallest piece) - centered
    glPushMatrix();
    glTranslatef(0, -0.8 + 1.275, 0);  // Move to center
    drawRectangle(1.4, 0.2);
    glPopMatrix();
    
    // Draw lower body
    glPushMatrix();
    glTranslatef(0, -0.3 + 1.275, 0);  // Move to center
    drawRectangle(0.9, 0.6);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 0.15 + 1.275, 0);  // Move to center
    drawRectangle(0.7, 0.5);
    glPopMatrix();
    
    // Draw crown base
    glPushMatrix();
    glTranslatef(0, 0.5 + 1.275, 0);  // Move to center
    drawRectangle(0.9, 0.25);
    glPopMatrix();
    
    // Draw crown points
    for (int i = -2; i <= 2; i++) {
        glPushMatrix();
        glTranslatef(i * 0.18, 0.75 + 1.275, 0);  // Move to center
        double height = (abs(i) <= 1) ? 0.3 : 0.2;
        drawRectangle(0.1, height);
        glPopMatrix();
    }
    
    // Draw cross on top
    glPushMatrix();
    glTranslatef(0, 1.1 + 1.275, 0);  // Move to center
    drawRectangle(0.06, 0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 1.15 + 1.275, 0);  // Move to center
    drawRectangle(0.2, 0.06);
    glPopMatrix();
}
