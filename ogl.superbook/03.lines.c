#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define GL_PI 3.14

void RenderScene (void) {
    GLfloat x, y, z, angle;    
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    //glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    z = 0.0f;
    for (angle = 0.0f; angle <= GL_PI; angle += (GL_PI / 20.0f)) {
	x = 50.0f * sin (angle);
	y = 50.0f * cos (angle);
	glVertex3f(x, y, z);
	x = 50.0f * sin (angle + GL_PI);
	y = 50.0f * cos (angle + GL_PI);
	glVertex3f(x, y, z);
    }    
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat nRange = 100.0f;
    GLfloat aspectRatio;
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

void SetupRC() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bounce");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
