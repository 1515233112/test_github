#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStack>
#include<QKeyEvent>
#include<QMap>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString operand;
    QString opcode;
    QStack<QString>operands;
    QStack<QString>opcodes;
    QMap<int,QPushButton* > digitBTNs;
    QString calculation(bool *ok = NULL);
private slots:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void on_btnDian_clicked();
    void on_btnDel_clicked();
    void btnUnaryOperatorClicked();
    void on_btnDY_clicked();

    void on_btnC_clicked();
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    QLabel *statusMsgLabel;
};
#endif // MAINWINDOW_H
