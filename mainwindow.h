#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase db;
    void connClose()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        db=QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("localhost");
            db.setDatabaseName("SortedTime");
            db.setUserName("postgres");
            db.setPassword("qwerty");
            if(db.open())
            {
                QMessageBox::information(this,"Connected","DataBase Connected Succesfully");

            }
            else
            {
                 QMessageBox::information(this," Not Connected","DataBase is Not  Connected");
            }

    }
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
