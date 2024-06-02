#include "Mydatabase.h"

#include <QDebug>
#include <QSqlQuery>

MyDatabase::MyDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("AffairDB.db"); // 相对路径是相对于.exe所在的文件夹下（即bin文件夹下）
    if(!m_db.open())
    {
        qDebug() << "Failed to Open database";
        return;
    }
    QSqlQuery query;

    QString sql = QString
       ("CREATE TABLE IF NOT EXISTS schedule ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT ,"

        "startTime TEXT ,"
        "endTime TEXT ,"
        "content TEXT NOT NULL,"
        "urgency TEXT ,"
        "category TEXT );");
    if(!query.exec(sql))
    {
        qDebug() << "Failed to create table";
        qDebug() << query.lastQuery();
        return;
    }
    m_db.close();
}

MyDatabase::~MyDatabase()
{

}

bool MyDatabase::selectAffair(QList<Affair> &scheduleList)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to Open Database : select";
        return false;
    }
    QSqlQuery query;
    QString sql = "Select * from schedule;";
    if(!query.exec(sql))
    {
        qDebug() << "Failed to selcet schedule;";
        return false;
    }
    while(query.next())
    {
        Affair aff;
        int id = query.value("id").toInt();
        QString startTime = query.value("startTime").toString();
        QString endTime = query.value("endTime").toString();
        QString content = query.value("content").toString();
        QString urgency = query.value("urgency") .toString();
        QString category = query.value("category").toString();

        aff.setData(id,startTime,endTime,content,urgency,category);
        scheduleList.append(aff);
    }
    m_db.close();
    return true;
}

bool MyDatabase::addAffair(Affair &schedule)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to Open Database : add";
        return false;
    }
    QSqlQuery query;
    query.prepare("insert into schedule (id,startTime,endTime,content,urgency,category)"
                  "values(NULL,:startTime,:endTime,:content,:urgency,:category)");

    query.bindValue(":content",schedule.content());
    query.bindValue(":startTime",schedule.startTime());
    query.bindValue(":endTime",schedule.endTime());

    query.bindValue(":urgency",schedule.urgency());
    query.bindValue(":category",schedule.category());
    if(!query.exec())
    {
        qDebug() << query.lastQuery();
        m_db.close();
        return false;
    }
    m_db.close();
    return true;
}

bool MyDatabase::updateAffair(Affair &schedule)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to Open Database : update";
        return false;
    }
    QSqlQuery query;
    query.prepare("update schedule set startTime=:startTime,endTime=:endTime,content=:content,urgency=:urgency,category=:category where id=:id");
    query.bindValue(":id",schedule.id());
    query.bindValue(":startTime",schedule.startTime());
    query.bindValue(":endTime",schedule.endTime());
    query.bindValue(":content",schedule.content());
    query.bindValue(":urgency",schedule.urgency());
    query.bindValue(":category",schedule.category());

    m_db.close();
    return true;
}

bool MyDatabase::deleteAffair(int id)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to Open Database : delete";
        return false;
    }
    QSqlQuery query;
    QString sql = QString("delete from schedule where id = %1").arg(id);
    if(!query.exec(sql))
    {
        qDebug() << "Failed to delete !!!";
        m_db.close();
        return false;
    }

    m_db.close();
    return true;
}

