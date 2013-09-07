#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define TRUE 1
int bEdgeFlag = 0;

void RenderScene (void) {
    glPolygonMode(GL_FRONT, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES); 
    {
	// first
	glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, 0.0f);
	glEdgeFlag(TRUE);	
	glVertex2f(20.0f, 0.0f);
	glVertex2f(0.0f, 40.0f);
	//second
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-60.0f, -20.0f);	
	glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, -40.0f);
	// third
	glEdgeFlag(TRUE);
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(0.0f, -80.0f);
	glEdgeFlag(bEdgeFlag);
	glVertex2f(20.0f, -40.0f);	
	// fourth
	glEdgeFlag(TRUE);
	glVertex2f(20.0f, -40.0f);
	glVertex2f(60.0f, -20.0f);
	glEdgeFlag(bEdgeFlag);
	glVertex2f(20.0f, 0.0f);	
	glEdgeFlag(TRUE);
	
	// draw two triangles for central square	
	// first
	glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(20.0f, 0.0f);	
	// second
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(20.0f, -40.0f);
	glVertex2f(20.0f, 0.0f);
	glEdgeFlag(TRUE);	
    }
    glEnd();
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
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("stars");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
