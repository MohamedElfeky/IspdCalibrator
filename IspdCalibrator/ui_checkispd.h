/********************************************************************************
** Form generated from reading UI file 'checkispd.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKISPD_H
#define UI_CHECKISPD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckIspd
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QTextEdit *textEdit_log;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_open_sp;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_sp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_baud;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_data;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_check;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_stop;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_customize;
    QPushButton *pushButton_applicate;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_20;
    QComboBox *comboBox_mmr_ip;
    QPushButton *pushButton_init;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QLabel *label_status;
    QLabel *label_timeout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_readAll;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_ispd_no;
    QLineEdit *lineEdit_ispd_no;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_ispd_hz;
    QLineEdit *lineEdit_ispd_hz;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_ispd_version;
    QLineEdit *lineEdit_ispd_version;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QLabel *label_11;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *pushButton_ispd_hr;
    QLineEdit *lineEdit_ispd_hr1;
    QLineEdit *lineEdit_ispd_hr2;
    QLineEdit *lineEdit_ispd_hr3;
    QLineEdit *lineEdit_ispd_hr_avg;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_ispd_sensor;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_ispd_cmp;
    QLabel *label_6;
    QLineEdit *lineEdit_acc_sp;
    QLineEdit *lineEdit_acc_mr;
    QLineEdit *lineEdit_acc_cmp;
    QLabel *label_7;
    QLineEdit *lineEdit_gy_sp;
    QLineEdit *lineEdit_gy_mr;
    QLineEdit *lineEdit_gy_cmp;
    QLabel *label_8;
    QLineEdit *lineEdit_hr_sp;
    QLineEdit *lineEdit_hr_mr;
    QLineEdit *lineEdit_hr_cmp;
    QLabel *label_9;
    QLineEdit *lineEdit_volt_sp;
    QLineEdit *lineEdit_volt_mr;
    QLineEdit *lineEdit_volt_cmp;
    QLabel *label_19;
    QLineEdit *lineEdit_isCharge;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_21;
    QLineEdit *lineEdit_ispd_id;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_24;
    QComboBox *comboBox_type;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_22;
    QComboBox *comboBox_color;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_23;
    QComboBox *comboBox_size;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *pushButton_record;

    void setupUi(QDialog *CheckIspd)
    {
        if (CheckIspd->objectName().isEmpty())
            CheckIspd->setObjectName(QStringLiteral("CheckIspd"));
        CheckIspd->resize(827, 691);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/image/cjqc_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        CheckIspd->setWindowIcon(icon);
        gridLayout_4 = new QGridLayout(CheckIspd);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_4 = new QGroupBox(CheckIspd);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        groupBox_4->setFont(font);
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit_log = new QTextEdit(groupBox_4);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        textEdit_log->setFont(font1);

        gridLayout->addWidget(textEdit_log, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 1, 3, 1, 1);

        groupBox = new QGroupBox(CheckIspd);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_open_sp = new QPushButton(groupBox);
        pushButton_open_sp->setObjectName(QStringLiteral("pushButton_open_sp"));
        sizePolicy.setHeightForWidth(pushButton_open_sp->sizePolicy().hasHeightForWidth());
        pushButton_open_sp->setSizePolicy(sizePolicy);
        pushButton_open_sp->setMinimumSize(QSize(0, 20));
        pushButton_open_sp->setFont(font);
        pushButton_open_sp->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(pushButton_open_sp, 0, 1, 6, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        comboBox_sp = new QComboBox(groupBox);
        comboBox_sp->setObjectName(QStringLiteral("comboBox_sp"));
        sizePolicy.setHeightForWidth(comboBox_sp->sizePolicy().hasHeightForWidth());
        comboBox_sp->setSizePolicy(sizePolicy);
        comboBox_sp->setFont(font);
        comboBox_sp->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(comboBox_sp);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(20);
        label_2->setFont(font2);
        label_2->setLayoutDirection(Qt::RightToLeft);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        comboBox_baud = new QComboBox(groupBox);
        comboBox_baud->setObjectName(QStringLiteral("comboBox_baud"));
        sizePolicy.setHeightForWidth(comboBox_baud->sizePolicy().hasHeightForWidth());
        comboBox_baud->setSizePolicy(sizePolicy);
        comboBox_baud->setFont(font2);
        comboBox_baud->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(comboBox_baud);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        comboBox_data = new QComboBox(groupBox);
        comboBox_data->setObjectName(QStringLiteral("comboBox_data"));
        sizePolicy.setHeightForWidth(comboBox_data->sizePolicy().hasHeightForWidth());
        comboBox_data->setSizePolicy(sizePolicy);
        comboBox_data->setFont(font2);
        comboBox_data->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(comboBox_data);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        comboBox_check = new QComboBox(groupBox);
        comboBox_check->setObjectName(QStringLiteral("comboBox_check"));
        sizePolicy.setHeightForWidth(comboBox_check->sizePolicy().hasHeightForWidth());
        comboBox_check->setSizePolicy(sizePolicy);
        comboBox_check->setFont(font2);
        comboBox_check->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(comboBox_check);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5);

        comboBox_stop = new QComboBox(groupBox);
        comboBox_stop->setObjectName(QStringLiteral("comboBox_stop"));
        sizePolicy.setHeightForWidth(comboBox_stop->sizePolicy().hasHeightForWidth());
        comboBox_stop->setSizePolicy(sizePolicy);
        comboBox_stop->setFont(font2);
        comboBox_stop->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_5->addWidget(comboBox_stop);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_6 = new QGroupBox(CheckIspd);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        groupBox_6->setFont(font);
        verticalLayout_2 = new QVBoxLayout(groupBox_6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_customize = new QPushButton(groupBox_6);
        pushButton_customize->setObjectName(QStringLiteral("pushButton_customize"));
        sizePolicy1.setHeightForWidth(pushButton_customize->sizePolicy().hasHeightForWidth());
        pushButton_customize->setSizePolicy(sizePolicy1);
        pushButton_customize->setFont(font);

        verticalLayout_2->addWidget(pushButton_customize);

        pushButton_applicate = new QPushButton(groupBox_6);
        pushButton_applicate->setObjectName(QStringLiteral("pushButton_applicate"));
        sizePolicy1.setHeightForWidth(pushButton_applicate->sizePolicy().hasHeightForWidth());
        pushButton_applicate->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        font3.setKerning(true);
        pushButton_applicate->setFont(font3);

        verticalLayout_2->addWidget(pushButton_applicate);


        gridLayout_4->addWidget(groupBox_6, 1, 1, 1, 2);

        pushButton = new QPushButton(CheckIspd);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setFont(font);

        gridLayout_4->addWidget(pushButton, 0, 1, 1, 3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_20 = new QLabel(CheckIspd);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setFont(font);

        horizontalLayout_8->addWidget(label_20);

        comboBox_mmr_ip = new QComboBox(CheckIspd);
        comboBox_mmr_ip->setObjectName(QStringLiteral("comboBox_mmr_ip"));
        comboBox_mmr_ip->setFont(font);

        horizontalLayout_8->addWidget(comboBox_mmr_ip);

        pushButton_init = new QPushButton(CheckIspd);
        pushButton_init->setObjectName(QStringLiteral("pushButton_init"));
        pushButton_init->setFont(font);

        horizontalLayout_8->addWidget(pushButton_init);


        gridLayout_4->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_10 = new QLabel(CheckIspd);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setFamily(QStringLiteral("DokChampa"));
        font4.setPointSize(20);
        font4.setBold(true);
        font4.setWeight(75);
        label_10->setFont(font4);

        horizontalLayout_13->addWidget(label_10);

        label_status = new QLabel(CheckIspd);
        label_status->setObjectName(QStringLiteral("label_status"));
        QFont font5;
        font5.setPointSize(20);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setWeight(75);
        label_status->setFont(font5);

        horizontalLayout_13->addWidget(label_status);

        label_timeout = new QLabel(CheckIspd);
        label_timeout->setObjectName(QStringLiteral("label_timeout"));
        label_timeout->setFont(font5);

        horizontalLayout_13->addWidget(label_timeout);


        gridLayout_4->addLayout(horizontalLayout_13, 2, 0, 1, 4);

        tabWidget = new QTabWidget(CheckIspd);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_9 = new QGridLayout(tab);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pushButton_readAll = new QPushButton(groupBox_2);
        pushButton_readAll->setObjectName(QStringLiteral("pushButton_readAll"));
        sizePolicy1.setHeightForWidth(pushButton_readAll->sizePolicy().hasHeightForWidth());
        pushButton_readAll->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(pushButton_readAll, 0, 0, 3, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_ispd_no = new QPushButton(groupBox_2);
        pushButton_ispd_no->setObjectName(QStringLiteral("pushButton_ispd_no"));
        sizePolicy2.setHeightForWidth(pushButton_ispd_no->sizePolicy().hasHeightForWidth());
        pushButton_ispd_no->setSizePolicy(sizePolicy2);
        pushButton_ispd_no->setMinimumSize(QSize(0, 30));
        pushButton_ispd_no->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_7->addWidget(pushButton_ispd_no);

        lineEdit_ispd_no = new QLineEdit(groupBox_2);
        lineEdit_ispd_no->setObjectName(QStringLiteral("lineEdit_ispd_no"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_ispd_no->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_no->setSizePolicy(sizePolicy3);
        lineEdit_ispd_no->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_7->addWidget(lineEdit_ispd_no);


        gridLayout_5->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_ispd_hz = new QPushButton(groupBox_2);
        pushButton_ispd_hz->setObjectName(QStringLiteral("pushButton_ispd_hz"));
        sizePolicy3.setHeightForWidth(pushButton_ispd_hz->sizePolicy().hasHeightForWidth());
        pushButton_ispd_hz->setSizePolicy(sizePolicy3);
        pushButton_ispd_hz->setMinimumSize(QSize(0, 30));
        pushButton_ispd_hz->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_9->addWidget(pushButton_ispd_hz);

        lineEdit_ispd_hz = new QLineEdit(groupBox_2);
        lineEdit_ispd_hz->setObjectName(QStringLiteral("lineEdit_ispd_hz"));
        sizePolicy3.setHeightForWidth(lineEdit_ispd_hz->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_hz->setSizePolicy(sizePolicy3);
        lineEdit_ispd_hz->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_9->addWidget(lineEdit_ispd_hz);


        gridLayout_5->addLayout(horizontalLayout_9, 1, 1, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton_ispd_version = new QPushButton(groupBox_2);
        pushButton_ispd_version->setObjectName(QStringLiteral("pushButton_ispd_version"));
        sizePolicy3.setHeightForWidth(pushButton_ispd_version->sizePolicy().hasHeightForWidth());
        pushButton_ispd_version->setSizePolicy(sizePolicy3);
        pushButton_ispd_version->setMinimumSize(QSize(0, 30));
        pushButton_ispd_version->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_10->addWidget(pushButton_ispd_version);

        lineEdit_ispd_version = new QLineEdit(groupBox_2);
        lineEdit_ispd_version->setObjectName(QStringLiteral("lineEdit_ispd_version"));
        sizePolicy3.setHeightForWidth(lineEdit_ispd_version->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_version->setSizePolicy(sizePolicy3);
        lineEdit_ispd_version->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_10->addWidget(lineEdit_ispd_version);


        gridLayout_5->addLayout(horizontalLayout_10, 2, 1, 1, 1);


        gridLayout_9->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_8 = new QGridLayout(groupBox_5);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        QFont font6;
        font6.setPointSize(16);
        label_11->setFont(font6);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_11, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font6);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_16, 0, 2, 1, 1);

        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setFont(font6);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_17, 0, 3, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setFont(font6);
        label_18->setLayoutDirection(Qt::LeftToRight);
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_18, 0, 4, 1, 1);

        pushButton_ispd_hr = new QPushButton(groupBox_5);
        pushButton_ispd_hr->setObjectName(QStringLiteral("pushButton_ispd_hr"));
        sizePolicy1.setHeightForWidth(pushButton_ispd_hr->sizePolicy().hasHeightForWidth());
        pushButton_ispd_hr->setSizePolicy(sizePolicy1);
        pushButton_ispd_hr->setMinimumSize(QSize(0, 30));
        pushButton_ispd_hr->setFocusPolicy(Qt::TabFocus);

        gridLayout_7->addWidget(pushButton_ispd_hr, 1, 0, 1, 1);

        lineEdit_ispd_hr1 = new QLineEdit(groupBox_5);
        lineEdit_ispd_hr1->setObjectName(QStringLiteral("lineEdit_ispd_hr1"));
        sizePolicy1.setHeightForWidth(lineEdit_ispd_hr1->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_hr1->setSizePolicy(sizePolicy1);
        lineEdit_ispd_hr1->setFocusPolicy(Qt::NoFocus);

        gridLayout_7->addWidget(lineEdit_ispd_hr1, 1, 1, 1, 1);

        lineEdit_ispd_hr2 = new QLineEdit(groupBox_5);
        lineEdit_ispd_hr2->setObjectName(QStringLiteral("lineEdit_ispd_hr2"));
        sizePolicy1.setHeightForWidth(lineEdit_ispd_hr2->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_hr2->setSizePolicy(sizePolicy1);
        lineEdit_ispd_hr2->setFocusPolicy(Qt::NoFocus);

        gridLayout_7->addWidget(lineEdit_ispd_hr2, 1, 2, 1, 1);

        lineEdit_ispd_hr3 = new QLineEdit(groupBox_5);
        lineEdit_ispd_hr3->setObjectName(QStringLiteral("lineEdit_ispd_hr3"));
        sizePolicy1.setHeightForWidth(lineEdit_ispd_hr3->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_hr3->setSizePolicy(sizePolicy1);
        lineEdit_ispd_hr3->setFocusPolicy(Qt::NoFocus);

        gridLayout_7->addWidget(lineEdit_ispd_hr3, 1, 3, 1, 1);

        lineEdit_ispd_hr_avg = new QLineEdit(groupBox_5);
        lineEdit_ispd_hr_avg->setObjectName(QStringLiteral("lineEdit_ispd_hr_avg"));
        sizePolicy1.setHeightForWidth(lineEdit_ispd_hr_avg->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_hr_avg->setSizePolicy(sizePolicy1);
        lineEdit_ispd_hr_avg->setFocusPolicy(Qt::NoFocus);

        gridLayout_7->addWidget(lineEdit_ispd_hr_avg, 1, 4, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_5, 1, 0, 1, 1);

        tabWidget->addTab(tab, icon, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy4);
        groupBox_3->setFont(font2);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_3->addWidget(label_12, 0, 0, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setMinimumSize(QSize(0, 4));
        label_13->setBaseSize(QSize(0, 0));
        QFont font7;
        font7.setPointSize(18);
        label_13->setFont(font7);
        label_13->setLayoutDirection(Qt::LeftToRight);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_13, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setMinimumSize(QSize(0, 2));
        label_14->setFont(font7);
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_14, 0, 2, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setMinimumSize(QSize(0, 2));
        label_15->setFont(font7);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_15, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_ispd_sensor = new QPushButton(groupBox_3);
        pushButton_ispd_sensor->setObjectName(QStringLiteral("pushButton_ispd_sensor"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_ispd_sensor->sizePolicy().hasHeightForWidth());
        pushButton_ispd_sensor->setSizePolicy(sizePolicy5);
        pushButton_ispd_sensor->setMinimumSize(QSize(0, 40));
        pushButton_ispd_sensor->setFont(font2);
        pushButton_ispd_sensor->setFocusPolicy(Qt::TabFocus);

        verticalLayout->addWidget(pushButton_ispd_sensor);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_ispd_cmp = new QPushButton(groupBox_3);
        pushButton_ispd_cmp->setObjectName(QStringLiteral("pushButton_ispd_cmp"));
        sizePolicy5.setHeightForWidth(pushButton_ispd_cmp->sizePolicy().hasHeightForWidth());
        pushButton_ispd_cmp->setSizePolicy(sizePolicy5);
        pushButton_ispd_cmp->setMinimumSize(QSize(0, 40));
        pushButton_ispd_cmp->setFont(font2);
        pushButton_ispd_cmp->setFocusPolicy(Qt::TabFocus);

        verticalLayout->addWidget(pushButton_ispd_cmp);


        gridLayout_3->addLayout(verticalLayout, 0, 4, 6, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);
        label_6->setMinimumSize(QSize(0, 2));
        label_6->setFont(font7);

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_acc_sp = new QLineEdit(groupBox_3);
        lineEdit_acc_sp->setObjectName(QStringLiteral("lineEdit_acc_sp"));
        sizePolicy.setHeightForWidth(lineEdit_acc_sp->sizePolicy().hasHeightForWidth());
        lineEdit_acc_sp->setSizePolicy(sizePolicy);
        lineEdit_acc_sp->setFocusPolicy(Qt::NoFocus);
        lineEdit_acc_sp->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_acc_sp, 1, 1, 1, 1);

        lineEdit_acc_mr = new QLineEdit(groupBox_3);
        lineEdit_acc_mr->setObjectName(QStringLiteral("lineEdit_acc_mr"));
        sizePolicy.setHeightForWidth(lineEdit_acc_mr->sizePolicy().hasHeightForWidth());
        lineEdit_acc_mr->setSizePolicy(sizePolicy);
        lineEdit_acc_mr->setFocusPolicy(Qt::NoFocus);
        lineEdit_acc_mr->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_acc_mr, 1, 2, 1, 1);

        lineEdit_acc_cmp = new QLineEdit(groupBox_3);
        lineEdit_acc_cmp->setObjectName(QStringLiteral("lineEdit_acc_cmp"));
        sizePolicy.setHeightForWidth(lineEdit_acc_cmp->sizePolicy().hasHeightForWidth());
        lineEdit_acc_cmp->setSizePolicy(sizePolicy);
        lineEdit_acc_cmp->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(lineEdit_acc_cmp, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy5.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy5);
        label_7->setMinimumSize(QSize(0, 2));
        label_7->setFont(font7);

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_gy_sp = new QLineEdit(groupBox_3);
        lineEdit_gy_sp->setObjectName(QStringLiteral("lineEdit_gy_sp"));
        sizePolicy.setHeightForWidth(lineEdit_gy_sp->sizePolicy().hasHeightForWidth());
        lineEdit_gy_sp->setSizePolicy(sizePolicy);
        lineEdit_gy_sp->setFocusPolicy(Qt::NoFocus);
        lineEdit_gy_sp->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_gy_sp, 2, 1, 1, 1);

        lineEdit_gy_mr = new QLineEdit(groupBox_3);
        lineEdit_gy_mr->setObjectName(QStringLiteral("lineEdit_gy_mr"));
        sizePolicy.setHeightForWidth(lineEdit_gy_mr->sizePolicy().hasHeightForWidth());
        lineEdit_gy_mr->setSizePolicy(sizePolicy);
        lineEdit_gy_mr->setFocusPolicy(Qt::NoFocus);
        lineEdit_gy_mr->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_gy_mr, 2, 2, 1, 1);

        lineEdit_gy_cmp = new QLineEdit(groupBox_3);
        lineEdit_gy_cmp->setObjectName(QStringLiteral("lineEdit_gy_cmp"));
        sizePolicy.setHeightForWidth(lineEdit_gy_cmp->sizePolicy().hasHeightForWidth());
        lineEdit_gy_cmp->setSizePolicy(sizePolicy);
        lineEdit_gy_cmp->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(lineEdit_gy_cmp, 2, 3, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy5.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy5);
        label_8->setMinimumSize(QSize(0, 2));
        label_8->setFont(font7);

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        lineEdit_hr_sp = new QLineEdit(groupBox_3);
        lineEdit_hr_sp->setObjectName(QStringLiteral("lineEdit_hr_sp"));
        sizePolicy.setHeightForWidth(lineEdit_hr_sp->sizePolicy().hasHeightForWidth());
        lineEdit_hr_sp->setSizePolicy(sizePolicy);
        lineEdit_hr_sp->setFocusPolicy(Qt::NoFocus);
        lineEdit_hr_sp->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_hr_sp, 3, 1, 1, 1);

        lineEdit_hr_mr = new QLineEdit(groupBox_3);
        lineEdit_hr_mr->setObjectName(QStringLiteral("lineEdit_hr_mr"));
        sizePolicy.setHeightForWidth(lineEdit_hr_mr->sizePolicy().hasHeightForWidth());
        lineEdit_hr_mr->setSizePolicy(sizePolicy);
        lineEdit_hr_mr->setFocusPolicy(Qt::NoFocus);
        lineEdit_hr_mr->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_hr_mr, 3, 2, 1, 1);

        lineEdit_hr_cmp = new QLineEdit(groupBox_3);
        lineEdit_hr_cmp->setObjectName(QStringLiteral("lineEdit_hr_cmp"));
        sizePolicy.setHeightForWidth(lineEdit_hr_cmp->sizePolicy().hasHeightForWidth());
        lineEdit_hr_cmp->setSizePolicy(sizePolicy);
        lineEdit_hr_cmp->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(lineEdit_hr_cmp, 3, 3, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy5.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy5);
        label_9->setMinimumSize(QSize(0, 2));
        label_9->setFont(font7);

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        lineEdit_volt_sp = new QLineEdit(groupBox_3);
        lineEdit_volt_sp->setObjectName(QStringLiteral("lineEdit_volt_sp"));
        sizePolicy.setHeightForWidth(lineEdit_volt_sp->sizePolicy().hasHeightForWidth());
        lineEdit_volt_sp->setSizePolicy(sizePolicy);
        lineEdit_volt_sp->setFocusPolicy(Qt::NoFocus);
        lineEdit_volt_sp->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_volt_sp, 4, 1, 1, 1);

        lineEdit_volt_mr = new QLineEdit(groupBox_3);
        lineEdit_volt_mr->setObjectName(QStringLiteral("lineEdit_volt_mr"));
        sizePolicy.setHeightForWidth(lineEdit_volt_mr->sizePolicy().hasHeightForWidth());
        lineEdit_volt_mr->setSizePolicy(sizePolicy);
        lineEdit_volt_mr->setFocusPolicy(Qt::NoFocus);
        lineEdit_volt_mr->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_volt_mr, 4, 2, 1, 1);

        lineEdit_volt_cmp = new QLineEdit(groupBox_3);
        lineEdit_volt_cmp->setObjectName(QStringLiteral("lineEdit_volt_cmp"));
        sizePolicy.setHeightForWidth(lineEdit_volt_cmp->sizePolicy().hasHeightForWidth());
        lineEdit_volt_cmp->setSizePolicy(sizePolicy);
        lineEdit_volt_cmp->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(lineEdit_volt_cmp, 4, 3, 1, 1);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy5.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy5);
        label_19->setMinimumSize(QSize(0, 2));
        label_19->setFont(font7);

        gridLayout_3->addWidget(label_19, 5, 0, 1, 1);

        lineEdit_isCharge = new QLineEdit(groupBox_3);
        lineEdit_isCharge->setObjectName(QStringLiteral("lineEdit_isCharge"));
        sizePolicy.setHeightForWidth(lineEdit_isCharge->sizePolicy().hasHeightForWidth());
        lineEdit_isCharge->setSizePolicy(sizePolicy);
        lineEdit_isCharge->setFocusPolicy(Qt::NoFocus);
        lineEdit_isCharge->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_isCharge, 5, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_15 = new QHBoxLayout(tab_3);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_21 = new QLabel(tab_3);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_6->addWidget(label_21);

        lineEdit_ispd_id = new QLineEdit(tab_3);
        lineEdit_ispd_id->setObjectName(QStringLiteral("lineEdit_ispd_id"));
        sizePolicy.setHeightForWidth(lineEdit_ispd_id->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_id->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(lineEdit_ispd_id);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_14->addWidget(label_24);

        comboBox_type = new QComboBox(tab_3);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));
        sizePolicy.setHeightForWidth(comboBox_type->sizePolicy().hasHeightForWidth());
        comboBox_type->setSizePolicy(sizePolicy);
        comboBox_type->setEditable(false);

        horizontalLayout_14->addWidget(comboBox_type);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_22 = new QLabel(tab_3);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_11->addWidget(label_22);

        comboBox_color = new QComboBox(tab_3);
        comboBox_color->setObjectName(QStringLiteral("comboBox_color"));
        sizePolicy.setHeightForWidth(comboBox_color->sizePolicy().hasHeightForWidth());
        comboBox_color->setSizePolicy(sizePolicy);
        comboBox_color->setEditable(false);

        horizontalLayout_11->addWidget(comboBox_color);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_23 = new QLabel(tab_3);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_12->addWidget(label_23);

        comboBox_size = new QComboBox(tab_3);
        comboBox_size->setObjectName(QStringLiteral("comboBox_size"));
        sizePolicy.setHeightForWidth(comboBox_size->sizePolicy().hasHeightForWidth());
        comboBox_size->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(comboBox_size);


        verticalLayout_4->addLayout(horizontalLayout_12);


        horizontalLayout_15->addLayout(verticalLayout_4);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        pushButton_record = new QPushButton(tab_3);
        pushButton_record->setObjectName(QStringLiteral("pushButton_record"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_record->sizePolicy().hasHeightForWidth());
        pushButton_record->setSizePolicy(sizePolicy6);
        pushButton_record->setMinimumSize(QSize(450, 230));

        horizontalLayout_16->addWidget(pushButton_record);


        horizontalLayout_15->addLayout(horizontalLayout_16);

        tabWidget->addTab(tab_3, QString());

        gridLayout_4->addWidget(tabWidget, 3, 0, 1, 4);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(comboBox_sp);
        label_2->setBuddy(comboBox_baud);
        label_4->setBuddy(comboBox_data);
        label_3->setBuddy(comboBox_check);
        label_5->setBuddy(comboBox_stop);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(pushButton_open_sp, pushButton_ispd_no);
        QWidget::setTabOrder(pushButton_ispd_no, pushButton_ispd_hz);
        QWidget::setTabOrder(pushButton_ispd_hz, pushButton_ispd_version);
        QWidget::setTabOrder(pushButton_ispd_version, pushButton_ispd_sensor);

        retranslateUi(CheckIspd);

        tabWidget->setCurrentIndex(2);
        comboBox_type->setCurrentIndex(0);
        comboBox_color->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CheckIspd);
    } // setupUi

    void retranslateUi(QDialog *CheckIspd)
    {
        CheckIspd->setWindowTitle(QApplication::translate("CheckIspd", "\346\243\200\346\265\213\346\240\207\347\255\276", 0));
        groupBox_4->setTitle(QApplication::translate("CheckIspd", "UDP\346\225\260\346\215\256", 0));
        groupBox->setTitle(QApplication::translate("CheckIspd", "\344\270\262\345\217\243\350\256\276\347\275\256", 0));
        pushButton_open_sp->setText(QApplication::translate("CheckIspd", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
        label->setText(QApplication::translate("CheckIspd", "\344\270\262\345\217\243\345\217\267\357\274\232", 0));
        label_2->setText(QApplication::translate("CheckIspd", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        comboBox_baud->clear();
        comboBox_baud->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "230400", 0)
        );
        label_4->setText(QApplication::translate("CheckIspd", "\346\225\260\346\215\256\344\275\215\357\274\232", 0));
        comboBox_data->clear();
        comboBox_data->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "8", 0)
        );
        label_3->setText(QApplication::translate("CheckIspd", "\346\240\241\351\252\214\344\275\215\357\274\232", 0));
        comboBox_check->clear();
        comboBox_check->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "0", 0)
        );
        label_5->setText(QApplication::translate("CheckIspd", "\345\201\234\346\255\242\344\275\215\357\274\232", 0));
        comboBox_stop->clear();
        comboBox_stop->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "1", 0)
        );
        groupBox_6->setTitle(QApplication::translate("CheckIspd", "\345\267\245\345\216\202\346\250\241\345\274\217\351\205\215\347\275\256", 0));
        pushButton_customize->setText(QApplication::translate("CheckIspd", "\345\274\200\345\247\213\351\205\215\347\275\256", 0));
        pushButton_applicate->setText(QApplication::translate("CheckIspd", "\347\273\223\346\235\237\351\205\215\347\275\256", 0));
        pushButton->setText(QApplication::translate("CheckIspd", "\350\275\254\345\210\260\345\275\225\345\205\245ID\347\252\227\345\217\243", 0));
        label_20->setText(QApplication::translate("CheckIspd", "\350\256\276\347\275\256IP", 0));
        pushButton_init->setText(QApplication::translate("CheckIspd", "\345\210\235\345\247\213\345\214\226\347\216\257\345\242\203", 0));
        label_10->setText(QApplication::translate("CheckIspd", "\346\223\215\344\275\234\347\273\223\346\236\234\357\274\232", 0));
        label_status->setText(QString());
        label_timeout->setText(QString());
        groupBox_2->setTitle(QApplication::translate("CheckIspd", "\351\205\215\347\275\256\344\277\241\346\201\257", 0));
        pushButton_readAll->setText(QApplication::translate("CheckIspd", "\344\270\200\351\224\256\350\257\273\345\217\226", 0));
        pushButton_ispd_no->setText(QApplication::translate("CheckIspd", "\346\240\207\347\255\276\345\217\267", 0));
        pushButton_ispd_hz->setText(QApplication::translate("CheckIspd", "\351\207\207\346\240\267\347\216\207", 0));
        pushButton_ispd_version->setText(QApplication::translate("CheckIspd", "\347\211\210\346\234\254\345\217\267", 0));
        groupBox_5->setTitle(QApplication::translate("CheckIspd", "\345\277\203\347\216\207", 0));
        label_11->setText(QApplication::translate("CheckIspd", "\347\254\254\344\270\200\346\254\241\350\216\267\345\217\226\345\200\274", 0));
        label_16->setText(QApplication::translate("CheckIspd", "\347\254\254\344\272\214\346\254\241\350\216\267\345\217\226\345\200\274", 0));
        label_17->setText(QApplication::translate("CheckIspd", "\347\254\254\344\270\211\346\254\241\350\216\267\345\217\226\345\200\274", 0));
        label_18->setText(QApplication::translate("CheckIspd", "\345\271\263\345\235\207\345\200\274", 0));
        pushButton_ispd_hr->setText(QApplication::translate("CheckIspd", "\350\257\273\345\217\226\345\277\203\347\216\207\345\200\274", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CheckIspd", "\346\243\200\346\265\213", 0));
        groupBox_3->setTitle(QApplication::translate("CheckIspd", "\345\257\271\346\257\224\346\225\260\346\215\256", 0));
        label_12->setText(QString());
        label_13->setText(QApplication::translate("CheckIspd", "\344\270\262\345\217\243\347\273\223\346\236\234", 0));
        label_14->setText(QApplication::translate("CheckIspd", "\345\237\272\347\253\231\347\273\223\346\236\234", 0));
        label_15->setText(QApplication::translate("CheckIspd", "\345\257\271\346\257\224\347\273\223\346\236\234", 0));
        pushButton_ispd_sensor->setText(QApplication::translate("CheckIspd", "\350\216\267\345\217\226\344\274\240\346\204\237\345\231\250\345\222\214\347\224\265\351\207\217\345\200\274", 0));
        pushButton_ispd_cmp->setText(QApplication::translate("CheckIspd", "\345\257\271\346\257\224\346\225\260\346\215\256", 0));
        label_6->setText(QApplication::translate("CheckIspd", "\345\212\240\351\200\237\345\272\246", 0));
        label_7->setText(QApplication::translate("CheckIspd", "\351\231\200\350\236\272\344\273\252", 0));
        label_8->setText(QApplication::translate("CheckIspd", "\345\277\203  \347\216\207", 0));
        label_9->setText(QApplication::translate("CheckIspd", "\347\224\265  \351\207\217", 0));
        label_19->setText(QApplication::translate("CheckIspd", "\345\205\205\347\224\265\347\212\266\346\200\201", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CheckIspd", "\345\257\271\346\257\224", 0));
        label_21->setText(QApplication::translate("CheckIspd", "ID\357\274\232", 0));
        label_24->setText(QApplication::translate("CheckIspd", "\344\272\247\345\223\201\345\236\213\345\217\267", 0));
        comboBox_type->clear();
        comboBox_type->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "D1", 0)
        );
        comboBox_type->setCurrentText(QApplication::translate("CheckIspd", "D1", 0));
        label_22->setText(QApplication::translate("CheckIspd", "\351\242\234\350\211\262", 0));
        comboBox_color->clear();
        comboBox_color->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "\347\231\275\347\272\242", 0)
        );
        comboBox_color->setCurrentText(QApplication::translate("CheckIspd", "\347\231\275\347\272\242", 0));
        label_23->setText(QApplication::translate("CheckIspd", "\345\244\247\345\260\217", 0));
        comboBox_size->clear();
        comboBox_size->insertItems(0, QStringList()
         << QApplication::translate("CheckIspd", "\344\270\255", 0)
        );
        pushButton_record->setText(QApplication::translate("CheckIspd", "\345\275\225\345\205\245", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("CheckIspd", "\345\275\225\345\205\245ID", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckIspd: public Ui_CheckIspd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKISPD_H
