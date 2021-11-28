// Ficha2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Sistema.h"
#include "Nave.h"
#include "Inimigo.h"
#include"Bala.h"

using namespace std;


//MENUS DE JOGO

// fonte do jogo
static void* font = GLUT_BITMAP_HELVETICA_18;


//Coordenadas de jogo (Sistema.h)
GLfloat worldCoordinates[4] = { -100.0f, 100.0f, -100.0f, 100.0f };


//Cria Nave
Nave* nave = new Nave(0.0,-75.0); // posicao inicial da nave

// vetores dos elementos que se movimentam sem a acao do jogadoor
vector<Bala*> balas;
vector<Inimigo*> inimigos;
vector<Bala*> balasInimigos;


GLboolean timeUp = false; //variavel para conseguir controlar o temporizador
GLboolean moverNave = false;

GLboolean disparou = false;


//Outras variaveis
GLint tempoBalasInimigos = 0;
GLboolean timerJogo = 0;


GLint vida = 3;
GLint pontuacao = 0;
GLint pontuacaoFinal;

GLvoid criarInimigos();


GLint direcaoInimigo = 3, invaderCountSideCollision;
GLint nInimigos = 0; //Contador de Inimigos derrotados
GLboolean pausa = false;


//Criação design do jogo
GLvoid reset();
GLboolean ganhou;


stringstream frase;
char caracter;

GLvoid desenharPontuacao() {
    frase.str("");
    frase.clear();
    frase << "Pontos: " << pontuacao << endl;
    while (frase.get(caracter)) {
        glutBitmapCharacter(font, caracter);
    }
}
GLvoid desenharPontuacaoFinal() {
    frase.str("");
    frase.clear();
    frase << "Pontuacao Final: " << pontuacaoFinal << endl;
    while (frase.get(caracter)) {
        glutBitmapCharacter(font, caracter);
    }
}
GLvoid desenharVida() {
    frase.str("");
    frase.clear();
    frase << "Vidas: " << vida << endl;
    while (frase.get(caracter)) {
        glutBitmapCharacter(font, caracter);
    }
}

void desenho(void) {

    glClearColor(0, 0, 0, 0);  // definir a cor de fundo --> preto
    glClear(GL_COLOR_BUFFER_BIT);  // limpar o buffer de cor
    glMatrixMode(GL_PROJECTION); // selação da matriz de projecao
    glLoadIdentity(); // carregar a matriz identidade 

    gluOrtho2D(worldCoordinates[0], worldCoordinates[1], worldCoordinates[2], worldCoordinates[3]); // definicao da tela = mundo de desenho de -100 a 100

    glMatrixMode(GL_MODELVIEW); // Matriz de visualização
    glLoadIdentity();

        glColor3f(1, 1, 1);
        glRasterPos2f(-90, -90);
        desenharPontuacao();
        glRasterPos2f(-70, -90);
        desenharVida();
        nave->desenhar();

        //Desenhar os Inimigos
        for (int i = 0; i < inimigos.size(); i++) {
            inimigos.at(i)->desenhar();
        }

        //insere 1 uma bala de cada nos vectores para o jogo não rebentar por causa do erase
        balas.push_back(new Bala(-101, -101));
        balasInimigos.push_back(new Bala(-101, -101));

        // Desenhar as balas da nave 
        for (int i = 0; i < balas.size(); i++) {
            balas.at(i)->desenhar();
        }

        /**** Desenhar as balas dos inimigos ****/
        for (int i = 0; i < balasInimigos.size(); i++) {
            balasInimigos.at(i)->desenhar();
        }
    

    glutSwapBuffers(); // So faço a troca de buffers quando acabo de desenhar tudo. 

}



//Metodos de inicialização do jogo!
GLvoid init() {
    pausa = false;
    vida = 3;
    nInimigos = 0;
    pontuacao = 0;
    nave = new Nave(0, -30);
    criarInimigos();
}


void teclado(unsigned char tecla, int x, int y) {
    GLboolean moveu = false;
    GLboolean disparo = false;
     
    if(!pausa){ 
        
    switch (tecla) {
    case 13:
        pausa = 1;
        break;
    case 27:
        exit(0);
        break;
    case 'w':   //UP
    case'W':
        moveu = nave->mover(0);
        break;
    case 'a':   //LEFT
    case'A':
        moveu = nave->mover(1);
        break;
    case 's':   //DOWN
    case'S':
        moveu = nave->mover(2);
        break;
    case 'd':   //RIGHT
    case'D':
        moveu = nave->mover(3);
        break;

    case 32:    //projetil
        balas.push_back(new Bala(nave->getPosX(), nave->getPosY()+ 6.0f));
        disparo = true;
        break;
    default:
        break;
    }
    }
    else 
        switch (tecla) {
        case 13:
            pausa = 0;
            break;
        case 27:
            exit(0);
        }
}

