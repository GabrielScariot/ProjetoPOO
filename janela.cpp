#include "janela.h"
#include <QTextEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QLabel>
#include <QObject>
#include <QMessageBox>
#include <vector>
#include <QBrush>
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <fstream>
#include <QFileDialog>
#include <QFile>
#include "jogador.h"
#include "jogadorx.h"
#include "jogadoro.h"
#include <string>


Janela* Janela::instancia = nullptr;
Janela::Janela(QWidget *parent) : QMainWindow{parent}

{

    this->setGeometry(100,100,800,600);
    this->setWindowTitle("Jogo Da Velha");

    QMenuBar *barra = new QMenuBar(this);
    QMenu *menuArquivo = new QMenu("Arquivo", this);
    barra->addMenu(menuArquivo);

    QAction *acaoAbrir = new QAction("Salvar", this);
    menuArquivo->addAction(acaoAbrir);

    QAction *acaoAbrir2 = new QAction("Carregar",this);
    menuArquivo->addAction(acaoAbrir2);

    connect(acaoAbrir2, SIGNAL(triggered(bool)),this,SLOT(carregarJogo()));

    connect(acaoAbrir, SIGNAL(triggered(bool)),this,SLOT(salvarJogo()));

    X = new QPushButton("X",this);
    X->setGeometry(650,0,60,60);

    Y = new QPushButton("Y",this);
    Y->setGeometry(710,0,60,60);

    tabuleir = new QImage;
    tabuleir->load("C:/Users/Gabriel/Desktop/Imagem Tictac/Tabuleiro.jpg");

    imagemX = new QImage;
    imagemX->load("C:/Users/Gabriel/Desktop/Imagem Tictac/X.png");

    imagemO = new QImage;
    imagemO->load("C:/Users/Gabriel/Desktop/Imagem Tictac/O.png");
    for(int i =0;i<9;i++){
        tabuleiro.push_back(new vector<Item*>);
    }
    int y=20;
    for(int i =0;i<3;i++){
        int x=30;
        if(i>0){y+=200;}
        for(int j =0;j<3;j++){
            tabuleiro[i]->push_back(new Item(this));
            tabuleiro[i]->at(j)->setGeometry(x,y,150,150);
            connect(tabuleiro[i]->at(j), SIGNAL(fuiClicado()), this, SLOT(verificarJogada()));
            x+=200;
        }
    }



    //Clicando

    connect(X, SIGNAL(pressed()),this,SLOT(setPlayerX()));
    connect(Y, SIGNAL(pressed()),this,SLOT(setPlayerO()));

}


void Janela::salvarJogo(){
    QString nomeArquivo = QFileDialog::getSaveFileName(this);
    std::fstream f(nomeArquivo.toStdString(), std::fstream::out);
    std::string textoArquivo;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            char aux=tabuleiro[i]->at(j)->getLugar();
            f << aux;
        }
    }
    if(player=='X'){
        f<< '!';
    }
    if(player=='O'){
        f<< '?';
    }
    f.close();
}

void Janela::abrirArquivo(){
    if(JogoComeco==1){
        throw 1;
    }
    else throw 'c';
}
void Janela::carregarJogo()
{

    try{
       abrirArquivo();

    }
    catch(int x){
         QMessageBox::warning(this,"ERRO","Um jogo ja esta em andamento");
    }
    catch(char c){

        QString nomeArquivo = QFileDialog::getOpenFileName(this);
        int aux1=0,aux2=0;
        char aqr;

        std::fstream f(nomeArquivo.toStdString(), std::fstream::in);
        if(f.is_open()){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    f >> aqr;
                    tabuleiro[i]->at(j)->setLugar(aqr);
                    if(tabuleiro[i]->at(j)->getLugar()== 'X'){
                        tabuleiro[i]->at(j)->setImagemX();
                    }
                    if(tabuleiro[i]->at(j)->getLugar()== 'O'){
                        tabuleiro[i]->at(j)->setImagemO();
                    }
                }

            }
            while(!f.eof()){
                f>> aqr;
                if(aqr=='!'){
                    player= 'X';

                }
                if(aqr=='?'){
                    player = 'O';

                }
            }
        }
    }

}


