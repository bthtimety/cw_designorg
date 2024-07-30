#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogdelete.h"
#include "dialogedit.h"
#include "dialogredaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Working with project organization's DB"));

    enablingElements(false);
    enablingEditing(false);

    readSettings();

    // проверка наличия драйвера SQL
    if (QSqlDatabase::isDriverAvailable("QPSQL"))
        qDebug() << "SUCCESS: PostgreSQL database driver found!";
    else
        qDebug() << "FAILURE: No postgreSQL database driver available!";

    // переводы
    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);
    qmPath = qApp->applicationDirPath() + "/tr";

    qDebug() << "qmPath: " << qmPath;
    createLanguageMenu();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}

// подключение к бд
void MainWindow::on_actionConnect_triggered()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("rdbms.vt"); // хост
    db.setDatabaseName("mydb"); // бд
    db.setPort(5432); // порт
    db.setConnectOptions("requiressl=1;connect_timeout=2");
    db.setUserName("myuser"); // пользователь
    db.setPassword("3333"); // пароль

    // проверка подключения
    if (db.open()) {
        qDebug() << "Connect success!";
        enablingElements(true);
    }
    else {
        qDebug() << "Connect fail: " << db.lastError().text();
    }
}


void MainWindow::on_actionAbout_the_author_triggered()
{
    QMessageBox::about(this, tr("About the app"),
                             tr("This program was developed by student\n"
                                "of ICTMS-3-8 Zaytseva Anastasia Alekseevna."));
}

// отключение от бд
void MainWindow::on_actionDisconnect_triggered()
{
    db.close();
    qDebug() << "Disconnected!";
    enablingElements(false);
    enablingEditing(false);
}

void MainWindow::readSettings() {
    QSettings settings("Home","cw_designorg");
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(400, 500)).toSize());
    move(settings.value("position", QPoint(200, 200 )).toPoint());
}

void MainWindow::writeSettings() {
    QSettings settings("Home","cw_designorg");
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();
}

void MainWindow::enablingElements(bool b) {
    ui->comboBox->setEnabled(b);
    ui->buttonQuery->setEnabled(b);
    ui->actionConnect->setEnabled(!b);
    ui->actionDisconnect->setEnabled(b);
}

