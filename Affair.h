#ifndef AFFAIR_H
#define AFFAIR_H

#include <QMainWindow>
#include <QString>
#include <QDate>



class Affair
{

public:

    Affair();

    bool setData(int id,QString startTime,QString endTime,QString content,QString urgency,QString category);




    QString startTime() const;
    void setStartTime(const QString &newStartTime);

    QString endTime() const;
    void setEndTime(const QString &newEndTime);

    QString content() const;
    void setContent(const QString &newContent);

    QString urgency() const;
    void setUrgency(const QString &newUrgency);

    QString category() const;
    void setCategory(const QString &newCategory);

    int id() const;
    void setId(int newId);

private:


    int m_id;
    QString m_startTime;
    QString m_endTime;
    QString m_content;
    QString m_urgency;
    QString m_category;
};

#endif // AFFAIR_H
