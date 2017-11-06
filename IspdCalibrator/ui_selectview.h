/********************************************************************************
** Form generated from reading UI file 'selectview.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTVIEW_H
#define UI_SELECTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectView
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *SelectView)
    {
        if (SelectView->objectName().isEmpty())
            SelectView->setObjectName(QStringLiteral("SelectView"));
        SelectView->resize(354, 406);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/image/cjqc_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        SelectView->setWindowIcon(icon);
        layoutWidget = new QWidget(SelectView);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 60, 291, 281));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        textBrowser->setFont(font);

        verticalLayout->addWidget(textBrowser);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font);
        pushButton_2->setIcon(icon);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, textBrowser);

        retranslateUi(SelectView);

        QMetaObject::connectSlotsByName(SelectView);
    } // setupUi

    void retranslateUi(QDialog *SelectView)
    {
        SelectView->setWindowTitle(QApplication::translate("SelectView", "\351\200\211\346\213\251", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("SelectView", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Cantarell'; font-size:24pt; font-weight:400;\">\347\231\273\351\231\206\346\210\220\345\212\237\357\274\201\357\274\201\357\274\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Cantarell'; font-size:24pt; font-weight:400;\">\350\257\267\351\200\211\346\213\251</span><span style=\" font-family:'Cantarell'; font-size:24pt; font-weight:400; font-style:italic; text-decoration: underline;\">\345\275\225\345\205\245ID</span><"
                        "span style=\" font-family:'Cantarell'; font-size:24pt; font-weight:400;\">\346\210\226\350\200\205</span><span style=\" font-family:'Cantarell'; font-size:24pt; font-weight:400; font-style:italic; text-decoration: underline;\">\346\243\200\346\265\213\346\240\207\347\255\276</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SelectView", "\345\275\225\345\205\245ID", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SelectView", "\346\243\200\346\265\213\346\240\207\347\255\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SelectView: public Ui_SelectView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTVIEW_H
