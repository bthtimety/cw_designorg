#include "dialogredaction.h"
#include "ui_dialogredaction.h"

dialogRedaction::dialogRedaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogRedaction)
{
    ui->setupUi(this);
    setWindowTitle(tr("Redactor"));
}

dialogRedaction::~dialogRedaction()
{
    delete ui;
}

void dialogRedaction::getData(QString& d1, QString& d2, QString& d3, QString& d4, QString& d5, QString& d6)
{
    d1 = ui->lineEdit1->text();
    d2 = ui->lineEdit2->text();
    d3 = ui->lineEdit3->text();
    d4 = ui->lineEdit4->text();
    d5 = ui->lineEdit5->text();
    d6 = ui->lineEdit6->text();
}

void dialogRedaction::editLabel(QString tableName)
{

    if (tableName == "projects")
    {
        ui->label1->setText(tr("Enter project_name:"));
        ui->label2->setText(tr("Enter manager_id:"));
        ui->label3->setText(tr("Enter consultant_id:"));
        ui->label4->setText(tr("Enter customer_id:"));
        ui->label5->setText(tr("Enter end_date:"));
        ui->label6->setText(tr("Enter price:"));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(true);
    }

    else if (tableName == "customers")
    {
        ui->label1->setText(tr("Enter customer_name:"));
        ui->label2->setText(tr("Enter phone_number:"));
        ui->label3->setText(tr("Enter email:"));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
    }

    else if (tableName == "departments")
    {
        ui->label1->setText(tr("Enter department_name:"));
        ui->label2->setText(tr(""));
        ui->label3->setText(tr(""));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(false);
        ui->lineEdit3->setEnabled(false);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
    }

    else if (tableName == "employees")
    {
        ui->label1->setText(tr("Enter first_name:"));
        ui->label2->setText(tr("Enter last_name:"));
        ui->label3->setText(tr("Enter job_id:"));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
    }

    else if (tableName == "jobs")
    {
        ui->label1->setText(tr("Enter job_name:"));
        ui->label2->setText(tr("Enter department_id:"));
        ui->label3->setText(tr(""));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(false);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
    }
}

void dialogRedaction::on_pushButtonOk_clicked()
{
    accept();
}


void dialogRedaction::on_pushButtonCancel_clicked()
{
    this->reject();
}

