#ifndef JANELA_H
#define JANELA_H
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QObject>
#include <iostream>
#include <vector>
#include <QTextEdit>
#include "item.h"
#include "jogador.h"
#include "jogadoro.h"
#include "jogadorx.h"

using namespace std;


class Janela: public QMainWindow{
    Q_OBJECT
    static Janela* instancia;
    QPushButton *X, *Y;
    QImage *imagemO, *imagemX, *tabuleir;
    QTextEdit *editor;
    static Janela *janela;
public:
    int Empate=9;
    void percorreVetor();
    Janela(const Janela &obj)= delete;
    Janela operator=(Janela obj) = delete;
    ~Janela(){}
    int JogoComeco=0;
    static Janela *getInstancia(){
        if(instancia == nullptr)
        {
            instancia = new Janela();
        }
        return instancia;

    }
    explicit Janela(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void verificaVencedor();
    void mousePressEvent(QMouseEvent *event);
    char player;
    Jogador *PlayerX = new JogadorX;
    Jogador *PlayerO = new JogadorO;
    std::vector<std::vector<Item*>*> tabuleiro;

signals:
public slots:
    void verificarJogada();
    void setPlayerX();
    void setPlayerO();
    void mostraVencedor();
    void hideLabel();
    void salvarJogo();
    void carregarJogo();
    void abrirArquivo();

};

#endif // JANELA_H
