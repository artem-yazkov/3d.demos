#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

GLfloat rx1 = 0.0f;
GLfloat ry1 = 0.0f;
GLfloat rsize = 25;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene() {
    GLdouble dRadius = 0.1;
    GLdouble dAngle;
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClearStencil(0.0f);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_STRIP); 
    {
        for(dAngle = 0; dAngle < 400.0; dAngle += 0.1) {
            glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
            dRadius *= 1.002;
        }
    }
    glEnd();

    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(rx1, ry1, rx1 + rsize, ry1 - rsize);
    glutSwapBuffers();
}

void TimerFunction (int value) {
    if (rx1 > windowWidth - rsize || rx1 < -windowWidth)
        xstep = -xstep;
    if (ry1 > windowHeight || ry1 < -windowHeight + rsize)
        ystep = -ystep;
    rx1 += xstep;
    ry1 += ystep;
    
    if (rx1 > (windowWidth - rsize + xstep))
        rx1 = windowWidth - rsize - 1;
    else if (rx1 < -(windowWidth + xstep))	
        rx1 = -windowWidth - 1;

    if (ry1 > (windowHeight + ystep))
        ry1 = windowHeight - 1;
    else if (ry1 < -(windowHeight - rsize + ystep))	
        ry1 = -windowHeight + rsize - 1;

    glutPostRedisplay();
    glutTimerFunc (33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio;
    if (h == 0) 
        h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat) w / (GLfloat) h;
    if (w <= h) {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;	
        glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    } else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;	
        glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc (33, TimerFunction, 1);
    glutMainLoop();
    return 0;
}
