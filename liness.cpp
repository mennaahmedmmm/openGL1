#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>

int _CarPosition = 0;  // Current car position
int _CarDirection = 1; // 1 for forward, -1 for backward

void init() {
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set up orthogonal 2D view
}

float TireRotateAngle = 0.0f;

void CarTire(int xx, int yy, float r) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(TireRotateAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xx, y + yy);
    }
    glEnd();
    glPopMatrix();
}

void ScaledTire() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(140.1, 95, 0);
    glScalef(80, 80, 0);
    glColor3ub(0, 0, 0);  // Black tire
    CarTire(0, 0, 0.2);
    glColor3ub(192, 192, 192);  // Silver rim
    CarTire(0, 0, 0.13);
    glPopMatrix();
}

void CarBody() {
    glColor3ub(0, 0, 255);  // Blue car body
    glBegin(GL_POLYGON);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(240, 127);
    glVertex2f(240, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 127);
    glVertex2f(130, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON);  // Back light
    glColor3ub(255, 0, 0);
    glVertex2f(110, 92);
    glVertex2f(115, 92);
    glVertex2f(115, 117);
    glVertex2f(110, 117);
    glEnd();

    glBegin(GL_POLYGON);  // Window
    glColor3ub(0, 0, 0);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(120, 127);
    glVertex2f(130, 127);
    glEnd();
}

void fullCar() {
    CarBody();
    ScaledTire();
    glPushMatrix();
    glTranslatef(65, 0, 0);
    ScaledTire();
    glPopMatrix();
}

void MovingCar() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_CarPosition, 140, 0);
    fullCar();
    glPopMatrix();
}

void TireRotate(int value) {
    TireRotateAngle -= 5.0f;
    glutPostRedisplay();
    glutTimerFunc(25, TireRotate, 0);
}

void MoveCar(int value) {
    int carWidth = 240;  // Approximate car width
    int windowWidth = 500;  // Window width

    _CarPosition += _CarDirection * 2;  // Move the car

    // Forward movement: stop when the front edge reaches the right boundary
    if (_CarDirection == 1 && _CarPosition + carWidth >= windowWidth) {
        _CarPosition = windowWidth - carWidth;  // Align front edge
        _CarDirection = -1;  // Reverse direction
    }
    // Backward movement: stop when the rear edge reaches the left boundary
    else if (_CarDirection == -1 && _CarPosition <= 0) {
        _CarPosition = 0;  // Align rear edge
        _CarDirection = 1;  // Reverse direction
    }

    glutPostRedisplay();
    glutTimerFunc(20, MoveCar, 0);
}


void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    MovingCar();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);  // Adjusted window size for simplicity
    glutCreateWindow("Car Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, TireRotate, 0);
    glutTimerFunc(20, MoveCar, 0);
    glutMainLoop();
    return 0;
}
