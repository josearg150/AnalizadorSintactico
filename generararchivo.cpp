#include "generararchivo.h"
#include "ui_generararchivo.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

//using namespace std;

generarArchivo::generarArchivo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::generarArchivo)
{
    ui->setupUi(this);
    this->setFixedSize(690, 400);
    this->setStyleSheet("background: #2a2a2a; "); //negro
    ui->textoAnalizado->setStyleSheet("background: #5a5a5a; color: #D69542;"); //negro
}

generarArchivo::~generarArchivo()
{
    delete ui;
}

void generarArchivo::on_btnLimpiar_clicked()
{
    ui->textoAnalizado->clear();
}

void generarArchivo::on_btnCancelar_clicked()
{
    close();
}

void generarArchivo::on_btnGenerar_clicked()
{
    if (ui->textoAnalizado->toPlainText() == "") {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setAttribute(Qt::WA_DeleteOnClose);
        msgbox->setWindowTitle("Advertencia");
        msgbox->setText("El contenido del archivo no puede estar vacío.");
        msgbox->setStyleSheet("color: #dedede;");
        msgbox->open();
    } else {
        QString contenido = ui->textoAnalizado->toPlainText();
        QString archivoGuardado = QFileDialog::getSaveFileName(this, tr("Guardar Archivo"), "archivo.dat", tr("Archivo (.dat)"));
        QFile archivo(archivoGuardado);
        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&archivo);
            out << contenido;
        }
        archivo.close();
    }
}
