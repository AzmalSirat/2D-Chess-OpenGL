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
    // Draw base (smallest piece)
    drawRectangle(0.3, 0.08);
    
    // Draw body
    glPushMatrix();
    glTranslatef(0, 0.15, 0);
    drawRectangle(0.18, 0.25);
    glPopMatrix();
    
    // Draw head
    glPushMatrix();
    glTranslatef(0, 0.35, 0);
    drawCircle(0.1, 16);
    glPopMatrix();
}

void drawRook() {
    // Draw base
    drawRectangle(0.35, 0.08);
    
    // Draw main body
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
    drawRectangle(0.25, 0.32);
    glPopMatrix();
    
    // Draw top crenellations
    glPushMatrix();
    glTranslatef(-0.08, 0.4, 0);
    drawRectangle(0.04, 0.08);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.4, 0);
    drawRectangle(0.04, 0.08);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.08, 0.4, 0);
    drawRectangle(0.04, 0.08);
    glPopMatrix();
}

void drawKnight() {
    // Draw base
    drawRectangle(0.35, 0.08);
    
    // Draw main body/neck
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
    drawRectangle(0.25, 0.25);
    glPopMatrix();
    
    // Draw horse head - main part
    glPushMatrix();
    glTranslatef(0.06, 0.38, 0);
    drawRectangle(0.25, 0.18);
    glPopMatrix();
    
    // Draw horse snout/nose
    glPushMatrix();
    glTranslatef(0.15, 0.32, 0);
    drawRectangle(0.12, 0.09);
    glPopMatrix();
    
    // Draw horse ears
    glPushMatrix();
    glTranslatef(0.03, 0.5, 0);
    drawTriangle(0.08);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.09, 0.5, 0);
    drawTriangle(0.08);
    glPopMatrix();
    
    // Draw mane - multiple segments for better look
    glPushMatrix();
    glTranslatef(-0.06, 0.44, 0);
    drawRectangle(0.04, 0.12);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.09, 0.35, 0);
    drawRectangle(0.04, 0.15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.075, 0.26, 0);
    drawRectangle(0.04, 0.09);
    glPopMatrix();
    
    // Draw eye
    glPushMatrix();
    glTranslatef(0.09, 0.41, 0);
    drawCircle(0.025, 8);
    glPopMatrix();
    
    // Draw nostril
    glPushMatrix();
    glTranslatef(0.18, 0.29, 0);
    drawCircle(0.015, 6);
    glPopMatrix();
}

void drawBishop() {
    // Draw base with rounded corners effect
    drawRectangle(0.35, 0.08);
    
    // Draw base ring
    glPushMatrix();
    glTranslatef(0, 0.06, 0);
    drawRectangle(0.3, 0.03);
    glPopMatrix();
    
    // Draw lower body (tapered)
    glPushMatrix();
    glTranslatef(0, 0.15, 0);
    drawRectangle(0.24, 0.12);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.24, 0);
    drawRectangle(0.21, 0.09);
    glPopMatrix();
    
    // Draw middle section
    glPushMatrix();
    glTranslatef(0, 0.31, 0);
    drawRectangle(0.18, 0.075);
    glPopMatrix();
    
    // Draw upper body (more elegant taper)
    glPushMatrix();
    glTranslatef(0, 0.39, 0);
    drawRectangle(0.15, 0.09);
    glPopMatrix();
    
    // Draw mitre base
    glPushMatrix();
    glTranslatef(0, 0.45, 0);
    drawRectangle(0.21, 0.045);
    glPopMatrix();
    
    // Draw mitre (bishop's hat) - more elegant shape
    glPushMatrix();
    glTranslatef(0, 0.51, 0);
    glScalef(0.8, 1.0, 1);
    drawTriangle(0.15);
    glPopMatrix();
    
    // Draw mitre decoration
    glPushMatrix();
    glTranslatef(0, 0.48, 0);
    drawRectangle(0.18, 0.015);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.495, 0);
    drawRectangle(0.15, 0.015);
    glPopMatrix();
    
    // Draw cross on top - more proportional
    glPushMatrix();
    glTranslatef(0, 0.585, 0);
    drawRectangle(0.018, 0.075);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.6, 0);
    drawRectangle(0.054, 0.018);
    glPopMatrix();
    
    // Add small decorative elements
    glPushMatrix();
    glTranslatef(0, 0.375, 0);
    drawCircle(0.024, 8);
    glPopMatrix();
}

