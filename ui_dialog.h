/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *spinBox_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(472, 622);
        verticalLayout_4 = new QVBoxLayout(Dialog);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QFont font1;
        font1.setPointSize(10);
        spinBox->setFont(font1);
        spinBox->setMinimum(1);
        spinBox->setMaximum(30);
        spinBox->setValue(5);

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_7->addWidget(label_5);

        spinBox_3 = new QSpinBox(groupBox_2);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setFont(font1);
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(30);
        spinBox_3->setValue(5);

        horizontalLayout_7->addWidget(spinBox_3);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        horizontalLayout_8->addWidget(label_6);

        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        horizontalLayout_8->addWidget(comboBox_3);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_9->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_9->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_9->addWidget(pushButton_6);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_4->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(false);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(spinBox);
        label_2->setBuddy(comboBox);
        label_5->setBuddy(spinBox);
        label_6->setBuddy(comboBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QString());
        groupBox->setTitle(QApplication::translate("Dialog", "\345\237\272\347\253\231\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256\350\207\252\345\212\250\344\270\212\346\212\245\346\227\266\351\227\264", Q_NULLPTR));
        spinBox->setSuffix(QApplication::translate("Dialog", "\347\247\222", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "\346\230\257\345\220\246\344\270\273\345\212\250\344\270\212\346\212\245\347\212\266\346\200\201", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\345\274\200\345\220\257", Q_NULLPTR)
         << QApplication::translate("Dialog", "\345\205\263\351\227\255", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("Dialog", "\351\207\215\345\220\257", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Dialog", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\347\224\265\346\272\220\346\216\247\345\210\266\346\235\277\350\256\276\347\275\256", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256\350\207\252\345\212\250\344\270\212\346\212\245\346\227\266\351\227\264", Q_NULLPTR));
        spinBox_3->setSuffix(QApplication::translate("Dialog", "\347\247\222", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog", "\346\230\257\345\220\246\344\270\273\345\212\250\344\270\212\346\212\245\347\212\266\346\200\201", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\345\274\200\345\220\257", Q_NULLPTR)
         << QApplication::translate("Dialog", "\345\205\263\351\227\255", Q_NULLPTR)
        );
        pushButton_3->setText(QApplication::translate("Dialog", "\345\205\263\351\227\255", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Dialog", "\351\207\215\345\220\257", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("Dialog", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
