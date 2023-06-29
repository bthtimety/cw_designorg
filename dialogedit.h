/*!
 * \author Зайцева А. А.
 * \version 1.0
 * \brief Заголовочный файл с описанием класса dialogEdit
 */

#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include <QDialog>

namespace Ui {
class dialogEdit;
}

/*!
 * \brief The dialogEdit class - класс диалогового окна для выбора изменяемой записи
 */
class dialogEdit : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief dialogEdit - конструктор класса
     * \param parent
     */
    explicit dialogEdit(QWidget *parent = nullptr);
    /*!
     * \brief dialogEdit - деструктор класса
     */
    ~dialogEdit();
    /*!
      * \brief num - функция для считывания значения, введенного пользователем
      * \return
      */
     int num();

private slots:
     /*!
      * \brief on_pushButtonOk_clicked - функция кнопки "Ок"
      */
     void on_pushButtonOk_clicked();
     /*!
      * \brief on_pushButtonCancel_clicked  - функция кнопки "Отмена"
      */
     void on_pushButtonCancel_clicked();

private:
    Ui::dialogEdit *ui;
};

#endif // DIALOGEDIT_H
