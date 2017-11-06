#include "dialog.h"
#include "ui_dialog.h"

#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include <QAbstractButton>

static hdtas::HdtasMessage send_msg;
static hdtas::HdtasPackage send_pkg;
static std::pair<const unsigned char *, size_t> send_to;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getWindowTittle(const QString &title)
{
    m_windownTitle = title;
}

void Dialog::on_spinBox_valueChanged(int arg1)
{
    // mr spinbox
    // set auto report timevalue

    hdtas::HdtasCtlMrPbRequest mr_request;
    mr_request.WriteAutoReportInterval(arg1);
    mr_request.StartSerialize();
    int cnt = mr_request.GetSerializeCount();
    while (cnt--) {
        mr_request.Serialize(&send_msg);
        send_msg.Serialize(&send_pkg);
        send_to = send_pkg.Pack();
        map.insert(send_to.first, send_to.second);
    }

    ui->buttonBox->setEnabled(true);
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            emit send(reinterpret_cast<const char *>(it.key()), it.value());
        }
    }
    if (button == ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        map.clear();
    }
}

void Dialog::on_pushButton_clicked()
{
    // restart mr
    ui->pushButton->setDisabled(true);

    hdtas::HdtasCtlMrPbRequest mr_request;
    std::string mr_id_str = m_windownTitle.toLocal8Bit().constData();
    device_mr_id mr_id;
    int ret = hdtas::utility::hex_2_int(mr_id_str, mr_id);
    if (-1 == ret) {
        qCritical("convert hex to int failed");
        return;
    }
    mr_request.Reboot_MR(mr_id);
    mr_request.StartSerialize();
    int cnt = mr_request.GetSerializeCount();
    while (cnt--) {
        mr_request.Serialize(&send_msg);
        send_msg.Serialize(&send_pkg);
        send_to = send_pkg.Pack();
        map.insert(send_to.first, send_to.second);
    }

    ui->buttonBox->setEnabled(true);
}

void Dialog::on_pushButton_2_clicked()
{
    // reset Mr
    ui->pushButton_2->setDisabled(true);

    hdtas::HdtasCtlMrPbRequest mr_request;
    std::string mr_id_str = m_windownTitle.toLocal8Bit().constData();
    device_mr_id mr_id;
    int ret = hdtas::utility::hex_2_int(mr_id_str, mr_id);
    if (-1 == ret) {
        qCritical("convert hex to int failed");
        return;
    }
    mr_request.Reset_MR(mr_id);
    mr_request.StartSerialize();
    int cnt = mr_request.GetSerializeCount();
    while (cnt--) {
        mr_request.Serialize(&send_msg);
        send_msg.Serialize(&send_pkg);
        send_to = send_pkg.Pack();
        map.insert(send_to.first, send_to.second);
    }

    ui->buttonBox->setEnabled(true);
}
