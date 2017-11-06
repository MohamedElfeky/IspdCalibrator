/********************************************************************************
** Form generated from reading UI file 'generateid.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEID_H
#define UI_GENERATEID_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateID
{
public:
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_test_ispd;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_sp;
    QComboBox *comboBox_sp;
    QPushButton *pushButton_open_sp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_baud;
    QComboBox *comboBox_baud;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_check;
    QComboBox *comboBox_check;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_data;
    QComboBox *comboBox_data;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_stop;
    QComboBox *comboBox_stop;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_customize;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_applicate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_status;
    QTabWidget *tabWidget;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_ispd_id;
    QPushButton *pushButton_record;
    QLabel *label_4;
    QComboBox *comboBox_type;
    QLabel *label_5;
    QComboBox *comboBox_color;
    QLabel *label_6;
    QComboBox *comboBox_size;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_hz;
    QPushButton *pushButton_confirm_hz;

    void setupUi(QDialog *GenerateID)
    {
        if (GenerateID->objectName().isEmpty())
            GenerateID->setObjectName(QStringLiteral("GenerateID"));
        GenerateID->resize(763, 738);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(80);
        sizePolicy.setVerticalStretch(20);
        sizePolicy.setHeightForWidth(GenerateID->sizePolicy().hasHeightForWidth());
        GenerateID->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/image/cjqc_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        GenerateID->setWindowIcon(icon);
        gridLayout_6 = new QGridLayout(GenerateID);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        pushButton_test_ispd = new QPushButton(GenerateID);
        pushButton_test_ispd->setObjectName(QStringLiteral("pushButton_test_ispd"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_test_ispd->sizePolicy().hasHeightForWidth());
        pushButton_test_ispd->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(22);
        pushButton_test_ispd->setFont(font);
        pushButton_test_ispd->setFocusPolicy(Qt::NoFocus);

        gridLayout_6->addWidget(pushButton_test_ispd, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(GenerateID);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_2->setFont(font1);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_sp = new QLabel(groupBox_2);
        label_sp->setObjectName(QStringLiteral("label_sp"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_sp->sizePolicy().hasHeightForWidth());
        label_sp->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(20);
        label_sp->setFont(font2);

        horizontalLayout_4->addWidget(label_sp);

        comboBox_sp = new QComboBox(groupBox_2);
        comboBox_sp->setObjectName(QStringLiteral("comboBox_sp"));
        sizePolicy3.setHeightForWidth(comboBox_sp->sizePolicy().hasHeightForWidth());
        comboBox_sp->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(comboBox_sp);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        pushButton_open_sp = new QPushButton(groupBox_2);
        pushButton_open_sp->setObjectName(QStringLiteral("pushButton_open_sp"));
        sizePolicy3.setHeightForWidth(pushButton_open_sp->sizePolicy().hasHeightForWidth());
        pushButton_open_sp->setSizePolicy(sizePolicy3);
        pushButton_open_sp->setFont(font2);
        pushButton_open_sp->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_open_sp, 0, 1, 5, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_baud = new QLabel(groupBox_2);
        label_baud->setObjectName(QStringLiteral("label_baud"));
        sizePolicy3.setHeightForWidth(label_baud->sizePolicy().hasHeightForWidth());
        label_baud->setSizePolicy(sizePolicy3);
        label_baud->setFont(font2);

        horizontalLayout_5->addWidget(label_baud);

        comboBox_baud = new QComboBox(groupBox_2);
        comboBox_baud->setObjectName(QStringLiteral("comboBox_baud"));
        sizePolicy3.setHeightForWidth(comboBox_baud->sizePolicy().hasHeightForWidth());
        comboBox_baud->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(comboBox_baud);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_check = new QLabel(groupBox_2);
        label_check->setObjectName(QStringLiteral("label_check"));
        sizePolicy3.setHeightForWidth(label_check->sizePolicy().hasHeightForWidth());
        label_check->setSizePolicy(sizePolicy3);
        label_check->setFont(font2);

        horizontalLayout_6->addWidget(label_check);

        comboBox_check = new QComboBox(groupBox_2);
        comboBox_check->setObjectName(QStringLiteral("comboBox_check"));
        sizePolicy3.setHeightForWidth(comboBox_check->sizePolicy().hasHeightForWidth());
        comboBox_check->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(comboBox_check);


        gridLayout->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_data = new QLabel(groupBox_2);
        label_data->setObjectName(QStringLiteral("label_data"));
        label_data->setFont(font2);

        horizontalLayout_7->addWidget(label_data);

        comboBox_data = new QComboBox(groupBox_2);
        comboBox_data->setObjectName(QStringLiteral("comboBox_data"));
        sizePolicy3.setHeightForWidth(comboBox_data->sizePolicy().hasHeightForWidth());
        comboBox_data->setSizePolicy(sizePolicy3);
        comboBox_data->setEditable(false);
        comboBox_data->setInsertPolicy(QComboBox::InsertAtBottom);

        horizontalLayout_7->addWidget(comboBox_data);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_stop = new QLabel(groupBox_2);
        label_stop->setObjectName(QStringLiteral("label_stop"));
        label_stop->setFont(font2);

        horizontalLayout_8->addWidget(label_stop);

        comboBox_stop = new QComboBox(groupBox_2);
        comboBox_stop->setObjectName(QStringLiteral("comboBox_stop"));
        sizePolicy3.setHeightForWidth(comboBox_stop->sizePolicy().hasHeightForWidth());
        comboBox_stop->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(comboBox_stop);


        gridLayout->addLayout(horizontalLayout_8, 4, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(GenerateID);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font1);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButton_customize = new QPushButton(groupBox_4);
        pushButton_customize->setObjectName(QStringLiteral("pushButton_customize"));
        sizePolicy1.setHeightForWidth(pushButton_customize->sizePolicy().hasHeightForWidth());
        pushButton_customize->setSizePolicy(sizePolicy1);
        pushButton_customize->setFont(font2);

        gridLayout_4->addWidget(pushButton_customize, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(55, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButton_applicate = new QPushButton(groupBox_4);
        pushButton_applicate->setObjectName(QStringLiteral("pushButton_applicate"));
        sizePolicy1.setHeightForWidth(pushButton_applicate->sizePolicy().hasHeightForWidth());
        pushButton_applicate->setSizePolicy(sizePolicy1);
        pushButton_applicate->setFont(font2);
        pushButton_applicate->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(pushButton_applicate, 0, 2, 1, 1);


        gridLayout_6->addWidget(groupBox_4, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(GenerateID);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setFont(font1);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_status = new QLabel(GenerateID);
        label_status->setObjectName(QStringLiteral("label_status"));
        sizePolicy1.setHeightForWidth(label_status->sizePolicy().hasHeightForWidth());
        label_status->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(20);
        font3.setItalic(true);
        label_status->setFont(font3);

        horizontalLayout_3->addWidget(label_status);


        gridLayout_6->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        tabWidget = new QTabWidget(GenerateID);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setSizeIncrement(QSize(0, 1));
        tabWidget->setFont(font1);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font2);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_ispd_id = new QLineEdit(groupBox);
        lineEdit_ispd_id->setObjectName(QStringLiteral("lineEdit_ispd_id"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_ispd_id->sizePolicy().hasHeightForWidth());
        lineEdit_ispd_id->setSizePolicy(sizePolicy4);
        lineEdit_ispd_id->setReadOnly(false);

        gridLayout_3->addWidget(lineEdit_ispd_id, 0, 1, 1, 1);

        pushButton_record = new QPushButton(groupBox);
        pushButton_record->setObjectName(QStringLiteral("pushButton_record"));
        sizePolicy4.setHeightForWidth(pushButton_record->sizePolicy().hasHeightForWidth());
        pushButton_record->setSizePolicy(sizePolicy4);
        pushButton_record->setFont(font2);
        pushButton_record->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(pushButton_record, 0, 2, 4, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        comboBox_type = new QComboBox(groupBox);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));
        sizePolicy3.setHeightForWidth(comboBox_type->sizePolicy().hasHeightForWidth());
        comboBox_type->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(comboBox_type, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        comboBox_color = new QComboBox(groupBox);
        comboBox_color->setObjectName(QStringLiteral("comboBox_color"));
        sizePolicy3.setHeightForWidth(comboBox_color->sizePolicy().hasHeightForWidth());
        comboBox_color->setSizePolicy(sizePolicy3);
        comboBox_color->setEditable(false);

        gridLayout_3->addWidget(comboBox_color, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);

        comboBox_size = new QComboBox(groupBox);
        comboBox_size->setObjectName(QStringLiteral("comboBox_size"));
        sizePolicy3.setHeightForWidth(comboBox_size->sizePolicy().hasHeightForWidth());
        comboBox_size->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(comboBox_size, 3, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        tabWidget->addTab(widget, icon, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font1);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 2);

        comboBox_hz = new QComboBox(groupBox_3);
        comboBox_hz->setObjectName(QStringLiteral("comboBox_hz"));
        sizePolicy3.setHeightForWidth(comboBox_hz->sizePolicy().hasHeightForWidth());
        comboBox_hz->setSizePolicy(sizePolicy3);
        comboBox_hz->setFont(font2);

        gridLayout_2->addWidget(comboBox_hz, 0, 2, 1, 1);

        pushButton_confirm_hz = new QPushButton(groupBox_3);
        pushButton_confirm_hz->setObjectName(QStringLiteral("pushButton_confirm_hz"));
        sizePolicy3.setHeightForWidth(pushButton_confirm_hz->sizePolicy().hasHeightForWidth());
        pushButton_confirm_hz->setSizePolicy(sizePolicy3);
        pushButton_confirm_hz->setFont(font2);

        gridLayout_2->addWidget(pushButton_confirm_hz, 1, 0, 1, 3);


        verticalLayout_4->addWidget(groupBox_3);

        tabWidget->addTab(tab_2, QString());

        gridLayout_6->addWidget(tabWidget, 3, 0, 1, 2);

#ifndef QT_NO_SHORTCUT
        label_sp->setBuddy(comboBox_sp);
        label_baud->setBuddy(comboBox_sp);
        label_check->setBuddy(comboBox_sp);
        label_data->setBuddy(comboBox_sp);
        label_stop->setBuddy(comboBox_sp);
        label_3->setBuddy(lineEdit_ispd_id);
        label_4->setBuddy(comboBox_type);
        label_5->setBuddy(comboBox_color);
        label_6->setBuddy(comboBox_size);
        label_2->setBuddy(comboBox_hz);
#endif // QT_NO_SHORTCUT

        retranslateUi(GenerateID);

        tabWidget->setCurrentIndex(1);
        comboBox_color->setCurrentIndex(1);
        comboBox_hz->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(GenerateID);
    } // setupUi

    void retranslateUi(QDialog *GenerateID)
    {
        GenerateID->setWindowTitle(QApplication::translate("GenerateID", "\345\275\225\345\205\245ID", Q_NULLPTR));
        pushButton_test_ispd->setText(QApplication::translate("GenerateID", "\350\275\254\345\210\260\346\243\200\346\265\213\347\252\227\345\217\243", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("GenerateID", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        label_sp->setText(QApplication::translate("GenerateID", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        pushButton_open_sp->setText(QApplication::translate("GenerateID", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        label_baud->setText(QApplication::translate("GenerateID", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        comboBox_baud->clear();
        comboBox_baud->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "230400", Q_NULLPTR)
        );
        label_check->setText(QApplication::translate("GenerateID", "\346\240\241\351\252\214\344\275\215\357\274\232", Q_NULLPTR));
        comboBox_check->clear();
        comboBox_check->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "0", Q_NULLPTR)
        );
        label_data->setText(QApplication::translate("GenerateID", "\346\225\260\346\215\256\344\275\215\357\274\232", Q_NULLPTR));
        comboBox_data->clear();
        comboBox_data->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "8", Q_NULLPTR)
        );
        label_stop->setText(QApplication::translate("GenerateID", "\345\201\234\346\255\242\344\275\215\357\274\232", Q_NULLPTR));
        comboBox_stop->clear();
        comboBox_stop->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "1", Q_NULLPTR)
        );
        groupBox_4->setTitle(QApplication::translate("GenerateID", "\351\205\215\347\275\256\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_customize->setText(QApplication::translate("GenerateID", "\345\274\200\345\247\213\351\205\215\347\275\256", Q_NULLPTR));
        pushButton_applicate->setText(QApplication::translate("GenerateID", "\347\273\223\346\235\237\351\205\215\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("GenerateID", "\346\223\215\344\275\234\347\273\223\346\236\234\357\274\232", Q_NULLPTR));
        label_status->setText(QString());
        groupBox->setTitle(QApplication::translate("GenerateID", "\345\275\225\345\205\245ID", Q_NULLPTR));
        label_3->setText(QApplication::translate("GenerateID", "ID", Q_NULLPTR));
        pushButton_record->setText(QApplication::translate("GenerateID", "\345\275\225\345\205\245", Q_NULLPTR));
        label_4->setText(QApplication::translate("GenerateID", "\344\272\247\345\223\201\345\236\213\345\217\267", Q_NULLPTR));
        comboBox_type->clear();
        comboBox_type->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "D1", Q_NULLPTR)
         << QApplication::translate("GenerateID", "D2", Q_NULLPTR)
         << QApplication::translate("GenerateID", "D3", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("GenerateID", "\351\242\234\350\211\262", Q_NULLPTR));
        comboBox_color->clear();
        comboBox_color->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "\351\273\221\347\272\242", Q_NULLPTR)
         << QApplication::translate("GenerateID", "\347\231\275\347\272\242", Q_NULLPTR)
        );
        comboBox_color->setCurrentText(QApplication::translate("GenerateID", "\347\231\275\347\272\242", Q_NULLPTR));
        label_6->setText(QApplication::translate("GenerateID", "\345\244\247\345\260\217", Q_NULLPTR));
        comboBox_size->clear();
        comboBox_size->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "\345\244\247", Q_NULLPTR)
         << QApplication::translate("GenerateID", "\344\270\255", Q_NULLPTR)
         << QApplication::translate("GenerateID", "\345\260\217", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("GenerateID", "\345\270\270\347\224\250", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("GenerateID", "\350\256\276\347\275\256\351\207\207\346\240\267\347\216\207", Q_NULLPTR));
        label_2->setText(QApplication::translate("GenerateID", "\350\257\267\351\200\211\346\213\251\351\207\207\346\240\267\347\216\207\357\274\232", Q_NULLPTR));
        comboBox_hz->clear();
        comboBox_hz->insertItems(0, QStringList()
         << QApplication::translate("GenerateID", "1", Q_NULLPTR)
         << QApplication::translate("GenerateID", "2", Q_NULLPTR)
         << QApplication::translate("GenerateID", "3", Q_NULLPTR)
         << QApplication::translate("GenerateID", "4", Q_NULLPTR)
         << QApplication::translate("GenerateID", "5", Q_NULLPTR)
         << QApplication::translate("GenerateID", "6", Q_NULLPTR)
         << QApplication::translate("GenerateID", "8", Q_NULLPTR)
         << QApplication::translate("GenerateID", "12", Q_NULLPTR)
        );
        comboBox_hz->setCurrentText(QApplication::translate("GenerateID", "3", Q_NULLPTR));
        pushButton_confirm_hz->setText(QApplication::translate("GenerateID", "\347\241\256\350\256\244", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("GenerateID", "\351\253\230\347\272\247", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GenerateID: public Ui_GenerateID {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEID_H