void criarInimigos() {
    GLfloat x = -80.0;
    GLfloat y = 80.0;
    for (int i = 0; i < 32; i++) { //i = numero de naves inimigas
        inimigos.push_back(new Inimigo(x, y));
        x = x + 10.0f;
        if (x >= 80.0) { //Sempre que X chega a -40 é retirado a Y 10, para desenhar o resto dos inimigos na linha de baixo. 
            x = -80.0f;
            y = y - 10.0f;
        }
    }

}
void moverInimigos() {
    //dominio de colissão dos inimigos
    GLfloat xMin, xMax, yMin, yMax, *currentInvaderPos;
    xMin = worldCoordinates[1] + 0.5f;
    xMax = worldCoordinates[0] - 0.5f;
    yMin = worldCoordinates[3] + 0.5f;
    yMax = worldCoordinates[2] - 0.5f;

        //ciclo
    for (int i = 0; i < inimigos.size(); i++) {
        currentInvaderPos = inimigos[i]->getPosition();

        if (currentInvaderPos[0] < xMin)
            xMin = currentInvaderPos[0];
        if (currentInvaderPos[0] > xMax)
            xMax = currentInvaderPos[0];
        if (currentInvaderPos[1] < yMin)
            yMin = currentInvaderPos[1];
        if (currentInvaderPos[1] > yMax)
            yMax = currentInvaderPos[1];
    }

    xMin = xMin - 1.5f;
    xMax = xMax + 1.5f;
    yMin = yMin - 1.0f;
    yMax = yMax + 1.0f;

    switch (direcaoInimigo) {
    case 1://left
        if (xMin - 0.2f <= worldCoordinates[0]) {
        direcaoInimigo = 3;
        invaderCountSideCollision++;
        }
    if (invaderCountSideCollision == 3) {
        invaderCountSideCollision = 0;
        direcaoInimigo = 2;
    }
        break;
    case 2://down
        direcaoInimigo = 3;
        break;
    case 3://right
        if (xMax + 0.2f >= worldCoordinates[1])
            direcaoInimigo = 1;
        break;
    }

    cout << xMin << "," << xMax << endl;

    //processar a direção de movimento
        
        //mover
        for (int i = 0; i < inimigos.size(); i++) {
            inimigos[i]->mover(direcaoInimigo);
        }

        
}
GLvoid removerBalas(GLint i) {
    balas.erase(balas.begin() + i);
}

GLvoid removerBalasInimigos(GLint i) {
    balasInimigos.erase(balasInimigos.begin() +i);
}

GLvoid removerInimigos(GLint i) {
    inimigos.erase(inimigos.begin() + i);
    nInimigos++;
    pontuacao = pontuacao + 10;
}

GLvoid reset() {
    for (int i = 0; i <= inimigos.size(); i++) {
        inimigos.clear();
        balas.clear();
    }
    init();
}
GLvoid criaBalaInimigo() { //Metodo que cria balas aleatorias dos inimigos 	
        //Escolhe inimigos aleatorios
    if (inimigos.size() > 0) {
        GLint inimigoA = rand() % inimigos.size();
        //Associa a variaveis o X e Y de cada Inimigo selecionado em cima
        GLfloat x = inimigos.at(inimigoA)->getPosition()[0];
        GLfloat y = inimigos.at(inimigoA)->getPosition()[1];
        //Cria 1 bala para cada inimigo
        balasInimigos.push_back(new Bala(x, y));
    }
}

//callback temporizado      repete a cada 0,50s
void timer(GLint i) {
    timerJogo = 1;
    glutTimerFunc(50, timer, 0);
}

void ColissaoNaveInimigo() {

    GLfloat xMinNave = nave->getCollisionBox()[0];
    GLfloat xMaxNave = nave->getCollisionBox()[1];
    GLfloat yMinNave = nave->getCollisionBox()[2];
    GLfloat yMaxNave = nave->getCollisionBox()[3];

    GLfloat xMinInimigo, xMaxInimigo, yMinInimigo, yMaxInimigo;

    for (int i = 0; i < inimigos.size(); i++) {

        xMinInimigo = inimigos[i]->getCollisionBox()[0];
        xMaxInimigo = inimigos[i]->getCollisionBox()[1];
        yMinInimigo = inimigos[i]->getCollisionBox()[2];
        yMaxInimigo = inimigos[i]->getCollisionBox()[3];

        if (!(xMaxInimigo <= xMinNave || yMinInimigo >= yMaxNave || xMinInimigo >= xMaxNave || yMaxInimigo <= yMinNave)) {
            removerInimigos(i);
            vida--;
        }
    }
}

