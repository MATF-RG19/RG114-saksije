#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
using namespace std;
extern int vreme;
extern int poeni;
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
        if(ima_bube) {
            crtaj_bubu();
            glColor3ub(255, 255, 0);
            rast_drveta -= 0.005;
            if(rast_drveta <= 0){
                ima_drvo = false;
                ima_bube = false;
            }
        }
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
        glutSolidSphere(0.6, 15, 15);
        glTranslatef(-0.4, 0, 0);
        glutSolidSphere(0.4, 15, 15);
        glTranslatef(0.8, -0.1, 0);
        glutSolidSphere(0.4, 15, 15);
        glPopMatrix();        
        } 
    }

    void buba()
    {
        glPushMatrix();
        //buba
        glutSolidSphere(0.1, 20, 20);
        glTranslatef(0, 0, -0.075);
        

        glPushMatrix();
        //levo oko
        glColor3f(1, 1, 1);
        glTranslatef(-0.03,0,0);
        glutSolidSphere(0.05, 10, 10);

        glPushMatrix();
        //levo zenica
        glColor3f(0, 0, 0);
        glTranslatef(0,0,-0.03);
        glutSolidSphere(0.025, 10, 10);
        glPopMatrix();

        glPopMatrix();

        glPushMatrix();
        //desno oko
        glColor3f(1, 1, 1);
        glTranslatef(0.03,0,0);
        glutSolidSphere(0.05, 10, 10);

        glPushMatrix();
        //desno zenica
        glColor3f(0, 0, 0);
        glTranslatef(0,0,-0.03);
        glutSolidSphere(0.025, 10, 10);
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();
    }

    void crtaj_bubu()
    {
        glPushMatrix();
        //glColor3f(0, 0, 0);
        glColor3f(rand()%10/10.0, rand()%10/10.0, rand()%10/10.0);
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
        glRotatef(-vreme*10, 0, 1, 0);
        glTranslatef(-0.85, 0.0, 0.0);
        buba();
        glPopMatrix();

        glPushMatrix();
        glColor3f(rand()%10/10.0, rand()%10/10.0, rand()%10/10.0);
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
        glRotatef(-vreme*10.0, 1, 1, 0);
        glTranslatef(-0.85, 0.0, 0.0);
        buba();
        glPopMatrix();

        glPushMatrix();
        glColor3f(rand()%10/10.0, rand()%10/10.0, rand()%10/10.0);
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
        glRotatef(-vreme*10.0, 0, 1, 1);
        glTranslatef(-0.85, 0.0, 0.0);
        buba();
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
