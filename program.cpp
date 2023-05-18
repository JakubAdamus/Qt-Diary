#include "program.h"
#include "mainwindow.h"

Program::Program(QObject *parent) : QObject(parent)
{}

void Program::setGUI(MainWindow *ui)
{
    GUI = ui;
}

void Program::saveEntryInDiary(DiaryEntry entry)
{
    if(!entry.getEntryAsString().isEmpty())
    {
      bool isOverWritten = false;
       for(QVector<DiaryEntry>::iterator iter = entries.begin(); iter!=entries.end(); iter++)
       {
           if(iter->getDateAsString() == entry.getDateAsString())
           {
               *iter = entry;
               isOverWritten= true;
               break;
           }
       }
       if (!isOverWritten)
       {
           entries.push_back(entry);
           std::sort(entries.begin(), entries.end());
       }
    }
}

void Program::readPosition()
{
    if(entries.size()!=0)
    {
        QDateTime entryDateTime, currentDateTime = QDateTime::currentDateTime();
        qint64 remainingTime, smallestTime= std::numeric_limits<qint64>::max();

        for(int ind=0; ind < entries.size(); ind++)
        {
           entryDateTime = QDateTime::fromString(entries.at(ind).getDateAsString(),"dd.MM.yyyy HH:mm");
           remainingTime = entryDateTime.secsTo(currentDateTime);

           if(abs(remainingTime) < smallestTime)
           {
              smallestTime=abs(remainingTime);
              index = ind;
           }
        }
    }
   emit scroll();
}

void Program::nextEntry()
{
    if(++index == entries.size())
        --index;
    emit scroll();
}

void Program::previousEntry()
{
    if(--index == -1)
        ++index;
     emit scroll();
}

QString Program::getEntryForDisplay(Display disp)
{
    if(entries.size() != 0)
    {
        int ind = index + (int)disp;

        if(ind==-1)
            return QString("BRAK WSPOMNIEŃ WCZEŚNIEJSZYCH");
        else if (ind == entries.size())
            return QString("BRAK WSPOMNIEŃ PÓŹNIEJSZYCH");
        else
            return QString(entries[ind].getDisplayData());
    }
    else
    {
        return QString();
    }
}

QString Program::imagePath()
{
    if(entries.size()!=0)
       return QString(entries[index].getImagePath());
    else
       return QString();
}

void Program::deleteEntry()
{
    if(entries.size()>=1)
    {
        QVector<DiaryEntry>::iterator iter = entries.begin();
        for(int ind=0;ind<index;ind++)
            iter++;

        entries.erase(iter);
        readPosition();
     }
}

void Program::load(std::string txtFilePath)
{
    std::string line;
    QFont font;
    QVector<QString> args;

    file.open(txtFilePath, std::ios::in);
    entries.clear();
    int i=0,j=0;

    while(std::getline(file,line))
    {
        j=line.find("  ",0);
        if(j==-1) break;

        args.push_back(QString().fromStdString(line.substr(0,j)));

        for(int k=0; k<2; k++)
        {
           i=line.find("  ",j+2);
           args.push_back(QString().fromStdString(line.substr(j+2,i-j-2)));
           j=line.find("  ",i+2);

            if(i==-1 && args.size() == 4)
            {
              args.push_back("");
              break;
            }

           args.push_back(QString().fromStdString(line.substr(i+2,j-i-2)));
        }

       font.fromString(args.at(2));
       entries.push_back(DiaryEntry(QDateTime().fromString(args.at(0),"dd.MM.yyyy HH:mm"),
                            QColor(args.at(1)),font,args.at(3),args.at(4)));
       args.clear();
    }
    file.close();
    readPosition();
}

void Program::save(std::string txtFilePath)
{
  file.open(txtFilePath, std::ios::out | std::ios::trunc);
   for (QVector<DiaryEntry>::iterator iter = entries.begin(); iter!=entries.end(); iter++)
   {
     file << iter->getSaveData().toStdString() << std::endl;
   }
  file.close();
}
