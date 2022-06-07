#ifndef JOGADOR_H
#define JOGADOR_H
#include <QObject>

class Jogador : public QObject
{

public:
    virtual char getJogador()=0;
    Jogador();
};

#endif // JOGADOR_H
