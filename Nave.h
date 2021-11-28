#pragma once
#include "Sistema.h"


class Nave
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
	Nave();
	Nave(GLfloat, GLfloat);
	GLboolean mover(GLint);
	GLvoid desenhar(GLvoid);
	GLint getPosX(GLvoid);
	GLint getPosY(GLvoid);
	GLfloat* getCollisionBox(GLvoid);
	~Nave();

};

