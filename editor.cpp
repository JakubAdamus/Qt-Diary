#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{ 
    ui->setupUi(this);
    ui->entryDateSelector->setDisplayFormat("dd.MM.yyyy HH:mm");
    ui->entryDateSelector->setDateTime(QDateTime::currentDateTime());
    ui->entryFormatSelector->addItems({"normalny", "kursywa", "pogrubiony"});
    ui->entryColorSelector->addItems({"czarny","czerwony","zielony","niebieski","różowy"});
    ui->entryTextField->setFontFamily(entryFormat.defaultFamily());
    ui->infoLabel->setText("Nie dodano pliku");
}

void Editor::on_buttonBox_accepted()
{
    emit sendEntryData(DiaryEntry(ui->entryDateSelector->dateTime(),entryColor,entryFormat,ui->entryTextField->toPlainText(),imagePath));
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_entryFormatSelector_currentIndexChanged(int index)
{
    switch(index)
    {
       case 0:
        entryFormat.setBold(0);
        entryFormat.setItalic(0);
         break;
       case 1:
        entryFormat.setBold(0);
        entryFormat.setItalic(1);
          break;
       case 2:
        entryFormat.setBold(1);
        entryFormat.setItalic(0);
          break;
    }
    ui->entryTextField->setFont(entryFormat);
}

void Editor::on_entryColorSelector_currentIndexChanged(int index)
{
    entryColor = ui->entryTextField->textColor();
    entryColor = colors.at(index);

    ui->entryTextField->setTextColor(entryColor);
    text = ui->entryTextField->toPlainText();
    ui->entryTextField->clear();
    ui->entryTextField->setPlainText(text);
    ui->entryTextField->setFont(entryFormat);
}

void Editor::on_entryTextField_textChanged()
{
    ui->entryTextField->setTextColor(entryColor);
}

void Editor::on_addPhotoButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this,"Open Image File","","Images (*.bmp *.jpg *.png)");
    
    if(!imagePath.isEmpty())
    {
       ui->infoLabel->clear();
          ui->infoLabel->setText("Dodano plik: " + imagePath);
    }
}

