/*!
 * \author Зайцева А. А.
 * \version 1.0
 * \brief Заголовочный файл с описанием класса dialogDelete
 */


#ifndef DIALOGDELETE_H
#define DIALOGDELETE_H

#include <QDialog>

namespace Ui {
class dialogDelete;
}
/*!
 * \brief The dialogDelete class - класс вывода диалогового окна для выбора удаляемой записи
 */
class dialogDelete : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief dialogDelete - конструктор класса
     * \param parent - указатель на родителя объекта
     */
    explicit dialogDelete(QWidget *parent = nullptr);
    /*!
     * \brief dialogDelete - деструктор класса
     */
    ~dialogDelete();
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
     * \brief on_pushButtonCancel_clicked - функция кнопки "Отмена"
     */
    void on_pushButtonCancel_clicked();

private:
    Ui::dialogDelete *ui;
};

#endif // DIALOGDELETE_H
