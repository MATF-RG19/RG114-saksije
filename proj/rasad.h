#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
using namespace std;
class rasad
{
private:
    
public:
    rasad(float x, float z);
    ~rasad();
    pair<float, float> pozicija;
    bool selected = false;
    bool ima_drvo = false;
    bool ima_bube = false;
    float rast_drveta = 0.0;
    void crtaj()
    {
        glColor3ub(139,69,19);
        if(selected)
            glColor3ub(200,0,0);
        glPushMatrix();
        GLdouble a[] = {0, 1, 0, 2.5};
        glClipPlane(GL_CLIP_PLANE0, a);
        glEnable(GL_CLIP_PLANE0);
        glTranslatef(pozicija.first, -2.3, pozicija.second);
        glScalef(1.3f, 0.7f, 0.7f);
        glutSolidSphere(0.7, 20, 20);
        glDisable(GL_CLIP_PLANE0);
        glPopMatrix();

    if(ima_drvo) {
        glPushMatrix();
        glColor3ub(160,82,45);       
        glTranslatef(pozicija.first, -2.3, pozicija.second);
        glRotatef(-90, 1, 0, 0);
        glScalef(1, 1, rast_drveta); 
        glutSolidCylinder(0.3, 1, 15, 15);
        rast_drveta+=0.001;
        
        rast_drveta = min(rast_drveta, 1.65f);
        glPopMatrix();

        glPushMatrix();
        glColor3ub(34,139,34);
        if(ima_bube)
            glColor3ub(255, 255, 0);
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
        glutSolidSphere(0.6, 15, 15);
        glTranslatef(-0.4, 0, 0);
        glutSolidSphere(0.4, 15, 15);
        glTranslatef(0.8, -0.1, 0);
        glutSolidSphere(0.4, 15, 15);
        glPopMatrix();        
        } 
    }
};

rasad::rasad(float x, float z)
{
    pozicija.first = x;
    pozicija.second = z;
}

rasad::~rasad()
{
}
