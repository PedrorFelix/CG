#pragma once
#include "Sistema.h"
class Bala
{
private:

	GLint posX;
	GLint posY;

	GLint speed;

	GLfloat posicaoBala[2];

	GLvoid corpo(GLvoid);

public:
	Bala(GLvoid);
	Bala(GLfloat, GLfloat);
	GLvoid desenhar(GLvoid);
	GLvoid mover(GLfloat, GLfloat);
	GLfloat getPosX(GLvoid);
	GLfloat getPosY(GLvoid);
	GLfloat* getCollisionBox(GLvoid);
	~Bala(GLvoid);
};