void Janela::mostraVencedor(){
    if(player=='X'){
        QMessageBox::warning(this,"Vencedor","Vencedor é o O");
        hideLabel();

    }

    else if(player=='O'){
        QMessageBox::warning(this,"Vencedor","Vencedor é o X");
        hideLabel();

    }}

void Janela::mousePressEvent(QMouseEvent *event){

}

void Janela::setPlayerX(){
    JogoComeco=1;
    X->hide();
    Y->hide();

    player = PlayerX->getJogador();

}
void Janela::setPlayerO(){
    JogoComeco=1;
    X->hide();
    Y->hide();
    player = PlayerO->getJogador();
}

void Janela::paintEvent(QPaintEvent *event ){
    QPainter painter(this);
    painter.drawImage(0,0,*tabuleir);

}
void Janela::hideLabel(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tabuleiro[i]->at(j)->getLugar()== 'v'){
                tabuleiro[i]->at(j)->hide();
            }
        }
    }

}

void Janela::verificarJogada(){
    for(int i =0;i<3;i++){
        for(int j =0;j<3;j++){
            if(sender()== tabuleiro[i]->at(j)){
                if(player=='X'){
                    tabuleiro[i]->at(j)->setLugar(player);
                    tabuleiro[i]->at(j)->setImagemX();
                    disconnect(tabuleiro[i]->at(j), SIGNAL(fuiClicado()), this, SLOT(verificarJogada()));
                    player = PlayerO->getJogador();
                    Empate--;


                }

                else if(player=='O'){
                    tabuleiro[i]->at(j)->setLugar(player);
                    tabuleiro[i]->at(j)->setImagemO();
                    disconnect(tabuleiro[i]->at(j), SIGNAL(fuiClicado()), this, SLOT(verificarJogada()));
                    player = PlayerX->getJogador();;
                    Empate--;

                }

            }
        }


    }
    verificaVencedor();

}

void Janela::verificaVencedor(){


    for(int i =0;i<3;i++){

        //Verificando As Linhas
        if(tabuleiro[i]->at(0)->getLugar()==tabuleiro[i]->at(1)->getLugar() && tabuleiro[i]->at(1)->getLugar()==tabuleiro[i]->at(2)->getLugar()&&tabuleiro[i]->at(0)->getLugar()!='v'){
            mostraVencedor();
        }
        //Verificando as colunas
        if(tabuleiro[0]->at(i)->getLugar()==tabuleiro[1]->at(i)->getLugar() && tabuleiro[1]->at(i)->getLugar()==tabuleiro[2]->at(i)->getLugar()&&tabuleiro[0]->at(i)->getLugar()!='v'){
            mostraVencedor();
        }

    }
    //Verificando Diagonal Esquerda p/ Direita
    if(tabuleiro[0]->at(0)->getLugar()==tabuleiro[1]->at(1)->getLugar() && tabuleiro[1]->at(1)->getLugar()==tabuleiro[2]->at(2)->getLugar() &&tabuleiro[0]->at(0)->getLugar()!='v' ){
        mostraVencedor();
    }
    //Verificando Diagonal Direita p/ Esquerda
    if(tabuleiro[0]->at(2)->getLugar()==tabuleiro[1]->at(1)->getLugar() && tabuleiro[1]->at(1)->getLugar()==tabuleiro[2]->at(0)->getLugar() &&tabuleiro[0]->at(2)->getLugar()!='v' ){
        mostraVencedor();
    }
    if(Empate==0){
         QMessageBox::warning(this,"Empate","EMPATE");
         hideLabel();
    }


}







