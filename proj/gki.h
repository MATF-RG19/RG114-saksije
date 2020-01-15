#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
using namespace std;

int mis_x;
int mis_y;
extern int visina_prozora;
extern int kliknut;

bool mouse_inside(int x,int y,int sirina,int visina){
return mis_x>=x && mis_x<=x+sirina && mis_y>=y && mis_y<=y+visina;
}

void crtajText(float x,float y,string txt){
 glColor3f(0,0,0);
 glRasterPos2f(x,y);
 for(auto it=txt.begin();it!=txt.end();it++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
}

void crtajPanel(float x,float y,float sirina,float visina){
 //pozadina
 glColor3f(0.92f,0.9f,0.01f);
 glBegin(GL_QUADS);
 glVertex2f(x,y);
 glVertex2f(x+sirina,y);
 glVertex2f(x+sirina,y+visina);
 glVertex2f(x,y+visina);
 glEnd();

 //ivice
 glColor3f(0,0,0);
 glBegin(GL_LINE_STRIP);
 glVertex2f(x,y);
 glVertex2f(x+sirina,y);
 glVertex2f(x+sirina,y+visina);
 glVertex2f(x,y+visina);
 glVertex2f(x,y);
 glEnd();
}

bool dugme(float x,float y,float sirina,float visina,string txt){
 //pozadina
 bool unutra=mouse_inside(x,y,sirina,visina);
 if(unutra){
 glColor3ub(135,206,250);
 if(kliknut)
 glColor3f(1,0.2f,0.2f);
 }
 else glColor3f(1,0.68f,0.65f);
 glBegin(GL_QUADS);
 glVertex2f(x,y);
 glVertex2f(x+sirina,y);
 glVertex2f(x+sirina,y+visina);
 glVertex2f(x,y+visina);
 glEnd();

 //ivice
 glColor3f(0,0,0);
 glBegin(GL_LINE_STRIP);
 glVertex2f(x,y);
 glVertex2f(x+sirina,y);
 glVertex2f(x+sirina,y+visina);
 glVertex2f(x,y+visina);
 glVertex2f(x,y);
 glEnd();

 //text

 //boja teksta
 if(unutra){
 	glColor3f(0,0,0);
 if(kliknut)
 	glColor3f(1,0.8f,0.2f);
 	}
 else 
	glColor3f(0,0,0);
 //stavljamo text na sredinu
 float t_x=sirina/2.0-(txt.size()*10/2.0);
 float t_y=visina/2.0-6;
 glRasterPos2f(x+t_x,y+t_y);
 for(auto it=txt.begin();it!=txt.end();it++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
 return unutra && kliknut;
}

void GKpasmouse(int x, int y){
	mis_x=x;
        mis_y=visina_prozora-y;
}

void GKImouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  { 
     kliknut=1;
  }	
}
