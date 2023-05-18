#include "diaryEntry.h"

DiaryEntry::DiaryEntry(QDateTime date, QColor color, QFont format, QString entry, QString imagePath)
    :date(date),entryFormat(format),entryColor(color), imagePath(imagePath)
{
    setEntry(entry);
}

 QString DiaryEntry::getDateAsString() const
 {
     return date.toString("dd.MM.yyyy HH:mm");
 }

 QString DiaryEntry::getEntryAsString() const
 {
     return entry;
 }

 QColor DiaryEntry::getEntryColor() const
 {
     return entryColor;
 }

 QString DiaryEntry::getImagePath() const
 {
     return imagePath;
 }

 QString DiaryEntry::getDisplayData() const
 {
    if(entryFormat.italic())
        return QString("<b>" + getDateAsString() +
                       "</b><br><span style=color:" + entryColor.name() + "><i>" + entry + "</i></span>");
    else if(entryFormat.bold())
        return QString("<b>" + getDateAsString() +
                       "</b><br><span style=color:" + entryColor.name() + "><b>" + entry + "</b></span>");
    else
        return QString("<b>" + getDateAsString() +
                       "</b><br><span style=color:" + entryColor.name() + ">" + entry + "</span>");
 }

 QString DiaryEntry::getSaveData() const
 {
     return QString(getDateAsString() + "  " + entryColor.name() +
                    "  " + entryFormat.toString() + "  " + entry + "  " + imagePath);
 }


 bool DiaryEntry::isEntryEmpty(QString temp) const
 {
     temp = temp.simplified();
     return temp.isEmpty();
 }

 void DiaryEntry::setEntry(QString entry) const
 {
     if(!isEntryEmpty(entry))
         this->entry = entry.simplified();
 }

 bool DiaryEntry::operator>(DiaryEntry &entry) const
 {
    return (this->date > entry.date);
 }

 bool DiaryEntry::operator<(DiaryEntry &entry) const
 {
    return (this->date < entry.date);
 }

 bool DiaryEntry::operator==(DiaryEntry &entry) const
 {
     return (this->date == entry.date);
 }

 bool DiaryEntry::operator!=(DiaryEntry &entry) const
 {
     return (this->date!= entry.date);
 }

