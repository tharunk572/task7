#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QStringList>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery* query=new QSqlQuery(conn.db);
    //query->prepare("SELECT * FROM public.\"SortedData\"", db);
    query->exec();


    model->setQuery("SELECT * FROM public.\"SortedData\"", db);
    delete query;
    ui->tableView->setModel(model);
    qDebug() << (model->rowCount());
    conn.connClose();

}


void MainWindow::on_pushButton_2_clicked()
{
    QString filepath=QFileDialog::getOpenFileName(this,"importCsv Files: Importing",QDir::rootPath(),"csv Files(*.csv)");
    qDebug()<<filepath<<"is the path of the file we imported";
    QFile mFile(filepath);
    if(!mFile.open(QFile::Text | QFile::ReadOnly))
    {
        return;
    }
    QTextStream inFile(&mFile);
    int cter=0;
    QString readLine =inFile.readLine();
    QStringList listvalue=readLine.split(",");
    ui->tableWidget->setColumnCount(listvalue.size());
    ui->tableWidget->setHorizontalHeaderLabels(listvalue);
while(!inFile.atEnd())
{
    QString readLine =inFile.readLine();
    QStringList listvalue=readLine.split(",");
    cter+=1;
    ui->tableWidget->setRowCount(cter);
    for(int k=0;k<listvalue.size();k++)
    {
        ui->tableWidget->setItem(cter-1,k,new QTableWidgetItem(listvalue[k]));
    }
}
mFile.flush();
mFile.close();

}

