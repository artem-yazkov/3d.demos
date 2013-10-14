#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

static GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

typedef struct gear_s
{
    GLfloat radius_inner;
    GLfloat radius_outer;
    GLfloat width;
    GLint   tooth_count;
    GLfloat tooth_depth;
} gear_t;

void drawGear(gear_t *gear)
{
    GLint i;
    GLfloat r0, r1, r2;
    GLfloat angle, da;
    GLfloat u, v, len;

    r0 = gear->radius_inner;
    r1 = gear->radius_outer - gear->tooth_depth / 2.0;
    r2 = gear->radius_outer + gear->tooth_depth / 2.0;

    glShadeModel(GL_FLAT);

    glNormal3f(0.0, 0.0, 1.0);

    /* draw front face */
    glBegin(GL_QUAD_STRIP);
    da = 2.0 * M_PI / gear->tooth_count / 4.0;
    for (i = 0; i <= gear->tooth_count; i++)
    {
       angle = i * 2.0 * M_PI / gear->tooth_count;
       glVertex3f(r0 * cos(angle), r0 * sin(angle), gear->width * 0.5);
       glVertex3f(r1 * cos(angle), r1 * sin(angle), gear->width * 0.5);
       if (i < gear->tooth_count)
       {
           glVertex3f(r0 * cos(angle + 0 * da), r0 * sin(angle + 0 * da), gear->width * 0.5);
           glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), gear->width * 0.5);
       }
    }
    glEnd();

    /* draw front sides of teeth */
    glBegin(GL_QUADS);
    da = 2.0 * M_PI / gear->tooth_count / 4.0;
    for (i = 0; i < gear->tooth_count; i++)
    {
       angle = i * 2.0 * M_PI / gear->tooth_count;
       glVertex3f(r1 * cos(angle + 0 * da), r1 * sin(angle + 0 * da), gear->width * 0.5);
       glVertex3f(r2 * cos(angle + 1 * da), r2 * sin(angle + 1 * da), gear->width * 0.5);
       glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), gear->width * 0.5);
       glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), gear->width * 0.5);
    }
    glEnd();

    glNormal3f(0.0, 0.0, -1.0);

    /* draw back face */
    glBegin(GL_QUAD_STRIP);
    da = 2.0 * M_PI / gear->tooth_count / 4.0;
    for (i = 0; i <= gear->tooth_count; i++)
    {
       angle = i * 2.0 * M_PI / gear->tooth_count;
       glVertex3f(r1 * cos(angle), r1 * sin(angle), -gear->width * 0.5);
       glVertex3f(r0 * cos(angle), r0 * sin(angle), -gear->width * 0.5);
       if (i < gear->tooth_count)
       {
           glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), - gear->width * 0.5);
           glVertex3f(r0 * cos(angle + 0 * da), r0 * sin(angle + 0 * da), - gear->width * 0.5);
       }
    }
    glEnd();

    /* draw back sides of teeth */
    glBegin(GL_QUADS);
    da = 2.0 * M_PI / gear->tooth_count / 4.0;
    for (i = 0; i < gear->tooth_count; i++)
    {
       angle = i * 2.0 * M_PI / gear->tooth_count;

       glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -gear->width * 0.5);
       glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -gear->width * 0.5);
       glVertex3f(r2 * cos(angle + 1 * da), r2 * sin(angle + 1 * da), -gear->width * 0.5);
       glVertex3f(r1 * cos(angle + 0 * da), r1 * sin(angle + 0 * da), -gear->width * 0.5);
    }
    glEnd();

    /* draw outward faces of teeth */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < gear->tooth_count; i++)
    {
        angle = i * 2.0 * M_PI / gear->tooth_count;

        glVertex3f(r1 * cos(angle), r1 * sin(angle), gear->width * 0.5);
        glVertex3f(r1 * cos(angle), r1 * sin(angle), -gear->width * 0.5);
        u = r2 * cos(angle + da) - r1 * cos(angle);
        v = r2 * sin(angle + da) - r1 * sin(angle);
        len = sqrt(u * u + v * v);
        u /= len;
        v /= len;
        glNormal3f(v, -u, 0.0);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da),  gear->width * 0.5);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -gear->width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da),  gear->width * 0.5);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -gear->width * 0.5);
        u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
        v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
        glNormal3f(v, -u, 0.0);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),  gear->width * 0.5);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -gear->width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
     }

     glVertex3f(r1 * cos(0), r1 * sin(0),  gear->width * 0.5);
     glVertex3f(r1 * cos(0), r1 * sin(0), -gear->width * 0.5);

     glEnd();

     glShadeModel(GL_SMOOTH);

     /* draw inside radius cylinder */
     glBegin(GL_QUAD_STRIP);
     for (i = 0; i <= gear->tooth_count; i++)
     {
        angle = i * 2.0 * M_PI / gear->tooth_count;
        glNormal3f(-cos(angle), -sin(angle), 0.0);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), -gear->width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle),  gear->width * 0.5);
     }
     glEnd();

}

void renderScene()
{
    gear_t gear = {1.0, 4.0, 1.0, 20, 0.7};

    static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
    static GLfloat red[4] = { 0.8, 0.1,  0.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);

    glPushMatrix();
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    glRotatef(view_rotz, 0.0, 0.0, 1.0);

    drawGear(&gear);

    glPopMatrix();

    glFlush();
}

void changeSize(GLsizei w, GLsizei h)
{
    GLfloat aspect = (GLfloat) h / (GLfloat) w;

    glViewport(0, 0, (GLint) w, (GLint) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -aspect, aspect, 5.0, 60.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -40.0);

}

void handleKeysSpecial(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        view_roty += 5.0;
    } else if (key == GLUT_KEY_RIGHT)
    {
        view_roty -= 5.0;
    } else if (key == GLUT_KEY_UP)
    {
        view_rotx += 5.0;
    } else if (key == GLUT_KEY_DOWN)
    {
        view_rotx -= 5.0;
    }

    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("opengl fixed pipeline");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutSpecialFunc(handleKeysSpecial);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();

    return 0;
}
