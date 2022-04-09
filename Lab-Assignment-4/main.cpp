// Assignment 4
// Computer Graphics Lab 
// Shamim Bin Zahid 
// Roll 43

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#define PI 3.14159265
static int W=700;
static int H=700;

using namespace std;

static void idle(void);
void calcV();

typedef struct{
    int x;
    int y;
} Point;

double P3D[8][3];
int face[6][4] = {
    {0,1,2,3},
    {4,0,3,7},
    {5,4,7,6},
    {0,4,5,1},
    {1,5,6,2},
    {7,3,2,6}
}; 

// hardcoded for now
double qdx = 0;
double qdy = 0;
double qdz = 300;
double zp = -300;
double s = 400;

double angle_x_left = 0, angle_y_down = 0;
double angle_x_right = 0, angle_y_up = 0;
int initialScreen = 1;
double q[3] = {qdx, qdy, qdz};

double cop[3] = {qdx,qdy,qdz +- zp};
double copoly[3] = {0,0,0};
double v[3];
double N[3];
vector<Point> P2D;

/* GLUT callback Handlers */

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
///
static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W/2, W/2, -H/2, H/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void drawLine_0(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delE=2*dy, delNE=2*(dy-dx), d=2*dy-dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(x<x1){
        if(d<0){
            d+=delE;
            x++;
        }
        else{
            d+=delNE;
            x++;
            y++;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_1(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delN=-2*dx, delNE=2*(dy-dx), d=dy-2*dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(y<y1){
        if(d<0){
            d+=delNE;
            x++;
            y++;
        }
        else{
            d+=delN;
            y++;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_2(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delN=-2*dx, delNW=-2*dy-2*dx, d=-2*dx-dy;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(y<y1){
        if(d>=0){
            d+=delNW;
            x--;
            y++;
        }
        else{
            d+=delN;
            y++;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_3(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delW=-2*dy, delNW=-2*dx-2*dy, d=-dx-2*dy;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(x>x1){
        if(d<0){
            d+=delNW;
            x--;
            y++;
        }
        else{
            d+=delW;
            x--;
        }
        glVertex2i(x,y);
    }
    glEnd();
}
static void drawLine_4(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delW=-2*dy, delSW=2*(-dy+dx), d=-2*dy+dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(x>x1)
    {
        if(d<0)
        {
            d+=delW;
            x--;
        }
        else
        {
            d+=delSW;
            x--;
            y--;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_5(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delS=2*dx, delSW=2*(-dy+dx), d=-dy+2*dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(y>y1){
        if(d<0){
            d+=delSW;
            x--;
            y--;
        }
        else{
            d+=delS;
            y--;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_6(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delS=2*dx, delSE=2*(dy+dx), d=dy+2*dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(y>y1){
        if(d<0){
            d+=delS;
            y--;
        }
        else{
            d+=delSE;
            x++;
            y--;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static void drawLine_7(int x0, int y0, int x1, int y1){
    int dx=x1-x0, dy=y1-y0,x=x0,y=y0;
    int delE=2*dy, delSE=2*(dy+dx), d=2*dy+dx;
    glBegin(GL_POINTS);
    glVertex2i(x0,y0);
    while(x1>x){
        if(d<0){
            d+=delSE;
            x++;
            y--;
        }
        else{
            d+=delE;
            x++;
        }
        glVertex2i(x,y);
    }
    glEnd();
}

static int zone(int dx, int dy){
    if(dx >= 0 && dy >= 0){
        if(dx>=dy)
            return 0;
        else
            return 1;
    }
    else if(dx < 0 && dy >=0){
        if(abs(dx)<=dy)
            return 2;
        else
            return 3;
    }
    else if(dx < 0 && dy < 0){
        if(abs(dx)>=abs(dy))
            return 4;
        else
            return 5;
    }
    else if(dx >= 0 && dy < 0){
        if(dx<=abs(dy))
            return 6;
        else
            return 7;
    }
    return 0;
}

static void genP3D(double s){
    double temp[8][3] =  {
        {s, -s, s},
        {s, -s, -s},
        {s, s, -s},
        {s, s, s},
        {-s, -s, s},
        {-s, -s, -s},
        {-s, s, -s},
        {-s, s, s}
    };
    for(int i=0; i< 8; i++){
        for(int j=0; j<3; j++){
            P3D[i][j] = temp[i][j]/2;
        }
    }
}


Point cal2DFrom3D(double p[3], double q[3], double zp){
    Point newP;
    double w;
    double temp;
    w = - p[2] * 1/q[2] + 1 + zp / q[2];
    temp = p[0] - p[2] * q[0]/q[2] + zp * q[0]/q[2];
    temp = temp / w;
    newP.x = (int)round(temp);
    temp = p[1] - p[2] * q[1]/q[2] + zp * q[1]/q[2];
    temp = temp / w;
    newP.y = (int)round(temp);
    return newP;
}

void findanddrawline(double x0, double y0, double x1, double y1){
    int dx=x1-x0, dy=y1-y0;
    int zoneNo = zone(dx,dy);
    if(zoneNo==0){
        glColor3d(1,1,1);
        drawLine_0(x0, y0,x1, y1);
    }
    else if(zoneNo==1){
        glColor3d(1,1,1);
        drawLine_1(x0, y0, x1, y1);
    }
    else if(zoneNo==2){
        glColor3d(1,1,1);
        drawLine_2(x0, y0, x1, y1);
    }
    else if(zoneNo==3){
        glColor3d(1,1,1);
        drawLine_3(x0, y0, x1, y1);
    }
    else if(zoneNo==4){
        glColor3d(1,1,1);
        drawLine_4(x0, y0, x1, y1);
    }
    else if(zoneNo==5){
        glColor3d(1,1,1);
        drawLine_5(x0, y0, x1, y1);
    }
    else if(zoneNo==6){
        glColor3d(1,1,1);
        drawLine_6(x0, y0, x1, y1);
    }
    else if(zoneNo==7){
        glColor3d(1,1,1);
        drawLine_7(x0, y0, x1, y1);
    }
}

void drawCube(){
    for(int k =0;k<6;k++){
        double vect_A[3];
        double vect_B[3];
        vect_A[0] = P3D[face[k][1]][0] - P3D[face[k][0]][0];
        vect_A[1] = P3D[face[k][1]][1] - P3D[face[k][0]][1];
        vect_A[2] = P3D[face[k][1]][2] - P3D[face[k][0]][2];
        vect_B[0] = P3D[face[k][3]][0] - P3D[face[k][0]][0];
        vect_B[1] = P3D[face[k][3]][1] - P3D[face[k][0]][1];
        vect_B[2] = P3D[face[k][3]][2] - P3D[face[k][0]][2];
        N[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
        N[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
        N[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];

        double dot_prod = 0;
        dot_prod = v[0]*N[0] + v[1]*N[1] + v[2]*N[2];

        if(dot_prod>=s*130){ // only god knows why this condition works
            findanddrawline(P2D[face[k][0]].x, P2D[face[k][0]].y, P2D[face[k][1]].x, P2D[face[k][1]].y);
            findanddrawline(P2D[face[k][1]].x, P2D[face[k][1]].y, P2D[face[k][2]].x, P2D[face[k][2]].y);
            findanddrawline(P2D[face[k][2]].x, P2D[face[k][2]].y, P2D[face[k][3]].x, P2D[face[k][3]].y);
            findanddrawline(P2D[face[k][3]].x, P2D[face[k][3]].y, P2D[face[k][0]].x, P2D[face[k][0]].y);
        }
    }
}

static void display(void){
    if(initialScreen){
        genP3D(s);
        initialScreen = 0;
        calcV();
    }
    for (int i = 0; i<8; i++){
        P2D.push_back(cal2DFrom3D(P3D[i], q, -zp));
    }
    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    // defining the light properties
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // defining the material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCube();
    
    glPopMatrix();
    glutSwapBuffers();
}
static void SpecialKey(int key, int x, int y){
    switch(key){
        static int tempX,tempY,tempZ;
    case GLUT_KEY_UP :
        if(angle_x_left == 0)
            angle_x_left = 360;
        else
            angle_x_left = angle_x_left - 0.01;
        for(int i=0; i<8; i++){
            P3D[i][0] = P3D[i][0];
            tempY = round(cos(angle_x_left * PI / 180.0 )*P3D[i][1] - sin ( angle_x_left * PI / 180.0 )*P3D[i][2]);
            tempZ = round(sin(angle_x_left * PI / 180.0 )*P3D[i][1] + cos ( angle_x_left * PI / 180.0 )*P3D[i][2]);
            P3D[i][1] = tempY;
            P3D[i][2] = tempZ;
        }
        P2D.clear();
        break;

    case GLUT_KEY_DOWN :
        if(angle_x_right<360)
            angle_x_right = angle_x_right + 0.01;
        else
            angle_x_right = 0;
        for(int i=0; i<8; i++){
            P3D[i][0] = P3D[i][0];
            tempY = round(cos ( angle_x_right * PI / 180.0 )*P3D[i][1] - sin ( angle_x_right * PI / 180.0 )*P3D[i][2]);
            tempZ = round(sin ( angle_x_right * PI / 180.0 )*P3D[i][1] + cos ( angle_x_right * PI / 180.0 )*P3D[i][2]);
            P3D[i][1] = tempY;
            P3D[i][2] = tempZ;
        }
        P2D.clear();
        break;

    case GLUT_KEY_LEFT:
        if(angle_y_down == 0)
            angle_y_down = 360;
        else
            angle_y_down = angle_y_down - 0.01;
        for(int i=0; i<8; i++){
            tempX = round(cos ( angle_y_down * PI / 180.0 )*P3D[i][0] + sin ( angle_y_down * PI / 180.0 )*P3D[i][2]);
            P3D[i][1] = P3D[i][1];
            tempZ = round( -sin ( angle_y_down * PI / 180.0 )*P3D[i][0] + cos ( angle_y_down * PI / 180.0 )*P3D[i][2]);
            P3D[i][0] = tempX;
            P3D[i][2] = tempZ;
        }
        P2D.clear();
        break;

    case GLUT_KEY_RIGHT :
        if(angle_y_up < 360)
            angle_y_up = angle_y_up + 0.01;
        else
            angle_y_up = 0;
        for(int i=0; i<8; i++){
            tempX = round(cos ( angle_y_up * PI / 180.0 )*P3D[i][0] + sin (angle_y_up * PI / 180.0 )*P3D[i][2]);
            P3D[i][1] = P3D[i][1];
            tempZ = round( -sin ( angle_y_up * PI / 180.0 )*P3D[i][0] + cos ( angle_y_up * PI / 180.0 )*P3D[i][2]);
            P3D[i][0] = tempX;
            P3D[i][2] = tempZ;
        }
        P2D.clear();
        break;
    }
}

#if 0
static void key(unsigned char key, int x, int y){
    switch (key){
        case 27 :
        case 'q':
            exit(0);
            break;
        case '+':
            slices++;
            stacks++;
            break;
        case '-':
            if (slices>3 && stacks>3){
                slices--;
                stacks--;
            }
            break;
        case 's':
            s-=10;
            genP3D(s);
            drawCube();
            break;
        case 'w':
            s+=10;
            genP3D(s);
            drawCube();
            break;
        
    }
    glutPostRedisplay();
}

#endif // 0

static void idle(void){
    glutPostRedisplay();
}


void calcV(){
    for(int i=0; i<3; i++){
        v[i] = cop[i] - copoly[i];
    }
    double denominator = sqrt(pow(v[0],2) + pow(v[1],2) + pow(v[2],2));
    v[0] = v[0]/denominator;
    v[1] = v[1]/denominator;
    v[2] = v[2]/denominator;
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialKey);
    //genLines();
    //glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}

