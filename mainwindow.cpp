#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generararchivo.h"
#include "ui_generararchivo.h"
#include "secundario.cpp"
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
    ui->tokens->clearContents();
    ui->producciones->clearContents();
    QString archivoAbierto = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), ".", tr("Archivos (*.dat)"));
    std::string archivoAbiertoStr = archivoAbierto.toLocal8Bit().constData();
    switch (analisisLex(archivoAbiertoStr)) {
        case 0: {
            for (int i = 0; i < returnK(); i++) {
                ui->tokens->insertRow(i);
                QTableWidgetItem *aux = new QTableWidgetItem(returnAsTokens()[i]);
                aux->setTextAlignment(Qt::AlignCenter);
                ui->tokens->setItem(i, 0, aux);
            }
            break;
        }
        case 1: {
            QMessageBox* msgbox = new QMessageBox(this);
            msgbox->setAttribute(Qt::WA_DeleteOnClose);
            msgbox->setWindowTitle("Aviso");
            msgbox->setText("Error al abrir el archivo.");
            msgbox->open();
            break;
        }
        case 2: {
            QMessageBox* msgbox = new QMessageBox(this);
            msgbox->setAttribute(Qt::WA_DeleteOnClose);
            msgbox->setWindowTitle("Aviso");
            msgbox->setText("El archivo está vacío.");
            msgbox->open();
            break;
        }
    }
    cerrarArchivo();
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
