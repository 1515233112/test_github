#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    digitBTNs ={{Qt::Key_0, ui->btn0},
                  {Qt::Key_1,ui->btn1},
                  {Qt::Key_2,ui->btn2},
                  {Qt::Key_3,ui->btn3},
                  {Qt::Key_4,ui->btn4},
                  {Qt::Key_5,ui->btn5},
                  {Qt::Key_6,ui->btn6},
                  {Qt::Key_7,ui->btn7},
                  {Qt::Key_8,ui->btn8},
                  {Qt::Key_9,ui->btn9},
                  };
    foreach (auto btn, digitBTNs) {
            connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    }
    connect(ui->btnCheng,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnJia,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnJian,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnChu,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnBFH,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnPF,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnDS,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnGH,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnZF,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    ui->statusbar->showMessage("suanhao");
    if(operands.size()==2 && opcodes.size()>0){
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();
        QString op = opcodes.front();
        opcodes.pop_front();
        if(op == "+"){
            result = operand1 + operand2;
        }else if(op == "➖"){
            result = operand1 - operand2;
        }else if(op == "×"){
            result = operand1 * operand2;
        }else if(op == "÷"){
            result = operand1 / operand2;
        }
        operands.push_back(QString::number(result));
        ui->statusbar->showMessage("ciip");

    }
    else
        ui->statusbar->showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    return QString :: number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit= qobject_cast<QPushButton *>(sender())->text();
    if(digit =="0" && operand == "0")
        digit = "";
    if(operand =="0" && digit !="0")
        operand = "";
    operand += digit;
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last operand" + operand);
     QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if(operand !=""){
        operands.push_back(operand);
        operand="";
        opcodes.push_back(opcode);
    }
    QString result = calculation();
    ui->display->setText(result);
}

void MainWindow::on_btnDian_clicked()
{
    if(!operand.contains("."))
      operand+=    qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}

void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand !=""){
        double result = operand.toDouble();
        operand="";
        QString op =qobject_cast<QPushButton*>(sender())->text();
        if(op == "%")
            result /=100.0;
        else if(op == "1/x")
            result = 1/result;
        else if(op == "x²")
            result *= result;
        else if(op == "√")
            result = sqrt(result);
        else if(op == "±")
            result = -result;

        ui->display->setText(QString::number(result));

    }


}



void MainWindow::on_btnDY_clicked()
{
    if(operand !=""){
        operands.push_back(operand);
        operand="";}
    QString result = calculation();
    ui->display->setText(result);
}


void MainWindow::on_btnC_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, digitBTNs.keys()){
        if(event->key()==btnKey)
            digitBTNs[btnKey]->animateClick();
    }
    QString keyText = event->text();
    if(keyText == "+"){
        ui->btnJia->animateClick();
    }else if(keyText == "-"){
        ui->btnJian->animateClick();
    }else if(keyText == "*"){
        ui->btnCheng->animateClick();
    }else if(keyText == "/"){
        ui->btnChu->animateClick();
    }else if(keyText == "."){
        on_btnDian_clicked();
    }else if(keyText == "="){
        on_btnDY_clicked();
    }else if(keyText == "C"){
        on_btnC_clicked();
    }

}

