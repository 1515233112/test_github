#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTableModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewPatient();
    emit PatientEditSuccess(currow);
}


void PatientView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%' ").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void PatientView::on_btEdit_clicked()
{
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();//获取当前选择单元格的模型索引
    emit PatientEditSuccess(curIndex.row());
}

