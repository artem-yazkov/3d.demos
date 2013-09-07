#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define GL_PI 3.14

int bCull = 1;
int bDepth = 1;
int bOutline = 1;

int xRot = 0.0f;
int yRot = 0.0f;

void RenderScene (void) {
    GLfloat x,y,angle;
    int iPivot = 1;	// for color alternating    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (bCull)
	glEnable(GL_CULL_FACE);
    else 
	glDisable(GL_CULL_FACE);

    if (bDepth)
	glEnable(GL_DEPTH_TEST);
    else 
	glDisable(GL_DEPTH_TEST);

    if (bOutline)
	glPolygonMode(GL_BACK, GL_LINE);
    else
	glPolygonMode(GL_BACK, GL_FILL);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    // draw cone
    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 75.0f);
    for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
	x = 50.0f * sin(angle);
	y = 50.0f * cos(angle);
	if ((iPivot % 2) == 0)
	    glColor3f(0.0f, 1.0f, 0.0f);
	else 
	    glColor3f(1.0f, 0.0f, 0.0f);
	iPivot++;
	glVertex2f(x, y);
    }
    glEnd();

    // draw base
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
	x = 50.0f * sin(angle);
	y = 50.0f * cos(angle);
	if ((iPivot % 2) == 0)
	    glColor3f(0.0f, 1.0f, 0.0f);
	else 
	    glColor3f(1.0f, 0.0f, 0.0f);
	iPivot++;
	glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
}

void TimerFunction (int value) {
    xRot+=2;    
    yRot++;
    glutTimerFunc (33, TimerFunction, 1);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("triangles");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc (33, TimerFunction, 1);
    SetupRC();
    glutMainLoop();
    return 0;
}
