#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define GL_PI 3.14

GLfloat sizes[2];
GLfloat step;

void RenderScene (void)
{
    GLfloat y;
    GLfloat curSize = sizes[0];

    GLint factor = 1;
    GLushort pattern = 0x5555;
    glEnable(GL_LINE_STIPPLE);

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    for (y = -90.0f; y <= 90.f; y += 20.0f) 
    {
        glLineWidth(curSize);
        glLineStipple(factor, pattern);

        glBegin(GL_LINES);
        glVertex2f(-80.0f, y);
        glVertex2f(80.0f, y);
        glEnd();
        curSize += step;
        factor++;
    }

    glPopMatrix();
    glPushMatrix();
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat nRange = 100.0f;
    GLfloat aspectRatio;
    if (h == 0)
        h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat) w / (GLfloat) h;
    if (w <= h)
    {
        glOrtho (-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, nRange);
    } else 
    {
        glOrtho (-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);
    printf("GL_LINE_WIDTH_RANGE = (%f, %f); GL_LINE_WIDTH_GRANULARITY = %f\n",
    sizes[0], sizes[1], step);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bounce");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
