#include "Inimigo.h"
#include "Sistema.h"


Inimigo::Inimigo() {

	position[0] =-101.0f; //fora da vista do jogador
	position[1] =-101.0f;
	velX = velY = 0.4f;

}

Inimigo::Inimigo(GLfloat px, GLfloat py) {

	position[0] = px;
	position[1] = py;
	//std::cout << worldCoordinates[0] << std::endl;
	velX = velY = 0.4;
}

void Inimigo::cockpit() {
	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 2.0f);
		glVertex2f(2.0f, 0.0f);
	}glEnd();
}
void Inimigo::asaEsquerda() {

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(2.0f, 1.0f);
		glVertex2f(2.0f, 0.0f);

	}glEnd();
}
void Inimigo::corpoNave() {

	glBegin(GL_QUADS); {

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 2.0f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(2.0f, 0.0f);
	}glEnd();


}
void Inimigo::asaDireita() {

	glBegin(GL_TRIANGLES); {

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(2.0f, 0.0f);
	}glEnd();
}

void Inimigo::desenhar() {
	// ajudaEixos();
	glColor3f(1.0f, 0.0f, 0.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glTranslatef(position[0], position[1], 0.0f);
	glPushMatrix();

	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.0f, -2.0f, 0.0f);
	corpoNave();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef(-3.0f, -1.0f, 0.0f);
	asaEsquerda();
	
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, -1.0f, 0.0f);
	asaDireita();	
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.0f, 0.0f, 0.0f);
	cockpit();	
	glPopMatrix();


	glPopMatrix();

	}



GLboolean Inimigo::mover(GLint dir) {
	switch (dir) {
	case 0:
		if ((position[1] + velY + 1.0f) < worldCoordinates[3]) {
			position[1] += velY;
			return true;
		}
		break;
	case 1:
		if ((position[0] - velX - 1.5f) > worldCoordinates[0]) {
			position[0] -= velX;
			return true;
		}
		break;
	case 2:
		if ((position[1] - velY - 1.0f) > worldCoordinates[2]) {
			position[1] -= velY;
			return true;
		}
		break;
	case 3:
		if ((position[0] + velX + 1.5f) < worldCoordinates[1]) {
			position[0] += velX;
			return true;
		}
		break;
	default:
		break;
	}
}

GLfloat* Inimigo::getPosition(GLvoid) {
	return position;
}


GLfloat* Inimigo::getCollisionBox(GLvoid) {
	static GLfloat collisionbox[4];
	collisionbox[0] = position[0] - 2;
	collisionbox[1] = position[0] + 2;
	collisionbox[2] = position[1] - 3;
	collisionbox[3] = position[1] + 3;
	return collisionbox;
}