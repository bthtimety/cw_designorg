#include "dialogdelete.h"
#include "ui_dialogdelete.h"

dialogDelete::dialogDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDelete)
{
    ui->setupUi(this);
    setWindowTitle(tr("Delete"));
}

dialogDelete::~dialogDelete()
{
    delete ui;
}

int dialogDelete::num()
{
    return ui->lineEdit->text().toInt();
}

void dialogDelete::on_pushButtonOk_clicked()
{
    num();
    accept();
}


void dialogDelete::on_pushButtonCancel_clicked()
{
    this->reject();
}

