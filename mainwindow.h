#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editor.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPixmap>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Display
{
    First = -1,
    Second = 0,
    Third = 1
};

class Program;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program  *prg = nullptr);
    ~MainWindow();

private slots:
    void on_addEntryButton_clicked();
    void display_1();
    void display_2();
    void display_3();
    void on_ScrollUpButton_clicked();
    void on_ScrollDownButton_clicked();
    void on_DeleteButton_clicked();
    void on_CreateCopyButton_clicked();
    void on_LoadCopyButton_clicked();

private:
    Editor *editorWindow = nullptr;
    Program *program = nullptr;
    void keyPressEvent(QKeyEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void displayImage();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
