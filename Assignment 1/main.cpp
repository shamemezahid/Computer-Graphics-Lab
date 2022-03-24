// Assignment 1 
// Computer Graphics Lab 
// Shamim Bin Zahid 
// Roll 43

#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>
#include<stdio.h>
static int W = 640;
static int H = 640;
static int ITERATIONS = 1000;

/* GLUT callback Handlers */

static void resize(int width, int height) {
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W / 2, W / 2, -H / 2, H / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// as drawline_0 originally was for zone 0
// this function takes zone as parameter and draws the points for the lines in drawline_0
void drawPoint(int x, int y, int zone){
       if(zone==0) glVertex2i(x,y);
  else if(zone==1) glVertex2i(y,x);
  else if(zone==2) glVertex2i(-y,x);
  else if(zone==3) glVertex2i(-x,y);
  else if(zone==4) glVertex2i(-x,-y);
  else if(zone==5) glVertex2i(-y,-x);
  else if(zone==6) glVertex2i(x,-y);
  else if(zone==7) glVertex2i(y,-x);
}

//bresenham algorithm to draw line with each point (modified with zone)
static void drawLine_0(int x0, int y0, int x1, int y1,int zone) {
    int dx = x1 - x0, dy = y1 - y0, x = x0, y = y0;
    int delE = 2 * dy, delNE = 2 * (dy - dx), d = 2 * dy - dx;
    glBegin(GL_POINTS); 
    // draws a pixel for each point in the line
    while (x < x1) {
        drawPoint(x, y, zone);
        if (d < 0) {
            d += delE;
            x++;
        }
        else {
            d += delNE;
            x++; y++;
        }
    }
    glEnd();
}

// finds the zone for each line
int ZoneFinder(int x0, int y0, int x1, int y1){
  int dx = x1 - x0;
  int dy = y1 - y0;
  if (dx >= 0 and dy >= 0){ 
    if (dx >= dy) return 0;
    else return 1;
  } else if (dx < 0 and dy >= 0){ 
    if (-dx >= dy)  return 3;
    else return 2;
  } else if (dx < 0 and dy < 0){  
    if (-dx >= -dy) return 4;
    else return 5;
  } else {
    if (dx >= -dy) return 7;  
    else return 6;
  }
}

//changes the parameter to drawline based on brasenham algorithm according to zone
void drawLine(int x0, int y0, int x1, int y1){
  int zone = ZoneFinder(x0, y0, x1, y1);
  printf("zone = %d\n", zone);
  // for each zone, brehenham algorithm is called thru drawLine_0
  if (zone == 0) drawLine_0(x0, y0, x1, y1, zone);
  else if (zone == 1) drawLine_0(y0, x0, y1, x1, zone);
  else if (zone == 2) drawLine_0(-y0, x0, -y1, x1, zone);
  else if (zone == 3) drawLine_0(-x0, y0, -x1, y1, zone);
  else if (zone == 4) drawLine_0(-x0, -y0, -x1, -y1, zone);
  else if (zone == 5) drawLine_0(-y0, -x0, -y1, -x1, zone);
  else if (zone == 6) drawLine_0(-y0, x0, -y1, x1, zone);
  else if (zone == 7) drawLine_0(x0, -y0, x1, -y1, zone);
}


static void display(void) {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0);
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2i(-W / 2, 0);
    glVertex2i(W / 2, 0);
    glVertex2i(0, -H / 2);
    glVertex2i(0, H / 2);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3d(1, 1, 0);
    // generates 1000 random lines and draws them
    for (int i = 0; i < ITERATIONS; i++) {
      // keeping the lines within the window screen
      int x0 = rand() % 640 - 320;
      int x1 = rand() % 640 - 320;
      int y0 = rand() % 640 - 320;
      int y1 = rand() % 640 - 320;
      int dx = x1 - x0;
      int dy = y1 - y0; 
      int z = ZoneFinder(x0, y0, x1, y1); //finds the zone of the line
      // for each zone, sets a different color and draws the line
      if(z==0){
        glColor3ub(255, 255, 255);
        drawLine(x0, y0 ,x1, y1);
      }
      if(z==1){
        glColor3ub(200, 25, 25);
        drawLine(x0, y0, x1, y1);
      }
      if(z==2){
        glColor3ub(25, 200, 25);
        drawLine(x0, y0, x1, y1);
      }
      if(z==3){
        glColor3ub(25, 25, 200);
        drawLine(x0, y0, x1, y1);
      }
      if(z==4){
          glColor3ub(25, 200, 200);
          drawLine(x0, y0, x1, y1);
      }
      if(z==5){
          glColor3ub(200, 25, 200);
          drawLine(x0, y0, x1, y1);
      }
      if(z==6){
          glColor3ub(200, 200, 25);
          drawLine(x0, y0, x1, y1);
      }
      if(z==7){
          glColor3ub(50, 100, 200);
          drawLine(x0, y0, x1, y1);
      }    
    }
    glPopMatrix();
    glutSwapBuffers();
}

#if 0
static void key(unsigned char key, int x, int y){
    switch (key){
    case 27:
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices > 3 && stacks > 3)
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

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

static void myInit(void) {
    glClearColor(0.1, 0.1, 0.1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}
/* Program entry point */

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("43 | Shamim Bin Zahid | Assignment 1");

    glutReshapeFunc(resize);
    myInit();
    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}



// run script
// g++ main.cpp -lGL -lglut -o main ./main