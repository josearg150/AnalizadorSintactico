#ifndef GENERARARCHIVO_H
#define GENERARARCHIVO_H

#include <QWidget>

namespace Ui {
class generarArchivo;
}

class generarArchivo : public QWidget
{
    Q_OBJECT

public:
    explicit generarArchivo(QWidget *parent = nullptr);
    ~generarArchivo();

private slots:
    void on_btnLimpiar_clicked();

    void on_btnCancelar_clicked();

    void on_btnGenerar_clicked();

private:
    Ui::generarArchivo *ui;
};

#endif // GENERARARCHIVO_H
