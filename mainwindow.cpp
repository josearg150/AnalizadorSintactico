#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generararchivo.h"
#include "ui_generararchivo.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbrir_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), ".", tr("Archivos (*.dat)"));
}

void MainWindow::on_actionGenerar_triggered()
{
    genVentana = new generarArchivo();
    genVentana->setAttribute( Qt::WA_DeleteOnClose );
    genVentana->setWindowIcon(QIcon(":/icon.ico"));
    genVentana->show();
}
