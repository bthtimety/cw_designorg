/*!
 * \author Зайцева А. А.
 * \version 1.0
 * \brief Заголовочный файл с описанием класса dialogRedaction
 */

#ifndef DIALOGREDACTION_H
#define DIALOGREDACTION_H

#include <QDialog>

namespace Ui {
class dialogRedaction;
}

/*!
 * \brief The dialogRedaction class - класс диалогового окна для добавления или изменения записи
 */
class dialogRedaction : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief dialogRedaction - конструктор класса
     * \param parent - указатель на родителя объекта
     */
    explicit dialogRedaction(QWidget *parent = nullptr);
    /*!
     * \brief dialogRedaction - деструктор класса
     */
    ~dialogRedaction();
    /*!
     * \brief getData - функция для считывания значений, введенных пользователем
     */
    void getData (QString&, QString&, QString&, QString&, QString&, QString&);
    /*!
     * \brief editLabel - функция установки текста в зависимости от выбранной таблицы
     */
    void editLabel (QString);

private slots:
    /*!
     * \brief on_pushButtonOk_clicked - функция кнопки "Ок"
     */
    void on_pushButtonOk_clicked();
    /*!
     * \brief on_pushButtonCancel_clicked - функция кнопки "Отмена"
     */
    void on_pushButtonCancel_clicked();

private:
    Ui::dialogRedaction *ui;
};

#endif // DIALOGREDACTION_H
