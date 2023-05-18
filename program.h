#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include "diaryEntry.h"
#include <fstream>

enum class Display;
class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr);
    QString getEntryForDisplay(Display disp);
    void save(std::string txtFilePath = "memories.txt");
    void load(std::string txtFilePath = "memories.txt");
    void readPosition();
    void deleteEntry();
    void nextEntry();
    void previousEntry();
    QString imagePath();

private slots:
    void saveEntryInDiary(DiaryEntry entry);

signals:
    void scroll();

private:
    MainWindow *GUI = nullptr;
    QVector<DiaryEntry> entries;
    int index = 0;
    std::fstream file;

};

#endif // PROGRAM_H
