#include "idatabase.h"
#include <QUuid>

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");//添加SQL LITE数据库驱动
    QString aFile = "C:/Users/Lenovo/OneDrive/文档/Navicat/SQLite/Servers/Lab4a.db";
    database.setDatabaseName(aFile);//设置数据库名称

    if(!database.open()){
        qDebug()<<"failed to open database";
    }else{
        qDebug()<<"open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    patientTableModel = new QSqlTableModel(this,database);
    patientTableModel->setTable("patient");
    patientTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式OnManualSubmit，OnRowChange
    patientTableModel->setSort(patientTableModel->fieldIndex("name"),Qt::AscendingOrder);//排序
    if(!(patientTableModel->select()))//查询数据
        return false;

    thePatientSelection = new QItemSelectionModel(patientTableModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTableModel->insertRow(patientTableModel->rowCount(),QModelIndex());//在末尾添加一条记录
    QModelIndex curIndex = patientTableModel->index(patientTableModel->rowCount()-1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTableModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTableModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTableModel->setFilter(filter);
    return patientTableModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();//获取当前选择单元格的模型索引
    patientTableModel->removeRow(curIndex.row());
    patientTableModel->submitAll();
    patientTableModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTableModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTableModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;//查询出当前记录的所有字段；
    query.prepare("select username,password from user where username= :User");
    query.bindValue(":User",userName);
    query.exec();
    if (query.next()) {
        QString username1 = query.value(0).toString(); // 获取用户名
        QString password1 = query.value(1).toString(); // 获取密码
        qDebug() << "Username:" << username1 << "Password:" << password1;
    }else{
        qDebug()<<"0no";
    }
    qDebug()<<query.lastQuery()<<query.first();
    if(query.first()){
        qDebug()<<"1yes";
    }else{
        qDebug()<<"1no";
    }
    if(query.value("username").isValid()){
        qDebug()<<"2yes";
    }else{
        qDebug()<<"2no";
    }
    if(query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if(passwd == password){
            qDebug() <<"login ok";
            return "loginOK";
        }else{
            qDebug() <<"wrong password";
            return "wrongpassword";
        }
    }else{
        qDebug() <<"on such user";
        return "loginFailed";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
