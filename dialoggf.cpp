#include "dialoggf.h"
#include "ui_dialoggf.h"

Dialoggf::Dialoggf(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialoggf)
{
    ui->setupUi(this);
}

Dialoggf::~Dialoggf()
{
    delete ui;
}
