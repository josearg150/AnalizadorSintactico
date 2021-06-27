#include "generararchivo.h"
#include "ui_generararchivo.h"

generarArchivo::generarArchivo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::generarArchivo)
{
    ui->setupUi(this);
}

generarArchivo::~generarArchivo()
{
    delete ui;
}
