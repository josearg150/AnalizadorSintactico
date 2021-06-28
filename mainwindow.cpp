#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generararchivo.h"
#include "ui_generararchivo.h"
#include "secundario.cpp"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>

using namespace std;

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
    std::string archivoAbiertoStr = archivoAbierto.toLocal8Bit().constData();
    ui->tokens->clearContents();
    ui->producciones->clearContents();
    ui->tokens->setRowCount(0);
    ui->producciones->setRowCount(0);

    switch (analisisLex(archivoAbiertoStr)) {
        case 0: {
            ui->textBrowser->clear();
            std::ifstream t(archivoAbiertoStr);
            std::stringstream buffer;
            buffer << t.rdbuf();
            QString qstr = QString::fromStdString(buffer.str());
            ui->textBrowser->append(qstr);
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
            msgbox->setText("No se seleccionó ningún archivo.");
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

    if (analisisSin() == 0) {
        for (int j = 0; j < 50; j++) {
            std::string str = as->producciones[j];
            if (str == "") {
                break;
            }
            QString qstr = QString::fromStdString(str);
            ui->producciones->insertRow(j);
            QTableWidgetItem *aux = new QTableWidgetItem(qstr);
            aux->setTextAlignment(Qt::AlignLeft);
            ui->producciones->setItem(j, 0, aux);
        }
    } else {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setAttribute(Qt::WA_DeleteOnClose);
        msgbox->setWindowTitle("Aviso");
        msgbox->setText("Error de sintaxis.");
        msgbox->open();
    }

    /*
    switch (analisisSin()) {
        case 0: {
            for (int j = 0; j < 50; j++) {
                std::string str = as->producciones[j];
                if (str == "") {
                    break;
                }
                QString qstr = QString::fromStdString(str);
                ui->producciones->insertRow(j);
                QTableWidgetItem *aux = new QTableWidgetItem(qstr);
                aux->setTextAlignment(Qt::AlignLeft);
                ui->producciones->setItem(j, 0, aux);
            }
        }
        case 1: {
            QMessageBox* msgbox = new QMessageBox(this);
            msgbox->setAttribute(Qt::WA_DeleteOnClose);
            msgbox->setWindowTitle("Aviso");
            msgbox->setText("Error de sintaxis.");
            msgbox->open();
        }
    }
    */

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
    msgbox->setText("© Padres de Familia 4A\nVersión 1.0 y final");
    msgbox->open();
}
