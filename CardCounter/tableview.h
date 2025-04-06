#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QObject>

class TableView : public QObject
{
    Q_OBJECT
public:
    explicit TableView(QObject *parent = nullptr);

signals:
};

#endif // TABLEVIEW_H
