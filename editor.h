#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QFileDialog>
#include "diaryEntry.h"

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();
signals:
    void sendEntryData(DiaryEntry);
private slots:
    void on_buttonBox_accepted();
    void on_entryFormatSelector_currentIndexChanged(int index);

    void on_entryColorSelector_currentIndexChanged(int index);

    void on_entryTextField_textChanged();

    void on_addPhotoButton_clicked();

private:
    QFont entryFormat;
    std::array<QColor,5> colors = {"black", "red", "green", "blue", "pink"};
    QColor entryColor;
    QString text;
    QString imagePath;
    Ui::Editor *ui;
};

#endif // EDITOR_H
