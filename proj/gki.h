#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
using namespace std;

int mis_x;
int mis_y;
extern int visina_prozora;
extern int sirina_prozora;
extern int kliknut;

//proveravamo da li je mis unutar pravougaonika
bool mouse_inside(int x,int y,int sirina,int visina){
return mis_x>=x && mis_x<=x+sirina && mis_y>=y && mis_y<=y+visina;
}

//crtamo tekst karakter po karakter na nekoj poziciji
void crtajText(float x,float y,string txt){
 glColor3f(0,0,0);
 glRasterPos2f(x,y);
 for(auto it=txt.begin();it!=txt.end();it++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
}

//crtamo obojen pravougaonik kao pozadinu
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


//crtaju se "zivoti" u uglu ekrana
void slika(int x,int y,int width,int height,unsigned int im){
glColor3f(1,1,1);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,im);	
glBegin(GL_QUADS);
 glTexCoord2f(0,0);
 glVertex2f(x,y);
 glTexCoord2f(1,0);
 glVertex2f(x+width,y);
 glTexCoord2f(1,1);
 glVertex2f(x+width,y+height);
 glTexCoord2f(0,1);
 glVertex2f(x,y+height);
 glEnd();
glBindTexture(GL_TEXTURE_2D,0);
glDisable(GL_BLEND);
}


//proveravamo gde je mis i da li je kliknut;
//u zavisnosti od toga vracamo true ili false i bojimo drugacije
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
 //stavljamo tekst na sredinu
 float t_x = sirina/2.0-(txt.size()*10/2.0);
 float t_y = visina/2.0-6;
 glRasterPos2f(x+t_x,y+t_y);
 for(auto it=txt.begin();it!=txt.end();it++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
    
 return unutra && kliknut;
}
//postavljamo pozicije misa
void GKpasmouse(int x, int y){
	mis_x=x;
  mis_y=visina_prozora-y;
}
//da li je kliknut mis
//na kraju svakog rendera vracamo na 0
void GKImouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  { 
     kliknut=1;
  }	
}
