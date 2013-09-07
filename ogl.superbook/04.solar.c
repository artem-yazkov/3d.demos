#include <GL/gl.h>
#include <GL/glut.h>

void RenderScene (void) {

    static float fMoonRot = 0.0f;
    static float fEarthRot = 0.0f;
/*
    float ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // first, move camera    
    glTranslatef(0.0f, 0.0f, -300.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

   GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 0.0, 0.0, 25.0, 1.0 };
   GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 0.0 };

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
    
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_SMOOTH);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();


    
    // light point
/*
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_COLOR_MATERIAL);
*/
    // put sun in center
    glColor3ub(255,255,0);
    glutSolidSphere(15.0f, 15, 15);
    
    
    // earth
    glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(105.0f, 0.0f, 0.0f);
    glColor3ub(0, 0, 255);
    glutSolidSphere(15.0f, 15, 15);

    // moon
    glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    glColor3ub(200,200,200);
    glutSolidSphere(6.0f, 15, 15);

    fMoonRot += 3.0f;
    if (fMoonRot > 360.0f)
	fMoonRot = 0.0f;
    fEarthRot += 1.0f;
    if (fEarthRot > 360.0f)
	fEarthRot = 0.0f;

    glutSwapBuffers();

}

void TimerFunction (int value) {
    glutTimerFunc (33, TimerFunction, 1);
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
    //GLfloat nRange = 100.0f;
    GLfloat aspectRatio;
    if (h == 0) 
	h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat) w / (GLfloat) h;
    gluPerspective(45.0f, aspectRatio, 1.0, 425.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
}

void SetupRC() {
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);        
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("solar");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutTimerFunc (33, TimerFunction, 1);
    glutMainLoop();
	return 0;
}
