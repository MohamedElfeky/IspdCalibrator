#include "login.h"
#include "selectview.h"
#include "checkispd.h"
#include "generateid.h"
#include <QApplication>

#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QMessageLogContext>
#include <QMutex>
#include <QMutexLocker>
#include <QTextCodec>

QFile* global_log_file = NULL;

static void logMessageHandler(QtMsgType type, const QMessageLogContext & msgContext, const QString & msg)
{
    QString txt;
    QDateTime date;
    txt.append(date.currentDateTime().toString()).append("[");
    switch (type)
    {
        case QtDebugMsg:
            txt.append("DEBUG").append("]");
            break;
        case QtInfoMsg:
            txt.append("INFO").append("]");
            break;
        case QtWarningMsg:
            txt.append("WARNING").append("]");
            break;
        case QtCriticalMsg:
            txt.append("CRITICAL").append("]");
            break;
        case QtFatalMsg:
            txt.append("FATAL").append("]");
            abort();
    }
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    QTextStream Output(global_log_file);
    txt += msg;
    Output << txt << endl;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QString logFileName = QDir::currentPath();
    int mid = logFileName.lastIndexOf("/");
    logFileName = logFileName.left(mid);
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("yyyy-MM-dd_hh_mm_ss");
    logFileName.append("/log/");
    logFileName.append(time_str);
    logFileName.append(QString(".log"));
    global_log_file = new QFile(logFileName);
    if (!global_log_file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
         delete global_log_file;
         global_log_file = NULL;
    }
    //qInstallMessageHandler(logMessageHandler);
    login l;
    GenerateID genID;
    SelectView sv;
    QObject::connect(&l, SIGNAL(tellUsername(QString)), &genID, SLOT(onUsername(QString)));
    if (l.exec() == QDialog::Accepted)
    {
        CheckIspd checkISPD;

        QObject::connect(&sv, SIGNAL(test_ispd()), &checkISPD, SLOT(start()));
        QObject::connect(&checkISPD, SIGNAL(quit()), &sv, SLOT(close()));

        QObject::connect(&sv, SIGNAL(record_id()), &genID, SLOT(start()));
        QObject::connect(&genID, SIGNAL(quit()), &sv, SLOT(close()));

        QObject::connect(&genID, SIGNAL(goto_checkISPD()), &checkISPD, SLOT(start()));
        QObject::connect(&genID, SIGNAL(quit()), &checkISPD, SLOT(close()));

        QObject::connect(&checkISPD, SIGNAL(goto_genID()), &genID, SLOT(start()));
        QObject::connect(&checkISPD, SIGNAL(quit()), &genID, SLOT(close()));

        QObject::connect(&sv, SIGNAL(quit()), &checkISPD, SLOT(close()));
        QObject::connect(&sv, SIGNAL(quit()), &l, SLOT(close()));

        checkISPD.hide();
        genID.hide();
        sv.show();
        return a.exec();
    }
}
