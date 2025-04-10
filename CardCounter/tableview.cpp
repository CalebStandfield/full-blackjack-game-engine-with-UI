#include "tableview.h"
#include <QPainter>
#include <QPixmap>
#include <QtWidgets/qboxlayout.h>
#include <qlabel.h>

TableView::TableView(QWidget *parent)
    : QWidget{parent}
{

}

TableView::~TableView()
{

}

void TableView::addCard(const QString& imagePath)
{
    QPixmap cardPixmap(imagePath);
    QLabel* cardLabel = new QLabel(this);
    cardLabel->setPixmap(cardPixmap.scaled(100, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cardLabel->setAlignment(Qt::AlignCenter);

    // Add to layout
    if (!layout()) {
        setLayout(new QHBoxLayout());
    }
    layout()->addWidget(cardLabel);
}

void TableView::addCardAt(const QString& imagePath, int x, int y)
{
    QPixmap cardPixmap(imagePath);
    if (cardPixmap.isNull()) {
        qDebug() << "FAILED TO LOAD IMAGE";
    }
    QLabel* cardLabel = new QLabel(this);
    cardLabel->setPixmap(cardPixmap.scaled(100, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cardLabel->resize(100, 150);
    cardLabel->move(x, y);
    cardLabel->show(); // Important when not using layouts
}
