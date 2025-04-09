#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QtWidgets/qwidget.h>

class TableView : public QWidget
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView();

private:

signals:
};

#endif // TABLEVIEW_H
