#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <math.h>
#include "rasad.h"
#include "gki.h"
#define p pair<float,float>
#define TIMER_INTERVAL 20
#define TIMER_ID 1
using namespace std;


//globalne promenljive koje koristimo tokom programa

int high_score=0; 
int trava_id; //za teksturu trave
int zemlja_id; //za teksturu druge trave
int zivot_id; //za teksturu drveta koje sluzi kao pokazatelj za zivot

int zivot;
bool kraj=false; //da li je gotov nivo
int vreme = 0; //vreme koje tece
int poeni=0; 
int kliknut=0; //da li je mis kliknut treba za gki
int meni=1;
int visina_prozora=0;
int sirina_prozora=0;
vector<vector<rasad*>> rasadnik;
pair<int, int> selektovan = make_pair(0,0); //trenutno izabran rasadnik


void selektuj (int i, int j)
{
    if(!kraj){ 
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
}

void dodaj_drvo(int i, int j)
{
    if(!kraj)
    if(!rasadnik[i][j]->ima_drvo){
        rasadnik[i][j]->ima_drvo = true;
        rasadnik[i][j]->rast_drveta = 1;
    }
}

void ukloni_bube(int i, int j){
    if(!kraj)
    if(rasadnik[i][j]->ima_bube)
        rasadnik[i][j]->ima_bube = false;
}
bool pokret=false;
int brojac=0;
//stoperica za postavljanje kamere unapred
void tajmer_kamera(int x){
 if(brojac<=100){
   brojac++; 
    pokret=true;
   glutTimerFunc(TIMER_INTERVAL,tajmer_kamera,3);
 }
 else {brojac=100;
 pokret=false;}
}
//stoperica za vracanje kamere unazad
void tajmer_kamera_nazad(int x){
 if(brojac>0){
   brojac--; 
   pokret=true;
   glutTimerFunc(TIMER_INTERVAL,tajmer_kamera_nazad,3);
 }
 else {brojac=0;
 pokret=false;}
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
    if(key=='e' && pokret==false){
      tajmer_kamera(1);
    }
    if(key=='q' && pokret==false){
	tajmer_kamera_nazad(1);
    }
}


bool trigger = false;
//funkcija koja nasumicno bira polje i postavlja bubice
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

//stoperica za generisanje bubica
void tajmer(int x)
{   if(!kraj){
    srand(time(NULL));
    //svake 3+random[0-5] sekundi stavimo 1 bubu na random mesto
    int sec = rand() % 5 + 3;
    if(meni==0)
    glutTimerFunc(sec*1000, dodaj_bube, 0);
    trigger = true;

    }
}
//funkcija za tok vremena kao stoperica
void tajmer_vreme(int x)
{   if(!kraj){
    vreme++;

    for(int i=0;i<rasadnik.size();i++)
        for(int j=0;j<rasadnik.size();j++)
		if(rasadnik[i][j]->ima_jabuke){
			if(rasadnik[i][j]->sec>=250){
				poeni++;
				rasadnik[i][j]->sec=0;
				} 
			else rasadnik[i][j]->sec++;
		} 
		else rasadnik[i][j]->sec=0;
    if(meni==0)
    glutTimerFunc(TIMER_INTERVAL, tajmer_vreme, TIMER_ID);
    }
}

//generisemo nas rasadnik
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
void meni_display();
//funkcija za izlazak iz igre u meni
void ex_f(int x){
glutDisplayFunc(meni_display);
        pokret=false;
	brojac=0;
    	glutKeyboardFunc(NULL);
	kraj=false;
}
//funkcija za crtanje igre
void on_display() {
    meni=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(135/255.0f,206/255.0f,235/255.0f, 0);
    glutKeyboardFunc(on_keyboard);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2+(3*sin(brojac*(3.14/2.0)/100)), -5+(4*sin(brojac*(3.14/2.0)/100)), 
              0, 0, 0,
              0, 1, 0);
    // ovde ide sve sto ces da crtas
    //crtanje
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
   // GLfloat lpos[] = {0, 4, 0, 1};
   // glEnable(GL_LIGHT0);
   // glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    GLfloat lpos1[] = {0, 1, -1, 0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos1);

    GLfloat lpos[] = {0, 1, -1, 0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, lpos);

    glPushMatrix();
    glTranslatef(0, -2, 3);
    glColor3ub(255,255,255);

    glBindTexture(GL_TEXTURE_2D,trava_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//crtamo okruzenje
    float dx=1000.0/250.0;
    float dz=504.0/250.0;
    for(float i=-500;i<=500;i+=dx)
    for(float j=-500;j<=4;j+=dz){
	    glBegin(GL_QUADS);
	    glNormal3f(0, 1, 0);
	    glTexCoord2f(0,1);
	    glVertex3f(i, 0, j+dz);
	    glTexCoord2f(0,0);
	    glVertex3f(i, 0, j);
	    glTexCoord2f(1,0);
	    glVertex3f(i+dx, 0, j);
	    glTexCoord2f(1,1);
	    glVertex3f(i+dx, 0, j+dz);
	    glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);
	//crtamo travnjak
    glColor3ub(230,255,230);
    glBindTexture(GL_TEXTURE_2D,zemlja_id);
    dx=10.0/5.0;
    dz=10.0/5.0;
    for(float i=-5;i<5;i+=dx)
    for(float j=-6;j<4;j+=dz){
	glBegin(GL_QUADS);
	    glNormal3f(0, 1, 0);
	    glTexCoord2f(0,1);
	    glVertex3f(i, 0.01, j+dz);
	    glTexCoord2f(0,0);
	    glVertex3f(i, 0.01, j);
	    glTexCoord2f(1,0);
	    glVertex3f(i+dx, 0.01, j);
	    glTexCoord2f(1,1);
	    glVertex3f(i+dx, 0.01, j+dz);
	    glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);
    glPopMatrix();
    crtaj_rasadnik();


    //postavljamo parametre za opengl i stavljamo ortografsku projekciju
   	//krecemo da crtamo gki
     glDisable(GL_LIGHTING);
     glDisable(GL_DEPTH_TEST);
     glLoadIdentity();
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0, sirina_prozora, 0, visina_prozora);
     glMatrixMode(GL_MODELVIEW);
     crtajPanel(sirina_prozora-140,visina_prozora-40,200,100);
     crtajText(sirina_prozora-130,visina_prozora-30,"POENI:"+to_string(poeni));
     for(int i=0;i<zivot;i++)
     slika(sirina_prozora-300+i*45,visina_prozora-40,40,40,zivot_id);
	//pri izlasku vracamo sve parametre za igru
     if(dugme(0,visina_prozora-30,100,30,"izadji")){
	if(poeni>high_score){
	high_score=poeni;
	FILE *file=fopen("rezultat.txt","w+");
	fprintf(file,"%d ",high_score);
	fclose(file);
	}
	glutDisplayFunc(meni_display);
        pokret=false;
	brojac=0;
    	glutKeyboardFunc(NULL);
     }
	if(zivot<=0){
	if(poeni>high_score){
	high_score=poeni;
	FILE *file=fopen("rezultat.txt","w+");
	fprintf(file,"%d ",high_score);
	fclose(file);
	}
	kraj=true;
	glutTimerFunc(1500,ex_f,5);
	}
	if(kraj==true){
	crtajPanel(sirina_prozora/2-100,visina_prozora/2-40,210,80);
     crtajText(sirina_prozora/2-95,visina_prozora/2,"gotovo je poeni:"+to_string(poeni));
	}
   //vracamo perspektivnu projekciju
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(90.0f, (sirina_prozora+0.0)/(visina_prozora+0.0), 0.1f, 250.0f);
//reset mis kliknut 
    kliknut=0;
    if(!trigger)
        tajmer(0);
    glutSwapBuffers();
    glutPostRedisplay();
}