void ColissaoNaveBalas() {

    GLfloat xMinNave = nave->getCollisionBox()[0];
    GLfloat xMaxNave = nave->getCollisionBox()[1];
    GLfloat yMinNave = nave->getCollisionBox()[2];
    GLfloat yMaxNave = nave->getCollisionBox()[3];

    GLfloat xMinBala, xMaxBala, yMinBala, yMaxBala;

    for (int i = 0; i < balasInimigos.size(); i++) {

        xMinBala = balasInimigos[i]->getCollisionBox()[0];
        xMaxBala = balasInimigos[i]->getCollisionBox()[1];
        yMinBala = balasInimigos[i]->getCollisionBox()[2];
        yMaxBala = balasInimigos[i]->getCollisionBox()[3];

        if (!(xMaxBala <= xMinNave || yMinBala >= yMaxNave || xMinBala >= xMaxNave || yMaxBala <= yMinNave)) {

            removerBalasInimigos(i);
            vida--;
        }
    }

}

void ColissaoInimigoBalas() {

    GLfloat xMinBala, xMaxBala, yMinBala, yMaxBala;
    GLfloat xMinInimigo, xMaxInimigo, yMinInimigo, yMaxInimigo;

    for (int i = 0; i < inimigos.size(); i++) {
        xMinInimigo = inimigos[i]->getCollisionBox()[0];
        xMaxInimigo = inimigos[i]->getCollisionBox()[1];
        yMinInimigo = inimigos[i]->getCollisionBox()[2];
        yMaxInimigo = inimigos[i]->getCollisionBox()[3];

        for (int j = 0; j < balas.size(); j++) {

            xMinBala = balas[j]->getCollisionBox()[0];
            xMaxBala = balas[j]->getCollisionBox()[1];
            yMinBala = balas[j]->getCollisionBox()[2];
            yMaxBala = balas[j]->getCollisionBox()[3];

            if (!(xMaxBala <= xMinInimigo || yMinBala >= yMaxInimigo || xMinBala >= xMaxInimigo || yMaxBala <= yMinInimigo)) {
                removerInimigos(i);
                removerBalas(j);
            }
        }
    }

}
GLvoid apagaBalas() {
    for (int i = 0; i < balas.size(); i++) {
        if (balas[i]->getPosY() > 101)
            balas.erase(balas.begin() + i);//apaga balas da nave que saem da tela de jogo
    }
    for (int i = 0; i < balasInimigos.size(); i++) {
        if (balasInimigos[i]->getPosY() < -101)
            balasInimigos.erase(balasInimigos.begin() + i);//apaga balas inimigas que saem da tela de jogo      
    }
}



//callback idle. Sempre que não acontece "nada"
void idle(GLvoid) {

    if (timerJogo)//resetar o timer
        timerJogo = 0;
    if (!pausa) {

        moverInimigos();

        for (int i = 1; i < balas.size(); i++) //Move balas do Jogador
            balas.at(i)->mover(0, 1);

        for (int j = 1; j < balasInimigos.size(); j++) //Move balas dos Inimigos
            balasInimigos[j]->mover(0, -1);

        //contra a velocidade das balas dos inimigos
        tempoBalasInimigos++;
        if (tempoBalasInimigos == 15) {

            criaBalaInimigo();
            tempoBalasInimigos = 0;
        }

        ColissaoNaveInimigo();
        ColissaoNaveBalas();
        ColissaoInimigoBalas();
        apagaBalas();

        if (vida == 0)
            reset();
        if (nInimigos >= 32)
            reset();
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Inicialização do freeGLUT

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Inicialização do modo de renderização #### GLUT_DOUBLE -> Modo de duplo buffer, tenho que trocar os buffers para aparecer o desenho

    glutInitWindowSize(800,800); // Definir o tamanho da janela

    glutInitWindowSize(0, 0); // Posição inicial da janela

    glutCreateWindow("Invaders!!"); // Criar a janela

     criarInimigos();


 // Registo das Callback
    //chama callback de desenho
   glutDisplayFunc(desenho);
   //chama callback idle
   glutIdleFunc(idle);
    //chama callback teclado
   glutKeyboardFunc(teclado);
    //chama callback timer
   glutTimerFunc(50, timer, 0);

    glutMainLoop(); // Iniciar o ciclo de eventos, so reage aos eventos programados


    return 0;

}
