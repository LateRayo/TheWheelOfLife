#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grafico.h"
#include "ui_grafico.h"

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

void MainWindow::on_Salir_clicked()
{
    QApplication::quit();
}


void MainWindow::on_RuedaOriginal_clicked()
{
    Grafico VentanaRueda;
    //VentanaRueda.show();
    VentanaRueda.exec();
}
