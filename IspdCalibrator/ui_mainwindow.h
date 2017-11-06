/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QAction *quit;
    QAction *about;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_mr_status_info;
    QSplitter *splitter_2;
    QTreeView *treeView;
    QSplitter *splitter;
    QTableView *tableView_udp_ispd;
    QTableView *tableView_udp_mrpb;
    QPushButton *pushButton_mr_ar_interval;
    QPushButton *pushButton_mr_ar_status;
    QMenuBar *menuBar;
    QMenu *File;
    QMenu *Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(652, 617);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/image/cjqc_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        open = new QAction(MainWindow);
        open->setObjectName(QStringLiteral("open"));
        quit = new QAction(MainWindow);
        quit->setObjectName(QStringLiteral("quit"));
        about = new QAction(MainWindow);
        about->setObjectName(QStringLiteral("about"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_mr_status_info = new QPushButton(centralWidget);
        pushButton_mr_status_info->setObjectName(QStringLiteral("pushButton_mr_status_info"));

        verticalLayout->addWidget(pushButton_mr_status_info);

        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy2);
        splitter_2->setOrientation(Qt::Horizontal);
        treeView = new QTreeView(splitter_2);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setMinimumSize(QSize(20, 20));
        treeView->setBaseSize(QSize(20, 20));
        treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        splitter_2->addWidget(treeView);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableView_udp_ispd = new QTableView(splitter);
        tableView_udp_ispd->setObjectName(QStringLiteral("tableView_udp_ispd"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableView_udp_ispd->sizePolicy().hasHeightForWidth());
        tableView_udp_ispd->setSizePolicy(sizePolicy3);
        tableView_udp_ispd->setAutoFillBackground(true);
        splitter->addWidget(tableView_udp_ispd);
        tableView_udp_mrpb = new QTableView(splitter);
        tableView_udp_mrpb->setObjectName(QStringLiteral("tableView_udp_mrpb"));
        tableView_udp_mrpb->setAutoFillBackground(true);
        splitter->addWidget(tableView_udp_mrpb);
        splitter_2->addWidget(splitter);

        verticalLayout->addWidget(splitter_2);

        pushButton_mr_ar_interval = new QPushButton(centralWidget);
        pushButton_mr_ar_interval->setObjectName(QStringLiteral("pushButton_mr_ar_interval"));

        verticalLayout->addWidget(pushButton_mr_ar_interval);

        pushButton_mr_ar_status = new QPushButton(centralWidget);
        pushButton_mr_ar_status->setObjectName(QStringLiteral("pushButton_mr_ar_status"));

        verticalLayout->addWidget(pushButton_mr_ar_status);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 652, 22));
        File = new QMenu(menuBar);
        File->setObjectName(QStringLiteral("File"));
        Help = new QMenu(menuBar);
        Help->setObjectName(QStringLiteral("Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(File->menuAction());
        menuBar->addAction(Help->menuAction());
        File->addAction(open);
        File->addAction(quit);
        Help->addAction(about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\243\200\346\265\213\346\240\207\347\255\276", Q_NULLPTR));
        open->setText(QApplication::translate("MainWindow", "open", Q_NULLPTR));
        quit->setText(QApplication::translate("MainWindow", "quit", Q_NULLPTR));
        about->setText(QApplication::translate("MainWindow", "about", Q_NULLPTR));
        pushButton_mr_status_info->setText(QApplication::translate("MainWindow", "\345\237\272\347\253\231\347\212\266\346\200\201\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_mr_ar_interval->setText(QApplication::translate("MainWindow", "\345\237\272\347\253\231\344\270\273\345\212\250\344\270\212\346\212\245\346\227\266\351\227\264\351\227\264\351\232\224", Q_NULLPTR));
        pushButton_mr_ar_status->setText(QApplication::translate("MainWindow", "\345\237\272\347\253\231\346\230\257\345\220\246\344\270\273\345\212\250\344\270\212\346\212\245\347\212\266\346\200\201", Q_NULLPTR));
        File->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        Help->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
