#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>
static int W=640;
static int H=480;

/* GLUT callback Handlers */

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
            x++; y++;
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
            x++; y++;
        }
        else{
            d+=delN;
            y++;
        }
    glVertex2i(x,y);
    }
    glEnd();
}

static int zone(int dx, int dy){
    if(dx>=0 && dy >= 0){
        if(dx>=dy) return(0);
        else return(1);
    }
    else if(dx<0 && dy<0){
      if(abs(dx)>=abs(dy)) return(4);
        else return(5);
    }
}

static void display(void){
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
    glBegin(GL_LINES);
        glVertex2i(-W/2, 0);
        glVertex2i(W/2, 0);
        glVertex2i(0, -H/2);
        glVertex2i(0, H/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3d(1,1,0);
    for(int i=0; i<100; i++){
        int x0=rand()%640; x0-=320;
        int x1=rand()%640; x1-=320;
        int y0=rand()%480; y0-=240;
        int y1=rand()%480; y1-=240;
        int dx=x1-x0, dy=y1-y0;
        int Zone = zone(dx,dy);
        if(Zone==0){
            glColor3f(1,1,0.5);
            drawLine_0(x0, y0 ,x1, y1);
        }
        if(Zone==1){
            glColor3d(1,0.5,1);
            drawLine_1(x0, y0, x1, y1);
        }
    }
    glPopMatrix();

    glutSwapBuffers();
}

#if 0
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}
#endif // 0
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

static void myInit(void){
glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

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
    myInit();
    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
