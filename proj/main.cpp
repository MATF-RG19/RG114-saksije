#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <math.h>
#include "rasad.h"
#define p pair<float,float>
using namespace std;

vector<vector<rasad*>> rasadnik;
pair<int, int> selektovan = make_pair(0,0);
void selektuj (int i, int j)
{
    if(i>=0 && i < rasadnik.size())
    {
        if(j>=0 && j<rasadnik.size())
        {
            rasadnik[selektovan.first][selektovan.second]->selected = false;
            rasadnik[i][j]->selected = true;
            selektovan.first = i;
            selektovan.second = j;
        }
    }
}

void dodaj_drvo(int i, int j)
{
    if(!rasadnik[i][j]->ima_drvo){
        rasadnik[i][j]->ima_drvo = true;
        rasadnik[i][j]->rast_drveta = 1;
    }
}

void ukloni_bube(int i, int j){
    if(rasadnik[i][j]->ima_bube)
        rasadnik[i][j]->ima_bube = false;
}

static void on_keyboard(unsigned char key, int x, int y) {
    if(key == 'w' || key == 'W'){
        
        selektuj(selektovan.first + 1, selektovan.second);}
    if(key == 's' || key == 'S')
        selektuj(selektovan.first - 1, selektovan.second);
    if(key == 'a' || key == 'A')
        selektuj(selektovan.first, selektovan.second + 1);
    if(key == 'd' || key == 'D')
        selektuj(selektovan.first, selektovan.second - 1);
    if(key == 13)
    {
        dodaj_drvo(selektovan.first, selektovan.second);
    }
    if(key == ' ')
    {
        ukloni_bube(selektovan.first, selektovan.second);
    }

}


bool trigger = false;

void dodaj_bube(int x)
{
    srand(time(NULL));
    int rand_i = rand() % 4;
    int rand_j = rand() % 4;
    
    if(rasadnik[rand_i][rand_j]->ima_drvo && !rasadnik[rand_i][rand_j]->ima_bube)
    {
        rasadnik[rand_i][rand_j]->ima_bube = true;
    }
    trigger = false;
}


void tajmer(int x)
{
    srand(time(NULL));
    int sec = rand() % 5 + 3;
    glutTimerFunc(sec*1000, dodaj_bube, 0);
    trigger = true;

    printf("%d\n", sec);
}


void generisi_rasadnik(int k, p x, p z){
    rasadnik.resize(k);
    float sirina = abs(x.first - x.second);
    float visina = abs(z.first - z.second);
    float pz = z.first;
    for(int i = 0; i<k; i++)
    {
        float px = x.first;
        rasadnik[i].resize(k);
        for(int j = 0; j<k; j++)
        {
            rasadnik[i][j] = new rasad(px, pz);
            px+=sirina/(float(k-1));
        }
        pz+=visina/(float(k-1));
    }
    selektuj(0, 0);
}

void crtaj_rasadnik()
{
    for(int i = 0; i<rasadnik.size(); i++) {
        for(int j = 0; j<rasadnik[i].size(); j++)
        {
            rasadnik[i][j]->crtaj();
        } 
    }
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutKeyboardFunc(on_keyboard);
    glLoadIdentity();
    gluLookAt(0, 2, -5, 
              0, 0, 0,
              0, 1, 0);
    // ovde ide sve sto ces da crtas
    //crtanje
    glPushMatrix();
    glTranslatef(0, -2, 3);
    glColor3ub(124,252,0);
    glBegin(GL_QUADS);
    glVertex3f(-500, 0, 4);
    glVertex3f(-500, 0, -500);
    glVertex3f(500, 0, -500);
    glVertex3f(500, 0, 4);
    glEnd();
    
    glColor3ub(34,139,34);
    glBegin(GL_QUADS);
    glVertex3f(4.5, 0, 3);
    glVertex3f(4.5, 0, -6);
    glVertex3f(-4.5, 0, -6);
    glVertex3f(-4.5, 0, 3);
    glEnd();
    glPopMatrix();
    crtaj_rasadnik();

    if(!trigger)
        tajmer(0);

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
     /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    generisi_rasadnik(4, make_pair(-4, 4), make_pair(-2, 6));
    /* Registruju se callback funkcije. */
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0f, 800.0f/600.0f, 0.1f, 250.0f);
    //gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(135/255.0f,206/255.0f,235/255.0f, 0);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();


    return 0;
}