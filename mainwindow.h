/*!
 * \author Зайцева А. А.
 * \version 1.0
 * \brief Заголовочный файл с описанием класса MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QComboBox>
#include <QTableView>
#include "QStandardItemModel"
#include "QStandardItem"

#include <QList>
#include <QEvent>
#include <QTranslator>
#include <QDir>
#include <QLibraryInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class QActionGroup;

/*!
 * \brief The MainWindow class - класс для отображения главного окна
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow - конструктор класса
     * \param parent - указатель на родителя объекта
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief MainWindow - деструктор класса
     */
    ~MainWindow();

private slots:
    /*!
     * \brief on_actionConnect_triggered - функция подключения к базе данных
     */
    void on_actionConnect_triggered();
    /*!
     * \brief on_actionAbout_the_author_triggered - функция вывода информации об авторе программы
     */
    void on_actionAbout_the_author_triggered();
    /*!
     * \brief on_actionDisconnect_triggered - функция отключения от базы данных
     */
    void on_actionDisconnect_triggered();
    /*!
     * \brief on_buttonQuery_clicked - функция вывода таблиц базы данных
     */
    void on_buttonQuery_clicked();
    /*!
     * \brief on_actionDelete_row_triggered - функция вывода диалогового окна для удаления записи
     */
    void on_actionDelete_row_triggered();
    /*!
     * \brief on_actionAdd_row_triggered - функция вывода диалогового окна для добавления записи
     */
    void on_actionAdd_row_triggered();
    /*!
     * \brief on_actionEdit_row_triggered - функция вывода диалогового окна для редактирования записи
     */
    void on_actionEdit_row_triggered();
    /*!
     * \brief switchLanguage - функция смены языка приложения
     * \param action - переменная класса QAction
     */
    void switchLanguage(QAction *action);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    /*!
     * \brief enablingElements - функция включения элементов меню при подключении к бд
     */
    void enablingElements(bool);
    /*!
     * \brief readSettings - функция сохранения настроек
     */
    void readSettings();
    /*!
     * \brief writeSettings - функция загрузки настроек
     */
    void writeSettings();
    /*!
     * \brief enablingEditing - функция включения меню редактирования при выводе таблицы
     */
    void enablingEditing(bool);
    /*!
     * \brief notSelected - функция выводы диалогового окна при неверных данных введеных пользователем
     */
    void notSelected();
    /*!
     * \brief deleting - функция удаления записи
     */
    void deleting(int);
    /*!
     * \brief verify - функция проверки корректности введенных пользователем данных
     * \return
     */
    bool verify(int);
    /*!
     * \brief adding - функция добавления записи
     */
    void adding(QString, QString, QString, QString, QString, QString);
    /*!
     * \brief editing - функция редактирования записи
     */
    void editing(QString, QString, QString, QString, QString, QString, int);
    /*!
     * \brief appTranslator - переменная для перевода приложения
     */
    QTranslator appTranslator;
    /*!
     * \brief qtTranslator - переменная для перевода стандартных фраз
     */
    QTranslator qtTranslator;
    /*!
     * \brief languageActionGroup - переменная, содержащая группу действий, связанных с выбором языка в приложении
     */
    QActionGroup *languageActionGroup;
    /*!
     * \brief qmPath - переменная, хранящая путь до файлов перевода
     */
    QString qmPath;
    /*!
     * \brief createLanguageMenu - функция для создания меню выбора языка
     */
    void createLanguageMenu();
};
#endif // MAINWINDOW_H
