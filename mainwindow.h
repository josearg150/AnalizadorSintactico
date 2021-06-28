#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generararchivo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

    void on_actionGenerar_triggered();

    void on_actionAyuda_triggered();

    void on_actionAcerca_de_triggered();

private:
    Ui::MainWindow *ui;
    generarArchivo *genVentana;
};
#endif // MAINWINDOW_H
