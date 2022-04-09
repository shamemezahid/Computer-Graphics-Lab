// Assignment 5
// Computer Graphics Lab 
// Shamim Bin Zahid 
// Roll 43

#include<bits/stdc++.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define HEIGHT 800
#define WIDTH 1000

typedef struct{
    float x;
    float y;
    float z;
} ver; 

typedef struct{
    float r;
    float a;
    float b;
    float c;
} sphere; 

ver Light={0, 0, -500};
int n;

static void reShape(int width, int height){
    const float ar = (float)width/(float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2,width/2-1,-height/2,height/2-1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static ver vec(ver p1, ver p2){ 
    ver V;
    float aV;
    V.x = p1.x - p2.x;
    V.y = p1.y - p2.y;
    V.z = p1.z - p2.z;
    aV=sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    V.x/=aV;
    V.y/=aV;
    V.z/=aV;
    return(V);
}

static float dot(ver a, ver b){ //dot product
    return(a.x*b.x + a.y*b.y + a.z*b.z);
}

static float mx(float a, float b){
    if(a<b) return a;
    else return b;
}

static void drawsphere(void){
    string filename("input.txt");
    double number;
    int flag = 0;
    vector<double>vec_center;

    //file input starts here
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
    }
    while (input_file >> number) {
        if(flag == 0){
            n = (int)number;
        }
        else{
            vec_center.push_back(number);
        }
        flag = 1;
    }
    cout << endl;
    input_file.close();
    //file input ends here

    sphere sp[n];

    int k = 0;
    for(int i = 0; i < n; i++){        
        sp[i].r = vec_center[k];
        k++;
        sp[i].a = vec_center[k];
        k++;
        sp[i].b = vec_center[k];
        k++;
        sp[i].c = vec_center[k];
        k++;
    }

    // debugging only
    // cout << n << endl;
    // for(int i = 0; i < n; i++){
    //     cout << sp[i].r << " " << sp[i].a << " " << sp[i].b << " "<< sp[i].c << endl;
    // }

    // hardcoding them values
    ver COP={0, 0, -500};
    float Zp = -250;
    
    ver P,N,L,Ce,V,H;
    float A,B,C,aH;
    int x,y,s,i;
    float I, tmin, t, t1,t2;
    for(y= -HEIGHT/2; y<HEIGHT/2; y++){
        for(x= -WIDTH/2; x<WIDTH/2; x++){
            tmin = 100000.0;
            for(s=0; s<n; s++){
                //A = (x - COP.x)^2 + (y - COP.y)^2 + (Zp - COP.z)^2;
                A = (x - COP.x)*(x - COP.x) + (y - COP.y)*(y - COP.y)
                + (Zp - COP.z)*(Zp - COP.z);
                B = 2*(COP.x-sp[s].a)*(x-COP.x) + 2*(COP.y-sp[s].b)*(y-COP.y)
                + 2*(COP.z-sp[s].c)*(Zp-COP.z);
                C = pow((COP.x-sp[s].a),2) + pow((COP.y-sp[s].b),2)
                +pow((COP.z-sp[s].c),2) -sp[s].r*sp[s].r;
                if(B*B < 4*A*C){ 
                    //no 
                } 
                else if(B*B == 4*A*C){ 
                    //boundary
                    t = -B/(2*A);
                    if(t<tmin){
                       tmin=t;
                       i = s; 
                    }
                }
                else{
                    //double intersection
                    t = (-B + sqrt(B*B - 4*A*C))/(2*A);
                    if(t<tmin){
                        tmin=t;
                        i = s;
                    }
                    t = (-B - sqrt(B*B - 4*A*C))/(2*A);
                    if(t<tmin){
                        tmin=t;
                        i = s;
                    }
                }
            }
            if(tmin == 100000.0){
                // no intersection
                glColor3f(0,0,0);
                glVertex2i(x,y);
            }
            else{
                P.x = COP.x + tmin*(x - COP.x);
                P.y = COP.y + tmin*(y - COP.y);
                P.z = COP.z + tmin*(Zp - COP.z);
                L=vec(Light, P);
                Ce.x=sp[i].a;
                Ce.y=sp[i].b;
                Ce.z=sp[i].c;
                N=vec(P, Ce);
                I=mx((0.2 + 0.8*dot(N,L)),1.0);
                glColor3f(I,I,I);
                glVertex2i(x,y);
            }
        }
    }
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glBegin(GL_POINTS);
    drawsphere();
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}


static void idle(void){
    glutPostRedisplay();
}

static void myinit(void){
    glClearColor(1,1,1,1);
}

static void specialKeyPressed(int key, int x, int y){
    int incr = 10;
    switch (key){
        case GLUT_KEY_UP: // Y Axis move up
            Light.y += incr;
            break;
        case GLUT_KEY_DOWN: // Y Axis move down
            Light.y -= incr;
            break;
        case GLUT_KEY_LEFT: // X Axis move left
            Light.x -= incr;
            break;
        case GLUT_KEY_RIGHT: // X Axis move right
            Light.x += incr;
            break;
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Shamim Bin Zahid | Ray Tracing");
    glutReshapeFunc(reShape);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyPressed);
    glutIdleFunc(idle);
    myinit();
    glutMainLoop();
    return EXIT_SUCCESS;
}

