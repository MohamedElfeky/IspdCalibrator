#ifndef HEADER_H
#define HEADER_H

#include <QtGui>
#include <QHeaderView>

class Header : public QHeaderView
{
public:
    Header(Qt::Orientation oritation, QWidget * parent = 0);

protected:
    void paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent * event);

private:
    bool isOn;
};

#endif // HEADER_H
