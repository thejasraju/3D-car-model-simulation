#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

using namespace std;


void printtext(int, int, string );
void loadObj(char *);
void drawCar(void);
void init(void);
void init1(void);
void display(void);
void display1(void);
void display2(void);
void myReshape(int , int);
void mouse(int , int, int , int );
void keys(unsigned char, int , int );
void spec_keys(int,int,int );
void color1(int choice);
void menu2(int choice);
void menu1(int choice);
void carHandler(int choice);



GLuint car;
int home,color=0;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */


int  main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        home=glutCreateWindow("3D CAR MODEL SIMULATION USING OpenGL");
        glutInitWindowSize(1000, 1000);
        init1();
        glutDisplayFunc(display1);
        glutMainLoop();
}



void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window

    int WindowHeight = 1000;
    int WindowWidth = 1000;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}



void loadObj(char *fname)
{
    FILE *fp;
    int read;
    int i=0;
    GLfloat x, y, z;
    char ch;
    car=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }

    glPointSize(20.0);
    glNewList(car, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_LINE_STRIP);

        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }

        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}


void drawCar()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    int a = color%21;
	if(a==0)        glColor3f(.97, .97, .97);	//white
	else if(a==1)	glColor3f(.9, .9, .9);
	else if(a==2) 	glColor3f(.275, .510, .706);	//blue
	else if(a==3)	glColor3f(.824, .412, .118);	//chocolate
	else if(a==4)	glColor3f(.941, .502, .502);	//Coral
	else if(a==5)	glColor3f(.0, .502, .0);	//green
	else if(a==6)	glColor3f(.502, .502, .502);	//grey
	else if(a==7)	glColor3f(.372549, .623529, .623529);	//cadet blue
	else if(a==8)	glColor3f(.6, .196078, .8);	//dark orchid
	else if(a==9)	glColor3f(.858824, .858824, .239216);	//golden yellow
	else if(a==10)	glColor3f(0.502,0, 0.502);	//purple
	else if(a==11)	glColor3f(0.184314,.184314, .309804);	//midnight blue
	else if(a==12)	glColor3f(0.137255,.137255, .556863);	//NavyBlue
	else if(a==13)	glColor3f(0.753 ,.753 , .753);	//Silver
	else if(a==14)	glColor3f(1.00,.078, 0.576);	//Neon pink
	else if(a==15)	glColor3f(1.00,.855, .725);	//Peach
	else if(a==16)	glColor3f(0.55,.09, .09);	//Scarlet
	else if(a==17)	glColor3f(0.13,.37, .31);	//Dusty Green
	else if(a==18)	glColor3f(0.42,.26, .15);	//browny
	else if(a==19)	glColor3f(0.85,.85, .95);	//Quartz
	else if(a==20)	glColor3f(0.85,.85, .10);	//light gold
	else if(a==21)	glColor3f(1.00, 0.00, 1.00);	//Magenta
    glScalef(1,1,1);
    glCallList(car);
    glPopMatrix();
}


void init()
{
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    int nColorMenu;
    int nMainMenu;
    int carMainMenu;
    int nCarMenu;
    nCarMenu = glutCreateMenu(carHandler);
    glutAddMenuEntry("Lamborghini Aventador",1);
    glutAddMenuEntry("Porsche Cayman",2);
    glutAddMenuEntry("Nissan GTR",3);
    glutAddMenuEntry("Ferrari F1 racecar",4);
    glutAddMenuEntry("Ford Mustang Shelby",5);
    glutAddMenuEntry("Audi R8",6);
    carMainMenu = glutCreateMenu(menu1);
    glutAddSubMenu("Select Car",nCarMenu);
    glutAddMenuEntry("Quit",1);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    nColorMenu=glutCreateMenu(color1);
	glutAddMenuEntry("White",1);
	glutAddMenuEntry("Blue",2);
	glutAddMenuEntry("Chocolate",3);
	glutAddMenuEntry("Coral",4);
	glutAddMenuEntry("Green",5);
	glutAddMenuEntry("Grey",6);
	glutAddMenuEntry("Cadet Blue",7);
	glutAddMenuEntry("Dark Orchid",8);
	glutAddMenuEntry("Golden Yellow",9);
	glutAddMenuEntry("Purple",10);
	glutAddMenuEntry("Midnight Blue",11);
	glutAddMenuEntry("Navy Blue",12);
	glutAddMenuEntry("Silver",13);
	glutAddMenuEntry("Neon Pink",14);
	glutAddMenuEntry("Peach",15);
	glutAddMenuEntry("Scarlet",16);
	glutAddMenuEntry("Dusty Green",17);
	glutAddMenuEntry("Brown",18);
	glutAddMenuEntry("Quartz",19);
	glutAddMenuEntry("Light Gold",20);
	nMainMenu = glutCreateMenu(menu2);
	glutAddSubMenu("Change Color", nColorMenu);
   	glutAddMenuEntry("Quit",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutSpecialFunc(spec_keys);
    glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
}

void init1(void)
{
    glutReshapeFunc(myReshape);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);
    glutKeyboardFunc(keys);
    int carMainMenu;
    int nCarMenu;
    nCarMenu = glutCreateMenu(carHandler);
    glutAddMenuEntry("Lamborghini Aventador",1);
    glutAddMenuEntry("Porsche Cayman",2);
    glutAddMenuEntry("Nissan GTR",3);
    glutAddMenuEntry("Ferrari F1 racecar",4);
    glutAddMenuEntry("Ford Mustang Shelby",5);
    glutAddMenuEntry("Audi R8",6);
    carMainMenu = glutCreateMenu(menu1);
    glutAddSubMenu("Select Car",nCarMenu);
    glutAddMenuEntry("Quit",1);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

void display(void)
{
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* Update viewer position in modelview matrix */
            glLoadIdentity();
            glutReshapeFunc(myReshape);
            gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            glRotatef(theta[0], 1.0, 0.0, 0.0);
            glRotatef(theta[1], 0.0, 1.0, 0.0);
            glRotatef(theta[2], 0.0, 0.0, 1.0);
            drawCar();
            glutSwapBuffers();
}


void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

    char string[200];
    sprintf(string, "3-D CAR MODEL SIMULATION USING OPENGL");
    printtext(375,600,string);

    sprintf(string, "A VTU 6th SEMESTER COMPUTER GRAPHICS AND VISUALIZATION PROJECT");
    printtext(285,550,string);

    sprintf(string, "BY:");
    printtext(600,450,string);

    sprintf(string,"NAME-1");
    printtext(600,400,string);

    sprintf(string,"NAME-2");
    printtext(600,350,string);

    sprintf(string,"PRESS SPACE TO CONTINUE");
    printtext(425,200,string);

    glutSwapBuffers();
}

