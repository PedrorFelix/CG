#include "Bala.h"

Bala::Bala(GLvoid) {

	posicaoBala[0] = 0; //x
	posicaoBala[1] = 0; //y

}

Bala::Bala(GLfloat x, GLfloat y) {

	posicaoBala[0] = x - 0; //trocar para desenhar corretamente
	posicaoBala[1] = y - 0;

}

GLvoid Bala::desenhar(GLvoid) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(posicaoBala[0], posicaoBala[1], 0);
	glPushMatrix();

	corpo();

	glPopMatrix();
	glPopMatrix();
}

GLvoid Bala::mover(GLfloat movX, GLfloat movY) {
	posicaoBala[0] += movX;
	posicaoBala[1] += movY;

	glutPostRedisplay();
}

GLfloat Bala::getPosX(GLvoid) {

	return posicaoBala[0]; //x
}

GLfloat Bala::getPosY(GLvoid) {

	return posicaoBala[1]; //y
}

GLvoid Bala::corpo(GLvoid) {

	glColor3f(1, 1, 1);

	glBegin(GL_QUADS); {
		glVertex2f(0.0, 0.0);
		glVertex2f(0.2, 0.0);
		glVertex2f(0.2, 1.0);
		glVertex2f(0.0, 1.0);
	}
	glEnd();
}

GLfloat* Bala::getCollisionBox(GLvoid) {

	static GLfloat collisionbox[4];
	collisionbox[0] = posicaoBala[0] - 0.25;
	collisionbox[1] = posicaoBala[0] + 0.25;
	collisionbox[2] = posicaoBala[1] - 0.1;
	collisionbox[3] = posicaoBala[1] + 0.1;

	return collisionbox;
}

Bala::~Bala(GLvoid)
{
}
