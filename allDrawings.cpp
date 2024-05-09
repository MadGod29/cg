#include <iostream>
#include <GL/glut.h>

using namespace std;

void display(int x,int y){
	//glColor3f(0,1,0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void DDALine(int x1,int y1,int x2,int y2){
	float dx,dy,steps,xinc,yinc,x,y;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy)){
		steps=abs(dx);
	}
	else{
		steps=abs(dy);
	}
	xinc=dx/steps;
	yinc=dy/steps;
	x=x1;
	y=y1;
	display(x,y);
	for(int i=0;i<=steps;i++){
		x+=xinc;
		y+=yinc;
		display(x,y);
	}
	glFlush();
}

void DDACircle(int xc, int yc, int r) {
    float x, y;
    float theta;

    for (theta = 0; theta <= 360; theta += 0.1) {
        x = xc + r * cos(theta);
        y = yc + r * sin(theta);
        display(round(x), round(y));
    }
    glFlush();
}

void BresenhamCircle(int xc, int yc, int r){
	int p,x,y;
	p=3-2*r;
	x=0;
	y=r;
	while(x<=y)
	{
		glBegin(GL_POINTS);
		glVertex2i(xc + x , yc + y);
		glVertex2i(xc - x , yc + y);
		glVertex2i(xc + x , yc - y);
		glVertex2i(xc - x , yc - y);
		glVertex2i(xc + y , yc + x);
		glVertex2i(xc - y , yc + x);
		glVertex2i(xc + y , yc - x);
		glVertex2i(xc - y , yc - x);
		glEnd();
		if(p>0)
		{
			p= p+ 4*(x-y) + 10;
			y--;
		}
		else
		{
			p=p+ 4*x +6;
		}
		x++;
	}
}

void BresenhamLine(int x1, int y1, int x2, int y2){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;
    int xinc = (x2 > x1) ? 1 : -1;
    int yinc = (y2 > y1) ? 1 : -1;

    if(dx > dy){
        int p = 2 * dy - dx;
        for(int i = 0; i <= dx; i++){
            display(x, y);
            if(p >= 0){
                y += yinc;
                p -= 2 * dx;
            }
            x += xinc;
            p += 2 * dy;
        }
    }
    else{
        int p = 2 * dx - dy;
        for(int i = 0; i <= dy; i++){
            display(x, y);
            if(p >= 0){
                x += xinc;
                p -= 2 * dy;
            }
            y += yinc;
            p += 2 * dx;
        }
    }
}

void floodFill(int x, int y) {
    float oldColor[3] = {1, 1, 1}; // Color of the background
    float fillColor[3] = {0, 0, 1}; // Color to fill with (blue)
    
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    
    if(color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
        glFlush();
        
        floodFill(x + 1, y);
        floodFill(x - 1, y);
        floodFill(x, y + 1);
        floodFill(x, y - 1);
    }
	glFlush();
}

void boundaryFill(int x, int y) {
    float boundaryColor[3] = {1, 1, 1}; // Color of the boundary
    float fillColor[3] = {0, 0, 1}; // Color to fill with (blue)
    
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    
    if(color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) {
        if(color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]) {
            glColor3fv(fillColor);
            glBegin(GL_POINTS);
                glVertex2i(x, y);
            glEnd();
            glFlush();
            
            boundaryFill(x + 1, y);
            boundaryFill(x - 1, y);
            boundaryFill(x, y + 1);
            boundaryFill(x, y - 1);
        }
    }
	glFlush();
}

void initialize(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Canvas color
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glColor3f(0, 0, 0); // Set drawing color to black

    // Draw something here using OpenGL commands

    glFlush(); // Ensure all OpenGL commands are executed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CG");
    initialize();
    glutDisplayFunc(draw); // Set the display callback function
    glutMainLoop();
    return 0;
}