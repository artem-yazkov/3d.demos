#include <GL/gl.h>
#include <GL/glut.h>

void RenderScene (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);

    // first red vertex
    glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
    glVertex3f(0.0f, 200.0f, 0.0f);

    // second green vertex
    glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
    glVertex3f(200.0f, -70.0f, 0.0f);

    // third blue vertex
    glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)250);
    glVertex3f(-200.0f, -70.0f, 0.0f);    
    glEnd();
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio;
    if (h == 0)
        h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat) w / (GLfloat) h;
    gluPerspective(45.0f, aspectRatio, 1.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -550.0f);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("triangle");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}
