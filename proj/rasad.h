#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
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