void MainWindow::on_buttonQuery_clicked()
{
    QSqlQuery query; // запрос
    QStandardItemModel *model = new QStandardItemModel; // модель
    QStandardItem *item;
    QStringList horizontalHeader; // столбцы
    QStringList verticalHeader; // строки

    enablingEditing(true);

    if (ui->comboBox->currentText() == "departments") { // для таблицы с отделами

        query.exec("SELECT * FROM departments");

        horizontalHeader << tr("Department");
        model->setHorizontalHeaderLabels(horizontalHeader);

        while (query.next())
            verticalHeader.append(query.value(0).toString());
        model->setVerticalHeaderLabels(verticalHeader);

        query.seek(-1);

        while (query.next()) {
            for (int i = 1; i < query.record().count(); i++) {
                item = new QStandardItem(QString(query.value(i).toString()));
                model->setItem(query.at(), i-1, item);
            }
        }
    }

    else if (ui->comboBox->currentText() == "customers") { // для таблицы с клиентами

        query.exec("SELECT * FROM customers");

        horizontalHeader << tr("Сustomers") << tr("Phone number") << "E-mail";
        model->setHorizontalHeaderLabels(horizontalHeader);

        while (query.next())
            verticalHeader.append(query.value(0).toString());
        model->setVerticalHeaderLabels(verticalHeader);

        query.seek(-1);

        while (query.next()) {
            for (int i = 1; i < query.record().count(); i++) {
                item = new QStandardItem(QString(query.value(i).toString()));
                model->setItem(query.at(), i-1, item);
            }
        }
    }

    else if (ui->comboBox->currentText() == "jobs") {

        query.exec("SELECT job_id, job_name, departments.department_name \
                    FROM jobs \
                    JOIN departments ON jobs.department_id = departments.department_id");


        horizontalHeader << tr("Job") << tr("Department");
        model->setHorizontalHeaderLabels(horizontalHeader);

        while (query.next())
            verticalHeader.append(query.value(0).toString());
        model->setVerticalHeaderLabels(verticalHeader);

        query.seek(-1);

        while (query.next()) {
            for (int i = 1; i < query.record().count(); i++) {
                item = new QStandardItem(QString(query.value(i).toString()));
                model->setItem(query.at(), i-1, item);
            }
        }
    }

    else if (ui->comboBox->currentText() == "employees") {

        query.exec("SELECT employee_id, first_name, last_name, jobs.job_name \
                    FROM employees \
                    JOIN jobs ON employees.job_id = jobs.job_id");


        horizontalHeader << tr("First name") << tr("Last name") << tr("Job");
        model->setHorizontalHeaderLabels(horizontalHeader);

        while (query.next())
            verticalHeader.append(query.value(0).toString());
        model->setVerticalHeaderLabels(verticalHeader);

        query.seek(-1);

        while (query.next()) {
            for (int i = 1; i < query.record().count(); i++) {
                item = new QStandardItem(QString(query.value(i).toString()));
                model->setItem(query.at(), i-1, item);
            }
        }
    }

    else if (ui->comboBox->currentText() == "projects") {

        query.exec("SELECT projects.project_id, projects.project_name, \
                             manager.last_name AS manager_last_name, \
                             consultant.last_name AS consultant_last_name, customer.customer_name, \
                             projects.end_date, projects.price FROM projects \
                             JOIN employees manager ON manager.employee_id = projects.manager_id \
                             JOIN employees consultant ON consultant.employee_id = projects.consultant_id \
                             JOIN customers customer ON customer.customer_id = projects.customer_id ");

        horizontalHeader << tr("Project") << tr("Manager") << tr("Consultant") << tr("Customer") << tr("End Date") << tr("Price");
        model->setHorizontalHeaderLabels(horizontalHeader);

        while (query.next())
            verticalHeader.append(query.value(0).toString());
        model->setVerticalHeaderLabels(verticalHeader);

        query.seek(-1);

        while (query.next()) {
            for (int i = 1; i < query.record().count(); i++) {
                item = new QStandardItem(QString(query.value(i).toString()));
                model->setItem(query.at(), i-1, item);
            }
        }
    }

    // передача данных в модель
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::enablingEditing(bool b) {
    ui->actionAdd_row->setEnabled(b);
    ui->actionEdit_row->setEnabled(b);
    ui->actionDelete_row->setEnabled(b);
    ui->menuEditing->setEnabled(b);
}

void MainWindow::notSelected() {
    QMessageBox message;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("Selected row doesn't exist! Please, try again."),
                                  QMessageBox::Ok |
                                  QMessageBox::Cancel);

    message.setDefaultButton(QMessageBox::Ok);
    if(reply == QMessageBox::Ok) return;
    else return;
}

void MainWindow::on_actionDelete_row_triggered()
{
    dialogDelete select;
    int selected;
    while (true) {
        if (select.exec())
            selected = select.num();
        if (select.result() == dialogDelete::Rejected) return;
        if(verify(selected))
            break;
        else notSelected();
    }
    deleting(selected);
    on_buttonQuery_clicked();
}

bool MainWindow::verify(int ver) {
    QSqlQuery query;
    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    while (query.next())
        if (ver == query.value(0))
            return true;
    return false;
}

void MainWindow::deleting(int del) {
    QSqlQuery query;
    QString string_del = QString::number(del);
    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    QString columnDel = query.record().fieldName(0);
    query.exec("DELETE FROM " + ui->comboBox->currentText() + " WHERE " + columnDel + " = " + string_del);
}



void MainWindow::on_actionAdd_row_triggered()
{
    dialogRedaction add;
    add.editLabel(ui->comboBox->currentText());
    QString d1, d2, d3, d4, d5, d6;

    while(true) {
        if(add.exec())
            add.getData(d1, d2, d3, d4, d5, d6);
        if(add.result() == dialogRedaction::Rejected)
            return;
        else
            break;
    }

    adding(d1, d2, d3, d4, d5, d6);
    on_buttonQuery_clicked();
}

