#ifndef ITEM_H
#define ITEM_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QImage>
#include <vector>


class Item : public QLabel
{
    Q_OBJECT
public:
    Item(QWidget* parent = nullptr);
    Item();
    void mousePressEvent(QMouseEvent* event);
    //void paintEvent(QPaintEvent* event);
     void setLugar(char tipo);
     void setImagemX();
     void setImagemO();
    QImage *ImagemX,*ImagemO,ResizedX,ResizedO;
    char valor;
    char getLugar();





signals:
    fuiClicado();
};

#endif // ITEM_H
