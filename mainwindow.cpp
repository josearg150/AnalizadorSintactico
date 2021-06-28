#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generararchivo.h"
#include "ui_generararchivo.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 460);
    ui->tokens->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->producciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    QString archivoAbierto = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), ".", tr("Archivos (*.dat)"));

}

void MainWindow::on_actionGenerar_triggered()
{
    genVentana = new generarArchivo();
    genVentana->setAttribute(Qt::WA_DeleteOnClose);
    genVentana->setWindowIcon(QIcon(":/icon.ico"));
    genVentana->show();
}

void MainWindow::on_actionAyuda_triggered()
{
    QMessageBox* msgbox = new QMessageBox(this);
    msgbox->setAttribute(Qt::WA_DeleteOnClose);
    msgbox->setWindowTitle("Ayuda");
    msgbox->setText("Échele ganas.");
    msgbox->open();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox* msgbox = new QMessageBox(this);
    msgbox->setAttribute(Qt::WA_DeleteOnClose);
    msgbox->setWindowTitle("Acerca de");
    msgbox->setText("© Padres de Familia 4A\nVersión 1.0");
    msgbox->open();
}