void MainWindow::adding(QString d1, QString d2, QString d3, QString d4, QString d5, QString d6) {
    QSqlQuery query;
    QString tableName = ui->comboBox->currentText();
    QString queryValues;

    if (tableName == "projects") {
        queryValues = "(DEFAULT, '" + d1 + "', " + d2 + ", " + d3 + ", " + d4 + ", DATE '" + d5 + "', " + d6 + ")";
    }
    else if (tableName == "customers") {
        queryValues = "(DEFAULT, '" + d1 + "', " + d2 + ", '" + d3 + "')";
    }
    else if (tableName == "departments") {
        queryValues = "(DEFAULT, '" + d1 + "')";
    }
    else if (tableName == "employees") {
        queryValues = "(DEFAULT, '" + d1 + "', '" + d2 + "', " + d3 + ")";
    }
    else if (tableName == "jobs") {
        queryValues = "(DEFAULT, '" + d1 + "', " + d2 + ")";
    }

    query.exec("INSERT INTO " + ui->comboBox->currentText() + " VALUES " + queryValues);
}

void MainWindow::on_actionEdit_row_triggered()
{
    dialogEdit select;
    int selected;
        while (true) {
            if (select.exec())
                selected = select.num();
            if (select.result() == dialogDelete::Rejected) return;
            if(verify(selected))
                break;
            else notSelected();
        }

     dialogRedaction edit;
     edit.editLabel(ui->comboBox->currentText());
     QString d1, d2, d3, d4, d5, d6;

     while(true) {
         if(edit.exec())
             edit.getData(d1, d2, d3, d4, d5, d6);
         if(edit.result() == dialogRedaction::Rejected)
             return;
         else
             break;
     }

     editing(d1, d2, d3, d4, d5, d6, selected);
     on_buttonQuery_clicked();
}


void MainWindow::editing(QString d1, QString d2, QString d3, QString d4, QString d5, QString d6, int number) {
    QSqlQuery query;
    QString tableName = ui->comboBox->currentText();
    QString queryValues;

    if (tableName == "projects") {
        queryValues = "project_name = '" + d1 + "', manager_id = " + d2 +
                      ", consultant_id = " + d3 + ", customer_id = " + d4 +
                      ", end_date = DATE '" + d5 + "', price = " + d6;
    }
    else if (tableName == "customers") {
        queryValues = "customer_name = '" + d1 + "', phone_number = " + d2 +
                      ", email = '" + d3 + "'";
    }
    else if (tableName == "departments") {
        queryValues = "department_name = '" + d1 + "'";
    }
    else if (tableName == "employees") {
        queryValues = "first_name = '" + d1 + "', last_name= '" + d2 + "', job_id = " + d3;
    }
    else if (tableName == "jobs") {
        queryValues = "job_name = '" + d1 + "', department_id = " + d2;
    }

    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    QString columnName = query.record().fieldName(0);
    query.exec("UPDATE " + ui->comboBox->currentText() + " SET " + queryValues + " WHERE " + columnName + " = " + QString::number(number));
}

void MainWindow::createLanguageMenu()
{
    languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);
    QDir dir(qmPath);
    QStringList fileNames = dir.entryList(QStringList("cw_designorg_*.qm"));
    for (int i = 0; i < fileNames.size(); i++)  {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.remove(0, locale.indexOf('_') + 1);
        locale.truncate(locale.lastIndexOf('.'));
        QTranslator translator;
        translator.load(fileNames[i], qmPath);
        QString language = translator.translate("MainWindow", "English");
        QAction *action = new QAction(tr("&%1 %2").arg(i + 1).arg(language), this);
        action->setCheckable(true);
        action->setData(locale);
        ui->menuLanguage->addAction(action);
        languageActionGroup->addAction(action);
        if (language == "English")
            action->setChecked(true);
    }
}

void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();
    appTranslator.load("cw_designorg_" + locale + ".qm", qmPath);
    locale.chop(3);
    qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    ui->retranslateUi(this);
}
