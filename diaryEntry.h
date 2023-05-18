#ifndef DIARYENTRY_H
#define DIARYENTRY_H
#include <QString>
#include <QDateTime>
#include <QFont>
#include <QColor>
#include <QImage>

class DiaryEntry
{
private:
    QDateTime date;
    mutable QString entry;
    QFont entryFormat;
    QColor entryColor;
    QString imagePath;
    bool isEntryEmpty(QString temp) const;
public:
    DiaryEntry(QDateTime date, QColor color, QFont format, QString entry, QString imagePath);
    QString getDateAsString() const;
    QString getEntryAsString() const;
    QString getDisplayData() const;
    QColor getEntryColor() const;
    QString getSaveData() const;
    QString getImagePath() const;
    void setEntry(QString entry) const;
    bool operator>(DiaryEntry &entry) const;
    bool operator<(DiaryEntry &entry) const;
    bool operator==(DiaryEntry &entry) const;
    bool operator!=(DiaryEntry &entry) const;
};

#endif
