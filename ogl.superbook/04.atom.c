#include <GL/gl.h>
#include <GL/glut.h>

void RenderScene (void) {
    static GLfloat fElect1 = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -100.0f);
    // red core
    glColor3ub(255, 0, 0);
    glutSolidSphere(10.0f, 15, 15);

    // yellow electrons
    glColor3ub(255, 255, 0);
    // first electron
    glPushMatrix();
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);    
    glTranslatef(90.0f, 0.0f, 0.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    // second electron
    glPushMatrix();
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);    
    glTranslatef(-70.0f, 0.0f, 0.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    // third electron 
    glPushMatrix();
    glRotatef(360.0f, -45.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);    
    glTranslatef(0.0f, 0.0f, 60.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    // increase electron's angle
    fElect1 += 1.0f;
    if (fElect1 > 360.0f)   
	fElect1 = 0.0f;
    glutSwapBuffers();
}

void TimerFunction (int value) {
    glutTimerFunc (33, TimerFunction, 1);
    glutPostRedisplay();
    
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


int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Atom");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc (33, TimerFunction, 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
	return 0;
}
