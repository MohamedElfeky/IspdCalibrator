#ifndef SELECTVIEW_H
#define SELECTVIEW_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class SelectView;
}

class SelectView : public QDialog
{
    Q_OBJECT

public:
    explicit SelectView(QWidget *parent = 0);
    ~SelectView();

protected:
    void closeEvent(QCloseEvent * event) override;

signals:
    void quit();

    void record_id();
    void test_ispd();

private slots:
    void close();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::SelectView *ui;
};

#endif // SELECTVIEW_H
