#include "Affair.h"


Affair::Affair()

{

}



bool Affair::setData(int id, QString startTime, QString endTime, QString content, QString urgency, QString category)
{
    m_id = id;
    m_startTime = startTime;
    m_endTime = endTime;
    m_content = content;
    m_urgency = urgency;
    m_category = category;

    return true;
}



QString Affair::startTime() const
{
    return m_startTime;
}

void Affair::setStartTime(const QString &newStartTime)
{
    m_startTime = newStartTime;
}

QString Affair::endTime() const
{
    return m_endTime;
}

void Affair::setEndTime(const QString &newEndTime)
{
    m_endTime = newEndTime;
}

QString Affair::content() const
{
    return m_content;
}

void Affair::setContent(const QString &newContent)
{
    m_content = newContent;
}

QString Affair::urgency() const
{
    return m_urgency;
}

void Affair::setUrgency(const QString &newUrgency)
{
    m_urgency = newUrgency;
}

QString Affair::category() const
{
    return m_category;
}

void Affair::setCategory(const QString &newCategory)
{
    m_category = newCategory;
}

int Affair::id() const
{
    return m_id;
}

void Affair::setId(int newId)
{
    m_id = newId;
}

