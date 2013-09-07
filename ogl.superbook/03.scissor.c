#include <GL/gl.h>
#include <GL/glut.h>

void RenderScene() {
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // in world coords
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-25.0f, 25.0f, 25.0f, -25.0f);

    // in window coords
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glScissor(70, 70, 140, 140);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    // in window coords
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glScissor(90, 90, 100, 100);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDisable(GL_SCISSOR_TEST);
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

int main(int argc, char **argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}
