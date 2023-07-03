#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
        void createUserTable();
        void insertUser();
        void selectUsers();
        void deleteline();
        void calculeaza();
        void update();

        void rowid(QSqlQuery select);

private slots:
        void on_add_clicked();

        void on_delete_2_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase aqa;
};

#endif // MAINWINDOW_H