void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

    char string[200];
    sprintf(string, "3-D CAR MODEL SIMULATION USING OPENGL");
    printtext(375,800,string);

    sprintf(string, "INSTRUCTIONS:");
    printtext(275,675,string);

    sprintf(string, "---PERSPECTIVE VIEWING CHANGES:     USE ARROW and x|X y|Y z|Z keys");
    printtext(275,600,string);

    sprintf(string, "---CHANGE CAR MODELS:               USE NUMBER keys 1-6 or LEFT MOUSE BUTTON");
    printtext(275,525,string);

    sprintf(string, "---CHANGE CAR COLOUR:               USE c|C keys or RIGHT MOUSE BUTTON ");
    printtext(275,450,string);

    sprintf(string, "---NAVIGATION TO HOME PAGE:         h|H key");
    printtext(275,375,string);

    sprintf(string, "---NAVIGATION TO INSTRUCTIONS PAGE: i|I key");
    printtext(275,300,string);

    sprintf(string, "---QUIT APPLICATION:                q|Q key or ESC key");
    printtext(275,225,string);

    glutSwapBuffers();
}

void myReshape(int w, int h)
{
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
        glMatrixMode(GL_MODELVIEW);
}


void spec_keys(int key,int x,int y)
{
	if(key == GLUT_KEY_UP)
            axis = 2;
	 if(key == GLUT_KEY_LEFT)
            axis = 0;
	 if(key == GLUT_KEY_RIGHT)
            axis = 1;
    theta[axis] += 10.0;
    if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    display();
}

void keys(unsigned char key, int x, int y)
{
/* Use x, X, y, Y, z, and Z keys to move viewer */
   if(key == 'x')
   {
       viewer[0]-= 1.0;
       display();
   }
   if(key == 'X')
   {
       viewer[0]+= 1.0;
       display();
   }
   if(key == 'y')
   {
       viewer[1]-= 1.0;
       display();
   }
   if(key == 'Y')
   {
       viewer[1]+= 1.0;
       display();
   }
   if(key == 'z')
   {
       viewer[2]-= 1.0;
       display();
   }
   if(key == 'Z')
   {
       viewer[2]+= 1.0;
       display();
   }
   if(key == 'c' | key == 'C')
   {
       color++;
       init();
       display();
   }
   if(key == 'h'| key == 'H')
   {
        glutDestroyWindow(home);
        home=glutCreateWindow("3D CAR MODEL SIMULATION USING OpenGL");
        glutInitWindowSize(1000, 1000);
        glutDisplayFunc(display1);
        init1();

   }
   if(key == 'i'| key == 'I')
   {
        glutCreateSubWindow(home,0,0,500,500);
        glutDisplayFunc(display2);
        glutFullScreen();
        init1();

   }
   if(key == 32)
   {
        glutCreateSubWindow(home,0,0,500,500);
        glutDisplayFunc(display2);
        glutFullScreen();
        init1();
   }
   if(key == 49)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("Avent.obj");
        glutFullScreen();
        init();
   }
    if(key == 50)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("porsche-cayman.obj");
        glutFullScreen();
        init();
   }
   if(key == 51)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("nissan-gt-r-nismo.obj");
        glutFullScreen();
        init();
   }
   if(key == 52)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("ferrari-f1-race-car.obj");
        glutFullScreen();
        init();
   }
     if(key == 53)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("1967-shelby-ford-mustang.obj");
        glutFullScreen();
        init();
   }
     if(key == 54)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("audi-r8-red.obj");
        glutFullScreen();
        init();
   }
   if(key == 'q' | key == 'Q')
   {
        exit(0);
   }
   if(key == 27)
   {
        exit(1);
   }
}

void color1(int choice)
{
    color=choice;
    glutPostRedisplay();
}

void menu2(int choice)
{
    if(choice=1)
    {
        exit(0);
    }
}

void menu1(int choice)
{
    if(choice==1)
    {
        exit(1);
    }
}

void carHandler(int choice)
{
    if(choice == 1)
   {

        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("Avent.obj");
        glutFullScreen();
        init();
   }
    if(choice == 2)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("porsche-cayman.obj");
        glutFullScreen();
        init();
   }
   if(choice == 3)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("nissan-gt-r-nismo.obj");
        glutFullScreen();
        init();
   }
   if(choice == 4)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("ferrari-f1-race-car.obj");
        glutFullScreen();
        init();
   }
     if(choice == 5)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("1967-shelby-ford-mustang.obj");
        glutFullScreen();
        init();
   }
     if(choice == 6)
   {
        glutCreateSubWindow(home,200,300,500,500);
        glutDisplayFunc(display);
        loadObj("audi-r8-red.obj");
        glutFullScreen();
        init();
   }
}










