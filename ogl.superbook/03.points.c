#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

static GLfloat xRotD = 1.5f;
static GLfloat yRotD = 0.5f;
static GLfloat zRotD = 0.0f;

void RenderScene()
{
    GLfloat x, y, z, angle;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    glBegin(GL_POINTS);
    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
    {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);
        glVertex3f(x, y, z);
        z += 0.5f;
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void TimerFunction(int value)
{
    xRot += xRotD;
    yRot += yRotD;
    zRot += zRotD;
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat nRange = 100.0f;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Points");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glColor3f(1.0f, 0.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutTimerFunc(33, TimerFunction, 1);
    glutMainLoop();
    return 0;
}