void drawQueen() {
    // Draw ornate base
    drawRectangle(0.42, 0.08);
    
    // Draw base rings for elegance
    glPushMatrix();
    glTranslatef(0, 0.06, 0);
    drawRectangle(0.36, 0.03);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.105, 0);
    drawRectangle(0.3, 0.024);
    glPopMatrix();
    
    // Draw lower body with elegant taper
    glPushMatrix();
    glTranslatef(0, 0.18, 0);
    drawRectangle(0.27, 0.12);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.27, 0);
    drawRectangle(0.24, 0.09);
    glPopMatrix();
    
    // Draw waist
    glPushMatrix();
    glTranslatef(0, 0.345, 0);
    drawRectangle(0.195, 0.06);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 0.42, 0);
    drawRectangle(0.21, 0.09);
    glPopMatrix();
    
    // Draw crown base with ornate design
    glPushMatrix();
    glTranslatef(0, 0.48, 0);
    drawRectangle(0.27, 0.045);
    glPopMatrix();
    
    // Draw crown band
    glPushMatrix();
    glTranslatef(0, 0.51, 0);
    drawRectangle(0.255, 0.03);
    glPopMatrix();
    
    // Draw crown points with varied heights for elegance
    for (int i = -3; i <= 3; i++) {
        glPushMatrix();
        glTranslatef(i * 0.036, 0.54, 0);
        double height;
        if (i == 0) height = 0.12;          // Center tallest
        else if (abs(i) == 1) height = 0.105;  // Next to center
        else if (abs(i) == 2) height = 0.075;  // Sides
        else height = 0.045;                    // Outer edges
        
        drawRectangle(0.018, height);
        glPopMatrix();
        
        // Add small circles on top of crown points
        if (abs(i) <= 2) {
            glPushMatrix();
            glTranslatef(i * 0.036, 0.54 + height/2 + 0.015, 0);
            drawCircle(0.012, 6);
            glPopMatrix();
        }
    }
    
    // Add decorative elements on the body
    glPushMatrix();
    glTranslatef(0, 0.405, 0);
    drawCircle(0.03, 8);
    glPopMatrix();
    
    // Add side decorations
    glPushMatrix();
    glTranslatef(-0.075, 0.405, 0);
    drawCircle(0.018, 6);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.075, 0.405, 0);
    drawCircle(0.018, 6);
    glPopMatrix();
    
    // Add decorative band around waist
    glPushMatrix();
    glTranslatef(0, 0.345, 0);
    drawRectangle(0.21, 0.012);
    glPopMatrix();
}

void drawKing() {
    // Draw base (tallest piece)
    drawRectangle(0.42, 0.08);
    
    // Draw lower body
    glPushMatrix();
    glTranslatef(0, 0.18, 0);
    drawRectangle(0.27, 0.18);
    glPopMatrix();
    
    // Draw upper body
    glPushMatrix();
    glTranslatef(0, 0.33, 0);
    drawRectangle(0.21, 0.15);
    glPopMatrix();
    
    // Draw crown base
    glPushMatrix();
    glTranslatef(0, 0.45, 0);
    drawRectangle(0.27, 0.075);
    glPopMatrix();
    
    // Draw crown points
    for (int i = -2; i <= 2; i++) {
        glPushMatrix();
        glTranslatef(i * 0.054, 0.525, 0);
        double height = (abs(i) <= 1) ? 0.09 : 0.06;
        drawRectangle(0.03, height);
        glPopMatrix();
    }
    
    // Draw cross on top
    glPushMatrix();
    glTranslatef(0, 0.63, 0);
    drawRectangle(0.018, 0.075);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.645, 0);
    drawRectangle(0.06, 0.018);
    glPopMatrix();
}
