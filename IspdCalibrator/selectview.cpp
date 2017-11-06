#include "selectview.h"
#include "ui_selectview.h"

SelectView::SelectView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectView)
{
    ui->setupUi(this);
}

SelectView::~SelectView()
{
    delete ui;
}

void SelectView::closeEvent(QCloseEvent *event)
{
    event->accept();

    emit quit();
}

void SelectView::on_pushButton_clicked()
{
   // 烧录ID
    this->hide();
    emit record_id();
}

void SelectView::on_pushButton_2_clicked()
{
   // 检测标签
    this->hide();
    emit test_ispd();
}

void SelectView::close()
{
    this->reject();
}
