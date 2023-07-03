#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include "QSqlRecord"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_9->setVisible(false);
     ui->lineEdit_10->setVisible(false);
      ui->lineEdit_11->setVisible(false);
       ui->lineEdit_12->setVisible(false);


    qDebug()<<"Application initialized...";

        QString name;
        name.append("aqa.sqlite");

        aqa = QSqlDatabase::addDatabase("QSQLITE");
        aqa.setDatabaseName(name);
        if(aqa.open())
        {
           qDebug()<<"Successful database connection";
        }
        else
        {
           qDebug()<<"Error: failed database connection";
        }

        createUserTable();
        selectUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUserTable()
{
    QString query;

    query.append("CREATE TABLE IF NOT EXISTS AQQA("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "DATA VARCHAR(19),"
                 "ArBA INTEGER NOT NULL,"
                 "ArBU INTEGER NOT NULL,"
                 "AcBA INTEGER NOT NULL,"
                 "AcBU INTEGER NOT NULL,"
                 "ARece INTEGER NOT NULL,"
                 "Acalda INTEGER NOT NULL,"
                 "Observatii VARCHAR(81)"
                    ");");

    QSqlQuery create;
    create.prepare(query);

    if (create.exec())
    {
        qDebug()<<"Table exists or has been created";
    }
    else
    {
        qDebug()<<"Table not exists or has not been created";
        qDebug()<<"ERROR! "<< create.lastError();
    }
}

void MainWindow::insertUser()
{
 QString a=ui->lineEdit->text(); //a=a.toInt();
 QString b=ui->lineEdit_2->text();// b=b.toInt();
 QString c=ui->lineEdit_3->text(); //c=c.toInt();
 QString d=ui->lineEdit_4->text(); //d=d.toInt();
 QString e=ui->lineEdit_5->text();// e=a.toInt();
 QString f=ui->lineEdit_6->text(); //f=b.toInt();
 QString g=ui->lineEdit_7->text();
 QString h=ui->lineEdit_8->text();




    QSqlQuery qry;
 qry.prepare("INSERT INTO AQQA (DATA, ArBA, ArBU, AcBA, AcBU, ARece, ACalda, Observatii) VALUES (?, ?, ?, ?, ?, ?, ?, ?)" );
     qry.addBindValue(h);
     qry.addBindValue(a);
     qry.addBindValue(b);
     qry.addBindValue(c);
     qry.addBindValue(d);
     qry.addBindValue(e);
     qry.addBindValue(f);
     qry.addBindValue(g);


 //qry.exec();

   if( !qry.exec() )
       qDebug() << qry.lastError();
   else
       qDebug( "Inserted!" );
}

void MainWindow::selectUsers()
{
    QString query;
    query.append("SELECT * FROM AQQA");

    QSqlQuery select;
    select.prepare(query);

    if (select.exec())
    {
        qDebug()<<"The user is properly selected";
    }
    else
    {
        qDebug()<<"The user is not selected correctly";
        qDebug()<<"ERROR! "<< select.lastError();
    }

    int row = 0;
    ui->tableWidget->setRowCount(0);

    while (select.next())
    {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(select.value(1).toByteArray().constData()));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(select.value(2).toByteArray().constData()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(select.value(3).toByteArray().constData()));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(select.value(4).toByteArray().constData()));
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(select.value(5).toByteArray().constData()));
        ui->tableWidget->setItem(row,5,new QTableWidgetItem(select.value(6).toByteArray().constData()));
        ui->tableWidget->setItem(row,6,new QTableWidgetItem(select.value(7).toByteArray().constData()));
        ui->tableWidget->setItem(row,7,new QTableWidgetItem(select.value(8).toByteArray().constData()));
        row++;
    }

}

void MainWindow::deleteline()
{


QSqlQuery qaa;
QSqlQuery qab;

qaa.prepare("DELETE FROM AQQA WHERE id = (SELECT MAX(id) FROM AQQA)");


if( !qaa.exec() )
    qDebug() << qaa.lastError();
else
    qDebug( "Deleted!" );
if(aqa.open())
{
    qDebug() << "Opened";

}
else
{
    qDebug() << aqa.lastError();

}
//model.

update();
}

void MainWindow::on_add_clicked()
{
calculeaza();
insertUser();
selectUsers();

}


void MainWindow::on_delete_2_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "STERGERE!!!", "Doriti sa stergeti ultima linie??", QMessageBox::Yes|QMessageBox::No).exec())
    {
deleteline();
connect(ui->tableWidget,SIGNAL(update()),ui->tableWidget,SLOT(update()));
update();
    }

//update();
}

void MainWindow::on_pushButton_2_clicked()
{
calculeaza();
}

void MainWindow::calculeaza()
{
QString AAA=ui->lineEdit->text();
QString BBB = ui->lineEdit_2->text();
QString CCC = ui->lineEdit_3->text();
QString DDD = ui->lineEdit_4->text();

int A = AAA.toInt() +BBB.toInt();
int B = CCC.toInt() + DDD.toInt();


QSqlQuery query;
   QString queryString = "SELECT ArBA FROM AQQA";

   query.exec(queryString);

   while (query.next()) {
       QSqlRecord record = query.record();
       qDebug() << "ARBA : " << record.value("ArBA").toString();
   QString ARBA= record.value("ArBA").toString();
   //QString A2 =ARBA;
   ui->lineEdit_9->setText(ARBA);
    }
//---------------------------
   QSqlQuery query1;
      QString queryString1 = "SELECT ArBU FROM AQQA";

      query1.exec(queryString1);

      while (query1.next()) {
          QSqlRecord record1 = query1.record();
          qDebug() << "ARBA : " << record1.value("ArBU").toString();
      QString ARBU= record1.value("ArBU").toString();
      ui->lineEdit_10->setText(ARBU);
       }
//-------------------------

      QSqlQuery query2;
         QString queryString2 = "SELECT AcBA FROM AQQA";

         query2.exec(queryString2);

         while (query2.next()) {
             QSqlRecord record2 = query2.record();
             qDebug() << "ACBA : " << record2.value("AcBA").toString();
         QString ACBA= record2.value("AcBA").toString();
         ui->lineEdit_11->setText(ACBA);
          }

//----------------------------

         QSqlQuery query3;
            QString queryString3 = "SELECT AcBU FROM AQQA";

            query3.exec(queryString3);

            while (query3.next()) {
                QSqlRecord record3 = query3.record();
                qDebug() << "ACBU : " << record3.value("AcBU").toString();
            QString ACBU= record3.value("AcBU").toString();
            ui->lineEdit_12->setText(ACBU);
             }
//------------------------------

QString ARBA = ui->lineEdit_9->text();
QString ARBU = ui->lineEdit_10->text();
QString ACBA = ui->lineEdit_11->text();
QString ACBU = ui->lineEdit_12->text();

int A1 = A - ARBA.toInt()-ARBU.toInt();
int B1 = B - ACBA.toInt()-ACBU.toInt();

ui->lineEdit_5->setText(QString::number(A1));
ui->lineEdit_6->setText(QString::number(B1));

   }

void MainWindow::on_pushButton_clicked()
{
   qApp->exit();
}

void MainWindow::update()
{


}
