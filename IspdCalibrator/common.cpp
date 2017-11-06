#include "common.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QApplication>
#include <QtEndian>
#include <QMap>
#include <cmath>
#include <assert.h>

namespace util {

data_base::data_base()
    : m_db_path("../database/IspdCalibrator.db")
    , m_db(QSqlDatabase::contains()
            ? QSqlDatabase::database("qt_sql_default_connection")
            : QSqlDatabase::addDatabase("QSQLITE"))
{ }

data_base::data_base(const QString &db_path)
    : m_db_path(db_path)
    , m_db(QSqlDatabase::contains()
            ? QSqlDatabase::database("qt_sql_default_connection")
            : QSqlDatabase::addDatabase("QSQLITE"))
{ }

data_base::~data_base() {
    if (m_db.isOpen())
        m_db.close();
}

bool data_base::init(QString & err) {
    m_db.setDatabaseName(m_db_path);
    if (!m_db.open()) {
        QMessageBox::critical(0, qApp->tr("数据库打开失败"),
                              qApp->tr("请检查数据库文件存放位置，"),
                              QMessageBox::Abort);
        err = m_db.lastError().text();
        qCritical() << err;
        return false;
    } else return true;
}

bool data_base::query(const QString & sql, QVariant & res, QString & err)
{
    QSqlQuery query;
    if (!query.exec(sql)) {
        err = query.lastError().text();
        return false;
    }
    while (query.next()) {
        res = query.value(0).toString();
    }
    return true;
}

bool data_base::update(const QString &sql, QString &err)
{
    QSqlQuery query;
    if (!query.prepare(sql)) {
        err = query.lastError().text();
        return false;
    }

    if (!query.exec()) {
        err = query.lastError().text();
        return false;
    }

    return true;
}

void data_base::set_db_path(const QString &path)
{
    m_db_path = path;
}




} // namespace util

namespace serialPort {

ReqPkg::ReqPkg(REQ_TYPE type) : m_type(type)
{

    m_header = 0xF0F0;
    m_tailer = 0xFEFE;
    setLength();
    setCrc();
}

QByteArray ReqPkg::toBinary() {
    QByteArray res;
    QDataStream data(&res, QIODevice::WriteOnly);

    data << m_header << m_type << m_length << m_crc << m_tailer;

    return res;
}

void ReqPkg::setCrc()
{
    m_crc = (m_header >> 8) + m_header
            + m_type + m_length;
}

void ReqPkg::setLength()
{
    m_length = 0x00;
}

//
IspdID::IspdID(quint32 id, REQ_TYPE type)
    : m_id(id)
    , m_type(type)
{ }

QByteArray IspdID::toBinary()
{
    QByteArray res;
    QDataStream data(&res, QIODevice::WriteOnly);

    data << qFromBigEndian(m_id);

    return res;
}

quint32 IspdID::getID() const
{
    return m_id;
}

REQ_TYPE IspdID::getType() const
{
    return m_type;
}

quint8 IspdID::getLength() const
{
    return sizeof(m_id);
}

quint8 IspdID::getCrc() const
{
    return static_cast<quint8>(m_id)
            + static_cast<quint8>(m_id >> 8)
            + static_cast<quint8>(m_id >> 16)
            + static_cast<quint8>(m_id >> 24);
}

IspdID::IspdID(const IspdID &ispdID)
{
    m_id = ispdID.getID();
    m_type = ispdID.getType();
}

IspdID &IspdID::operator=(const IspdID &ispdID)
{
    m_id = ispdID.getID();
    m_type = ispdID.getType();
    return *this;
}

//
IspdHZ::IspdHZ(quint8 hz, REQ_TYPE type)
    : m_hz(hz)
    , m_type(type)
{

}

QByteArray IspdHZ::toBinary()
{
    QByteArray res;
    QDataStream data(&res, QIODevice::WriteOnly);

    data << qFromBigEndian(m_hz);

    return res;
}

IspdHZ::IspdHZ(const IspdHZ &ispdHZ)
{
    m_hz = ispdHZ.getHZ();
    m_type = ispdHZ.getType();
}

IspdHZ &IspdHZ::operator=(const IspdHZ &ispdHZ)
{
    m_hz = ispdHZ.getHZ();
    m_type = ispdHZ.getType();
    return *this;
}

} // namespace serialPort

