#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "welcomeview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patienteditview.h"
#include "patientview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void pushWidgetToStackView(QWidget *qwidget);

    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView(int rowNo);
    void goPatientView();
    void goPreviousView();

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

    void on_labelTitle_linkActivated(const QString &link);

private:
    Ui::MasterView *ui;

    LoginView *loginView;
    WelcomeView *welcomeView;
    DoctorView *doctorView;
    DepartmentView *departmentView;
    PatientEditView *patientEditView;
    PatientView *patientView;


};
#endif // MASTERVIEW_H
