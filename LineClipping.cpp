#include<stdlib.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>


int xl=50,xh=200,yl=50,yh=200;
float u1,v1,u2,v2;
int flag=0;

void init ()
{
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
}
	
void dda(float x1,float y1,float x2,float y2)
{
	float dx,dy,x=x1,y=y1,xi,yi;
	dx=x2-x1;
	dy=y2-y1;
	int steps;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	xi=dx/(float)steps;
	yi=dy/(float)steps;
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	for(int i=0;i<steps;i++)
	{
		x+=xi;
		y+=yi;
		
		glVertex2f(x,y);
	}
	glEnd();
	glFlush();
}

void drawWindow(){
	dda(50,50,200,50);
	dda(50,50,50,200);
	dda(50,200,200,200);
	dda(200,50,200,200);
}

void mymouse(int button,int state,int x,int y){
	glColor3f(0,0,0);
	if(state==GLUT_DOWN && flag==0 ){
		u1=x;
		v1=480-y;
		flag=1;
	}
	else if(state==GLUT_DOWN && flag==1){
		u2=x;
		v2=480-y;
		flag=2;
		dda(u1,v1,u2,v2);
	}
}

struct code{
	int l,r,t,b;
};

code getcode(int x,int y){
	code c={0,0,0,0};
	if(x<xl){
		c.l=1;
	}
	if(y<yl){
		c.b=1;
	}
	if(x>xh){
		c.r=1;
	}
	if(y>yh){
		c.t=1;
	}
	return c;
}

void cohen(){
	int xi,yi;
	code c1,c,c2;
	int flag;
	float m=(v2-v1)/(u2-u1);
	c1=getcode(u1,v1);
	c2=getcode(u2,v2);
	
	while(1){
		if( c1.t==0 && c2.t==0 && c1.b==0 && c2.b==0 && c1.r==0 && c2.r==0 && c1.l==0 && c2.l==0 ){
			break;
		}
		else if( ( (c1.t  && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l) ) !=0)
		{
			u1=v1=u2=v2=0;
			break;
		}
		else{
			if(c1.l==1 || c2.l==1){
				xi=xl;
				yi=v1+(m*(xl-u1));
				
				if(c1.l==1){
					flag=0;
				}
				else{
					flag=1;
				}
			}
			else if(c1.r==1 || c2.r==1){
				xi=xh;
				yi=v1+(m*(xh-u1));
				
				if(c1.r==1){
					flag=0;
				}
				else{
					flag=1;
				}
			}
			else if(c1.t==1 || c2.t==1){
				yi=yh;
				xi=u1+((1/m)*(yh-v1));
				
				if(c1.t==1){
					flag=0;
				}
				else{
					flag=1;
				}
			}
			else if(c1.b==1 || c2.b==1){
				yi=yl;
				xi=u1+((1/m)*(yl-v1));
				
				if(c1.b==1){
					flag=0;
				}
				else{
					flag=1;
				}
			}
			
			c=getcode(xi,yi);
			if(flag==0)
			{
				u1=xi;
				v1=yi;
				c1=c;
			}
			if(flag==1)
			{
				u2=xi;
				v2=yi;
				c2=c;
			}
		}
	}
	drawWindow();
	dda(u1,v1,u2,v2);
}


void mykeyb(char unsigned  key,int x,int y){
	
	if(key=='c'){
		init();
		cohen();
	}
	if(key=='r'){
		init();
		drawWindow();
		flag=0;
	}
	
}

int main(int argc,char ** argv){
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Line clipping");
	gluOrtho2D(0,640,0,480);
	init();
	glFlush();
	drawWindow();
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykeyb);
	glutMainLoop();
	return 0;
}
