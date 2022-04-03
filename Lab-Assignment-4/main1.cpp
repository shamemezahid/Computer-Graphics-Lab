#include<stdlib.h>
#include<GL/glut.h>

GLfloat vertices[]{
    -1,-1,-1,
     1,-1,-1,
     1, 1,-1,
    -1, 1,-1,
    -1,-1,-1,
     1,-1,-1,
     1, 1,-1,
    -1, 1,-1,
}

GLfloat colors[]{
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1,
}

GLubyte cubeIndices[]{
    0,3,2,1
    2,3,7,6
    0,4,7,3
    1,2,6,5
    4,5,6,7
    
}