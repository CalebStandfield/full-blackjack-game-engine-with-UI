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

void TableView::addCardAt(const QString& imagePath, int x, int y, qreal rotationAngle)
{
    QPixmap cardPixmap(imagePath);

    // Scale first to ensure consistent sizing
    QPixmap scaledPixmap = cardPixmap.scaled(75, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Then apply rotation
    QTransform transform;
    transform.rotate(rotationAngle);
    QPixmap rotatedPixmap = scaledPixmap.transformed(transform, Qt::SmoothTransformation);

    QLabel* cardLabel = new QLabel(this);
    cardLabel->setPixmap(rotatedPixmap);
    cardLabel->resize(rotatedPixmap.size());
    cardLabel->move(x, y);
    cardLabel->show();
}
