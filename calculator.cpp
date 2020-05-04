#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));

    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText(buttonVal);
    } else {
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed() {
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    if (QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    }
    else if (QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    }
    else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    }
    else {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        }
        else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        }
        else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        }
        else {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign() {
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal)) {
        double dblDisplayVal = -1 * displayVal.toDouble();
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::ClearButtonPressed() {
    calcVal = 0.0;
    ui->Display->setText(QString::number(calcVal));
}