void meni_display() {
	//crtamo glavni meni
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f,0.8f,0.48f,1);
	kraj=false;
    glDisable(GL_LIGHTING);
     glDisable(GL_DEPTH_TEST);
     glLoadIdentity();
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0, sirina_prozora, 0, visina_prozora);
     glMatrixMode(GL_MODELVIEW);
     crtajPanel(sirina_prozora/2-100,visina_prozora-550,200,500);

     //pokrecemo nivo i pokrecemo vreme za tajmer i generisemo teren
     if(dugme(sirina_prozora/2-75,visina_prozora-115,150,45,"igraj")){
	generisi_rasadnik(4, make_pair(-4, 4), make_pair(-2, 6));
	meni=0;
	poeni=0;
	zivot=3;
	kraj=false;
	brojac=0;
	pokret=false;
	tajmer_vreme(0);
	glutDisplayFunc(on_display);
        glutKeyboardFunc(on_keyboard);
     }
     crtajText(sirina_prozora/2-70,visina_prozora-140,"High score:"+to_string(high_score));
     if(dugme(sirina_prozora/2-75,visina_prozora-530,150,45,"izadji")){
	exit(EXIT_FAILURE);
     }

    meni=1;
    kliknut=0;
    glutSwapBuffers();
    glutPostRedisplay();
}
void resize(int x,int y){
 //menjamo promenljive pri promeni dimenzije prozora
 sirina_prozora=x;
 visina_prozora=y;
 glViewport(0,0,x,y);
}
int main(int argc, char** argv) {
     /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    /* Registruju se callback funkcije. */
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(meni_display);
    glutKeyboardFunc(NULL);
    glMatrixMode(GL_PROJECTION);
    //postavljamo inicijalne dimenzije prozora i projekciju
    visina_prozora=600;
    sirina_prozora=800;
    gluPerspective(90.0f, (sirina_prozora+0.0)/(visina_prozora+0.0), 0.1f, 250.0f);
    glEnable(GL_TEXTURE_2D);
    //gluOrtho2D(0, 800, 0, 600);
    glutReshapeFunc(resize);
    glutMouseFunc(GKImouse);
    glutPassiveMotionFunc(GKpasmouse);
	//ucitavamo resorse 
    trava_id=image("./trava.bmp");
    zemlja_id=image("./z.bmp");
    zivot_id=image("./drvo.bmp");
	//ucitavamo high score
	FILE *file=fopen("rezultat.txt","r");
	if(file!=NULL)
	fscanf(file,"%d",&high_score);
	else file=fopen("rezultat.txt","w");
	fclose(file);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();


    return 0;
}
