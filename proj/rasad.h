#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include<vector>
using namespace std;
extern int vreme;
extern int poeni;
extern int zivot;
extern bool kraj;
extern int high_score;

#define JABUKE_VELIKA_KROSNJA 15
#define JABUKE_MALA_KROSNJA 9
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
    bool ima_jabuke=false;
    float rast_drveta = 0.0;
    int sec=0;
    vector<vector<float>> jabuke; 

    void crtaj()
    {
        glColor3ub(139,69,19);
        if(selected)
            glColor3ub(200,0,0);
        glPushMatrix();
        GLdouble a[] = {0, 1, 0, 2.5};
	//crtamo rasad kao sferu koju odsecamo klip ravni
        glClipPlane(GL_CLIP_PLANE0, a);
        glEnable(GL_CLIP_PLANE0);
        glTranslatef(pozicija.first, -2.3, pozicija.second);
        glScalef(1.3f, 0.7f, 0.7f);
        glutSolidSphere(0.7, 20, 20);
        glDisable(GL_CLIP_PLANE0);
        glPopMatrix();

    //ako ima drvo na rasadniku crtamo krosnje i stablo
    if(ima_drvo) {
	
        glPushMatrix();
        glColor3ub(160,82,45);       
        glTranslatef(pozicija.first, -2.3, pozicija.second);
        glRotatef(-90, 1, 0, 0);
        glScalef(1, 1, rast_drveta); 
        glutSolidCylinder(0.3, 1, 15, 15);
	if(!kraj)
        rast_drveta+=0.001;
        
        rast_drveta = min(rast_drveta, 1.65f);

	//ako je stiglo do konacne faze crtamo i jabuke na drvetu
	if(rast_drveta==1.65f)
	ima_jabuke=true;
	else
	ima_jabuke=false;
        glPopMatrix();

        glPushMatrix();
        glColor3ub(34,139,34);
        if(ima_bube) {
            crtaj_bubu();
            glColor3ub(255, 255, 0);
		if(!kraj)
            rast_drveta -= 0.005;
            if(rast_drveta <= 0){
                ima_drvo = false;
                ima_bube = false;
		poeni--;
		zivot--;
            }
        }
        glTranslatef(pozicija.first, -2 + rast_drveta, pozicija.second);
	if(ima_jabuke){
	//za svaku krosnju crtamo jabuke na ivicama sfere
	glColor3ub(190,45,34);


	for(int i=0;i<JABUKE_VELIKA_KROSNJA;i++){
	  glPushMatrix();

	//prvih 150 milisekundi jabuke rastu ide od 0 do 0.07
	//posto sinus sec*(PI/2)/150
	//je 0 kad je sec 0 , a 1 kad je sec 150
	if(sec<150){
	  glTranslatef(0.55*jabuke[i][0],0.55*jabuke[i][1],0.55*jabuke[i][2]);
	  glutSolidSphere(0+0.07*sin(sec*(3.14/2.0)/150.0), 15, 15);
	  glPopMatrix();
	}
	//drugih 50 sekundi ostaju gde jesu
	else if(sec<200){
	  glTranslatef(0.55*jabuke[i][0],
	 0.55*jabuke[i][1],0.55*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();	
	}
	//nakon 200 sekundi padaju ispod y=0
	//jabuke se nalaze negde izmedju 1 i 2
	else {
	glTranslatef(0.55*jabuke[i][0],
	 0.55*jabuke[i][1]-2*sin((sec-200)*(3.14/2.0)/50.0),0.55*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();
	}
	 }
	}


	glColor3ub(34,139,34);
        glutSolidSphere(0.6, 15, 15);
	
        glTranslatef(-0.4, 0, 0);

	if(ima_jabuke){
	glColor3ub(190,45,34);
	for(int i=JABUKE_VELIKA_KROSNJA;i<JABUKE_VELIKA_KROSNJA+
	JABUKE_MALA_KROSNJA;i++){
	  glPushMatrix();
	  
	if(sec<150){
	  glTranslatef(0.4*jabuke[i][0],0.4*jabuke[i][1],0.4*jabuke[i][2]);
	  glutSolidSphere(0+0.07*sin(sec*(3.14/2.0)/150.0), 15, 15);
	  glPopMatrix();
	}
	//drugih 50 sekundi ostaju gde jesu
	else if(sec<200){
	  glTranslatef(0.4*jabuke[i][0],
	 0.4*jabuke[i][1],0.4*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();	
	}
	//nakon 200 sekundi padaju ispod y=0
	//jabuke se nalaze negde izmedju 1 i 2
	else {
	glTranslatef(0.4*jabuke[i][0],
	 0.4*jabuke[i][1]-2*sin((sec-200)*(3.14/2.0)/50.0),0.4*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();
	}		
		
	 }
	}
	glColor3ub(34,139,34);
        glutSolidSphere(0.4, 15, 15);
        glTranslatef(0.8, -0.1, 0);
        glutSolidSphere(0.4, 15, 15);

	if(ima_jabuke){
	glColor3ub(190,45,34);
	for(int i=JABUKE_VELIKA_KROSNJA+
	JABUKE_MALA_KROSNJA;i<JABUKE_VELIKA_KROSNJA+
	2*JABUKE_MALA_KROSNJA;i++){

	  glPushMatrix();

	if(sec<150){
	  glTranslatef(0.4*jabuke[i][0],0.4*jabuke[i][1],0.4*jabuke[i][2]);
	  glutSolidSphere(0+0.07*sin(sec*(3.14/2.0)/150.0), 15, 15);
	  glPopMatrix();
	}
	//drugih 50 sekundi ostaju gde jesu
	else if(sec<200){
	  glTranslatef(0.4*jabuke[i][0],
	 0.4*jabuke[i][1],0.4*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();	
	}
	//nakon 200 sekundi padaju ispod y=0
	//jabuke se nalaze negde izmedju 1 i 2
	else {
	glTranslatef(0.4*jabuke[i][0],
	 0.4*jabuke[i][1]-2*sin((sec-200)*(3.14/2.0)/50.0),0.4*jabuke[i][2]);
	  glutSolidSphere(0.07, 15, 15);
	  glPopMatrix();
	}

	 }
	}
        glPopMatrix();        
        } 
    }

    void buba()
    {
	//crtamo bubu kao vise sferica
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
    jabuke.resize(JABUKE_VELIKA_KROSNJA+2*JABUKE_MALA_KROSNJA);
    
    //ako treba nasumicnost
    //srand(rand()%1000); 
    //Generisu se jabuke na sferi duzine poluprecnika 1
    for(int i=0;i<JABUKE_VELIKA_KROSNJA+2*JABUKE_MALA_KROSNJA;i++){
	int x=rand()%200-100;
	int y=rand()%200-100;
	int z=rand()%200-100;
	float norm=sqrtf(x*x+y*y+z*z);
	//uzima se normiran vektor da bi bila duzina 1
	float tx=(float)x/norm;
	float ty=(float)y/norm;
	float tz=(float)z/norm;
	jabuke[i].push_back(tx);
	jabuke[i].push_back(ty);
	jabuke[i].push_back(tz);
    }
	ima_jabuke=false;
}

unsigned int image(string filename){
  FILE *file;
	//funkcija za ucitavanje teksture iz bmp fajla
	//uzeto sa casa 
	//citamo prvi deo fajla koji je obavezan
	//sadrzi informacije o slici
  unsigned short type;
  unsigned int size1;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;

  unsigned int size;
  //sirina slike odnosno dimenzije matrice piksela
  unsigned int width;
  //visina slike odnosno dimenzije matrice 
  unsigned int height;
  unsigned short planes;
  //koliko bitova ima da li je rgb ili rgba
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;

  unsigned int i;
  unsigned char r, g, b, a;

  file = fopen(filename.c_str(), "rb");
  if(file==NULL)
   cout<<"ne postoji fajl"<<endl;
  fread(&type, 2, 1, file);
  fread(&size1, 4, 1, file);
  fread(&reserved1, 2, 1, file);
  fread(&reserved2, 2, 1, file);
  fread(&offsetbits, 4, 1, file);

  fread(&size, 4, 1, file);
  fread(&width, 4, 1, file);
  fread(&height, 4, 1, file);
  fread(&planes, 2, 1, file);
  fread(&bitcount, 2, 1, file);
  fread(&compression, 4, 1, file);
  fread(&sizeimage, 4, 1, file);
  fread(&xpelspermeter, 4, 1, file);
  fread(&ypelspermeter, 4, 1, file);
  fread(&colorsused, 4, 1, file);
  fread(&colorsimportant, 4, 1, file);

  char *pixels;
  //u zavisnosti od toga da li je rgb ili rgba alociramo memoriju
  if (bitcount == 24)
    pixels = (char *)malloc(3 * width * height * sizeof(char));
  else if (bitcount == 32)
    pixels = (char *)malloc(4 * width * height * sizeof(char));
  else {
    exit(1);
  }
  unsigned int image_id;
  bool alfa=false;
  //citamo boje u matricu
  if (bitcount == 24)
    for (i = 0; i < width * height; i++) {
	alfa=false;
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      pixels[3 * i] = r;
      pixels[3 * i + 1] = g;
      pixels[3 * i + 2] = b;

    }
  else if (bitcount == 32)
    for (i = 0; i < width * height; i++) {
	alfa=true;
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      pixels[4 * i] = r;
      pixels[4 * i + 1] = g;
      pixels[4 * i + 2] = b;
      pixels[4 * i + 3] = a;
    }

    //generisemo teksturu koristeci matricu napravljenu malopre
    glGenTextures(1,&image_id);
    glBindTexture(GL_TEXTURE_2D,image_id);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//ako ima alfu to koristimo za providljivost
    if(!alfa)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, pixels);
    else 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    free(pixels);
    fclose(file);
    glBindTexture(GL_TEXTURE_2D,0);
   return image_id;
}

rasad::~rasad()
{
}
