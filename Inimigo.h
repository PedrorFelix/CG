#pragma once
#include "Sistema.h"

class Inimigo
{
private:
	// privados para que não possa alterar ao invocar a classe desenho

	GLfloat position[2];
	GLfloat velX;
	GLfloat velY;

	GLvoid cockpit();
	GLvoid asaDireita();
	GLvoid asaEsquerda();
	GLvoid corpoNave();

public:
	Inimigo();
	Inimigo(GLfloat, GLfloat);
	GLboolean mover(GLint);
	GLvoid desenhar(GLvoid);
	GLvoid inimigoUpDownDraw(GLvoid);
	GLvoid inimigoLeftRightDraw(GLvoid);
	GLfloat* getPosition(GLvoid);
	GLfloat* getCollisionBox(GLvoid);
	~Inimigo();

};