namespace encrypt
{
/*
    const std::map<qint32, QString> tenTo34 =
    {
        {0, "0"},
        {1, "1"},
        {2, "2"},
        {3, "3"},
        {4, "4"},
        {5, "5"},
        {6, "6"},
        {7, "7"},
        {8, "8"},
        {9, "9"},
        {10, "A"},
        {11, "B"},
        {12, "C"},
        {13, "E"},
        {14, "D"},
        {15, "F"},
        {16, "G"},
        {17, "J"},
        {18, "H"},
        {19, "K"},
        {20, "L"},
        {21, "N"},
        {22, "M"},
        {23, "P"},
        {24, "Q"},
        {25, "R"},
        {26, "T"},
        {27, "S"},
        {28, "U"},
        {29, "V"},
        {30, "W"},
        {31, "Y"},
        {32, "X"},
        {33, "Z"},
    };
    */
    //add by guosj
    const static unsigned int g_ispd_id_map_table[34] =
    {
        'Q', '9', 'Y', 'V', '2', 'F', 'N', 'Z', '5', 'U',
        'A', '6', '8', 'B', '4', 'J', '1', 'D', 'C', 'K',
        'M', 'L', 'P', '3', 'S', 'T', 'W', 'H', 'G', 'E',
        'X', '0', 'R', '7',
    };

    /*
    QVector<qint8> encode(qint32 x)
    {
       QVector<qint8> vec;
       while (x > 127)
       {
            vec.push_back(0x80 | static_cast<qint8>(x & 0x7F));
            x >>= 7;
       }
       vec.push_back(static_cast<qint8>(x));
       return vec;
    }

    QString decimalToAny(quint32 num, quint32 n)
    {
        QString new_sum_str = "";
        quint32 remainder;
        QString remainder_str;
        while (num != 0)
        {
            remainder = num % n;
            if (remainder < 34 && remainder > 9)
            {
                remainder_str = tenTo34.at(remainder);
            }
            else
            {
                remainder_str = QString::number(remainder);
            }
            new_sum_str += remainder_str;
            num = num / n;
        }
        return new_sum_str;
    }

    static quint32 findKey(const QString & value)
    {
        quint32 result = -1;
        for (auto elem : tenTo34)
        {
            if (elem.second == value)
            {
                result = elem.first;
            }
        }
        return result;
    }

    quint32 anyToDecimal(const QString & num, quint32 n)
    {
        double new_num = 0.0;
        quint32 nNum = num.length() - 1;
        for (auto elem = num.begin(); elem != num.end(); elem++)
        {
            quint32 tmp = double(findKey(*elem));
            if (tmp != -1)
            {
                new_num = new_num + tmp*std::pow(double(n), double(nNum));
                nNum -= 1;
            }
            else
            {
                break;
            }
        }
        return static_cast<quint32>(new_num);
    }
    */

    //add by guosj
    QString encrypt_ispd_id(unsigned int id)
    {
        QString q_str;
        std::string str;
        do
        {
            unsigned int mod = id % 34;
            str += g_ispd_id_map_table[mod];
            id = id / 34;
        }
        while(0 != id);
        std::reverse(str.begin(), str.end());
        q_str = QString::fromStdString(str);
        return q_str;
    }

    //add by guosj
    unsigned int dencrypt_ispd_id(const std::string& id)
    {
        unsigned int rtn = 0;
        size_t size = id.size();
        assert(0 != size);

        for (size_t i = size; i > 0; --i)
        {
            unsigned int j = 0;
            for(; j < 34; j++)
            {
                if (id[i-1] == g_ispd_id_map_table[j])
                break;
            }
            assert(34 != j);
            rtn += j * pow((double)34, (double)size-i);
        }
        return rtn;
    }
}
