#include "header.h"

Header::Header(Qt::Orientation orientation, QWidget * parent)
    : QHeaderView(orientation, parent)
{ }

void Header::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (0 == logicalIndex) {
        QStyleOption option;
        option.rect = QRect(10, 10, 10, 10);
        if (isOn) {
            option.state = QStyle::State_On;
        } else {
            option.state = QStyle::State_Off;
        }

        this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
    }
}

void Header::mousePressEvent(QMouseEvent *event)
{
    if (isOn) {
        isOn = false;
    } else {
        isOn = true;
    }

    this->update();
    QHeaderView::mousePressEvent(event);
}
