#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define GL_PI 3.14

void RenderScene (void) {
    static GLdouble dRadius = 1;
    static GLdouble dAngle = 0.0;
    if (dAngle == 0.1)
        glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
    glEnd();
    dRadius *= 1.01;
    dAngle += 0.1;
    if (dAngle > 50.0) {
        dRadius = 0.1;
        dAngle = 0.0;
    }
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat nRange = 100.0f;
    GLfloat aspectRatio;
    glClear(GL_COLOR_BUFFER_BIT);
    if (h == 0) 
        h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat) w / (GLfloat) h;
    if (w <= h) {
        glOrtho (-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, nRange);
    } else {
        glOrtho (-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
}

void TimerFunction (int value) {
    glutTimerFunc (33, TimerFunction, 1);
    glutPostRedisplay();
}

void SetupRC() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("single");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc (33, TimerFunction, 1);
    SetupRC();
    glutMainLoop();
    return 0;
}
