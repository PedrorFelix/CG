#include "Nave.h"
#include "Sistema.h"


Nave::Nave(){

	position[0] = position[1] = 0.0;
	velX = 1.5;
	velY = 1.5;

}

Nave::Nave(GLfloat px, GLfloat py) {

	position[0] = px;
	position[1] = py;
	velX = 1.0;
	velY = 1.5;
	//std::cout << worldCoordinates[0] << std::endl;

}

GLint Nave::getPosX(GLvoid) {
	return position[0];
}

GLint Nave::getPosY(GLvoid) {
	return position[1];
}

GLboolean Nave::mover(GLint direction) {
	printf("%d\n", getPosX());
	switch (direction)
	{
	case 0://cima
		if (position[1] + velY + 6.0f < worldCoordinates[3]) {
			position[1] += velY;
			return true;
		}
		break;
	case 1://esquerda
		if(position[0] - velX - 3.0f > worldCoordinates[0]){
			position[0] -= velX;
			return true;			
		}
		break;
	case 2://baixo
		if (position[1] - velY - 4.0f > worldCoordinates[2]) {
			position[1] -= velY;
			return true;
		}
		break;
	case 3://direita
		if (position[0] + velX + 3.0f < worldCoordinates[3]) {
			position[0] += velX;
			return true;
		}
		break;
	default:
		break;
	}
	return true;
}

GLfloat* Nave::getCollisionBox(GLvoid) {
	GLfloat collisonBox[4];
	collisonBox[0] = position[0] - 3; //xMin
	collisonBox[1] = position[0] + 2;
	collisonBox[2] = position[1] - 4; //yMin
	collisonBox[3] = position[1] + 6;

	return collisonBox;
}

void Nave::cockpit(){

	glBegin(GL_TRIANGLES); {

		glVertex2f(0.0f, 0.0f);
		glVertex2f(2.0f, 6.0f);
		glVertex2f(4.0f, 0.0f);
	}glEnd();


}
void Nave::asaEsquerda(){

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.5f, 3.0f);
		glVertex2f(1.5f, 0.0f);

	}glEnd();
}
void Nave::corpoNave(){

	glBegin(GL_QUADS); {

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 4.0f);
		glVertex2f(4.0f, 4.0f);
		glVertex2f(4.0f, 0.0f);
	}glEnd();


}
void Nave::asaDireita() {

	glBegin(GL_TRIANGLES); {

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 3.0f);
		glVertex2f(1.5f, 0.0f);


	}glEnd();
}

// como é um metodo de ajuda não deve estar incluido na classe Nave.h
void ajudaEixos() {
	//desenhar os eixos
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES); {
	
		glVertex2f(0.0f, 0.0f);
		glVertex2f(2.0f, 0.0f);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 2.0f);
	
	}

	glEnd();
}

void Nave::desenhar(GLvoid) {
	// em vez de ter glMatrixIden temos translacoes controladas com pilha


	// ajudaEixos();

	glColor3f(0.0f, 1.0f, 0.0f);
	
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// onde eu quero colocar a nave, que vai servir para fazer o resto das translacoes,
	// ou seja é uma translacao que soma com todas as outras translacoes


	glTranslatef(position[0],position[1], 0.0f);
	glPushMatrix();
	glTranslatef(-2.0f, -4.0f, 0.0f);
	corpoNave();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.50f, -3.0f, 0.0f);
	asaEsquerda();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.0f, -3.0f, 0.0f);
	asaDireita();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	cockpit();
	glPopMatrix();
	glPopMatrix();

}
Nave::~Nave(){

}
