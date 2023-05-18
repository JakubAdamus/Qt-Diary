#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "program.h"

MainWindow::MainWindow(QWidget *parent, Program *prg)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), program(prg)
{
    prg->setGUI(this);
    ui->setupUi(this);
    ui->displayField->setReadOnly(true);
    ui->displayField_2->setReadOnly(true);
    ui->displayField_3->setReadOnly(true);
    this->setFocusPolicy(Qt::StrongFocus);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setMinimumSize(130,70);
    connect(program,SIGNAL(scroll()),this,SLOT(display_1()));
    connect(program,SIGNAL(scroll()),this,SLOT(display_2()));
    connect(program,SIGNAL(scroll()),this,SLOT(display_3()));
    program->load();
}

MainWindow::~MainWindow()
{
    program->save();
    delete ui;
}

void MainWindow::on_addEntryButton_clicked()
{
  editorWindow = new Editor(this);
  connect(editorWindow, SIGNAL(sendEntryData(DiaryEntry)),program, SLOT(saveEntryInDiary(DiaryEntry)));
  if(editorWindow->exec())
  {
      program->readPosition();
  }
  delete editorWindow;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
     case Qt::Key_Up:
      program->previousEntry();
          break;
     case Qt::Key_Down:
      program->nextEntry();
          break;
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
   if(event->angleDelta().y() > 0)
       program->previousEntry();
   else if (event->angleDelta().y() < 0)
       program->nextEntry();
}

void MainWindow::display_1()
{
   ui->displayField->clear();
   ui->displayField->insertHtml(program->getEntryForDisplay(Display::First));
   ui->displayField->show();
}

void MainWindow::display_2()
{
   ui->displayField_2->clear();
   ui->displayField_2->insertHtml(program->getEntryForDisplay(Display::Second));
   displayImage();
   ui->displayField_2->show();
}

void MainWindow::display_3()
{
    ui->displayField_3->clear();
    ui->displayField_3->insertHtml(program->getEntryForDisplay(Display::Third));
    ui->displayField_3->show();
}

void MainWindow::on_ScrollUpButton_clicked()
{
    program->previousEntry();
}

void MainWindow::on_ScrollDownButton_clicked()
{
    program->nextEntry();
}

void MainWindow::displayImage()
{
    QSize size = ui->imageLabel->size();
    if(!program->imagePath().isEmpty())
        ui->imageLabel->setPixmap(QPixmap::fromImage(QImage(program->imagePath()).scaled(size)));
    else
        ui->imageLabel->setText("Brak Zdjęcia");
}

void MainWindow::on_DeleteButton_clicked()
{
    program->deleteEntry();
}

void MainWindow::on_CreateCopyButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Save in Text File","","Text (*.txt)");
    if(!filePath.isEmpty())
       program->save(filePath.toStdString());
}

void MainWindow::on_LoadCopyButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Load from Text File","","Text (*.txt)");
    if(!filePath.isEmpty())
       program->load(filePath.toStdString());
}
