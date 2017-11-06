#ifndef DELEGATION_H
#define DELEGATION_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QPen>
#include <QTableView>

class delegation : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit delegation(QObject * parent = 0);
    virtual ~ delegation();
};

// readOnly
class readOnly_delegate : public delegation {
    Q_OBJECT
public:
    explicit readOnly_delegate(QObject * parent = 0);
protected:
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

// checkBox
class CheckBox_delegate : public delegation {
    Q_OBJECT
public:
    explicit CheckBox_delegate(QTableView * tableView);
protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QPen pen;
    QTableView * view;
};

#endif // DELEGATION_H
