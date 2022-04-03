#include <math.h>
#include <GL/glut.h>


float transZ=50;      
float rotateA=0;         
float rotateAspeed=0.0;

void cube (float dimX, float dimY, float dimZ){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,dimY/2,0);
    glScalef(dimX/2, dimY/2, dimZ/2);

    glBegin(GL_QUADS);        
    glColor3f(0.0, 1.0, 0.0);    // Color Green - TOP

    glVertex3f(1.0, 1.0, 1.0); // TOP-RIGHT-NEAR
    glVertex3f(-1.0, 1.0, 1.0); // TOP-LEFT-NEAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-LEFT-FAR
    glVertex3f(1.0, 1.0, -1.0); // TOP-RIGHT-FAR

    glColor3f(1.0, 0.0, 0.0); // Color RED - Bottom

    glVertex3f(1.0, -1.0, 1.0); //BOTTOM-RIGHT-NEAR
    glVertex3f(-1.0, -1.0, 1.0); //BOTTOM-LEFT-NEAR
    glVertex3f(-1.0, -1.0, -1.0); //BOTTOM-LEFT-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-RIGHT-FAR

    glColor3f(1.0, 1.0, 0.0); // Color Yellow - Back

    glVertex3f(1.0, 1.0, -1.0); //TOP-RIGHT-FAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-LEFT-FAR
    glVertex3f(-1.0, -1.0, -1.0); //BOTTOM-LEFT-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-RIGHT-FAR

    glColor3f(0.0, 0.0, 1.0); //Color Blue - RIGHT

    glVertex3f(1.0, 1.0, 1.0); //TOP-FRONT-NEAR
    glVertex3f(1.0, 1.0, -1.0); //TOP-BACK-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-BACK-FAR
    glVertex3f(1.0, -1.0, 1.0); //BOTTOM-FRONT-NEAR

    glColor3f(1.0, 0.5, 0.0); //Color Orange - Left

    glVertex3f(-1.0, 1.0, 1.0); //TOP-FRONT-NEAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-BACK-FAR
    glVertex3f(-1.0, -1.0, -1.0);//BOTTOM-BACK-FAR
    glVertex3f(-1.0, -1.0, 1.0); //BOTTOM-FRONT-NEAR
    
    glEnd();
    glPopMatrix();
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix()
    glRotatef(alpha, 1, 0, 0); //rotate alpha around the x axis
    glRotatef(beta, 0, 1, 0); //rotate beta around the y axis
    glRotatef(gamma, 0, 0, 1); //rotate gamma around the z axis

    //dram my cube
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


   gluLookAt(transZ*cos(rotateA),10,transZ*sin(rotateA), 0,10,0, 0,1,0);

   cube(30,30,30);

   glFlush();            

   glutSwapBuffers();
}

void init (void){
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glFrustum(-1, 1, -1, 1, 1, 1000);

   glEnable(GL_DEPTH_TEST); 
}


void keyboard(unsigned char key, int x, int y){
switch (key) {
    case 27:                
        exit(0);
        break;
    case 'S':
        transZ+=1.0f;
        glutPostRedisplay();  
        break;
    case 'W':
        transZ-=1.0f;
        if (transZ<0) transZ=0;
        glutPostRedisplay();  
        break;
    case 's':
        transZ+=0.5f;
        glutPostRedisplay();  
        break;
    case 'w':
        transZ-=0.5f;
        if (transZ<0) transZ=0;
        glutPostRedisplay(); 
        break;
    case 'A':
        rotateAspeed+=0.001f;
        glutPostRedisplay();  
        break;
    case 'a':
        rotateAspeed+=0.001f;
        glutPostRedisplay();  
        break;
    case 'D':
        rotateAspeed-=0.001f;
        glutPostRedisplay();  
        break;
    case 'd':
        rotateAspeed-=0.001f;
        glutPostRedisplay();  
        break;
   }
}

void idle(void)
{
  rotateA=rotateA + rotateAspeed;
  glutPostRedisplay();    
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Cube");
   init ();

   glutDisplayFunc(display);
   glutIdleFunc(idle); 

   glutKeyboardFunc(keyboard); 
   glutMainLoop();
   return 0;
}