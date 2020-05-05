#include "calculator.h"
#include "ui_calculator.h"

// current value of our calculation
double calcVal = 0.0;

// set true if this was last math button pressed
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    // setup the user interface
    ui->setupUi(this);

    // display initial calcVal 0.0 in our Display widget
    ui->Display->setText(QString::number(calcVal));

    // holds references to all the number buttons
    QPushButton *numButtons[10];

    // cycle through all buttons
    for(int i = 0; i < 10; i++) {
        QString buttonName = "Button" + QString::number(i);
        // get the buttons by name and add to array
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        // setup event listener for this button
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    // connect signals and slots for math buttons
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    // connect equals button
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    // connect change sign button
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    // connect clear button
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed() {
    // get reference to number pressed
    QPushButton *button = (QPushButton *)sender();

    // get number on button
    QString buttonVal = button->text();

    // get display value
    QString displayVal = ui->Display->text();

    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText(buttonVal);
    } else {
        // concatenate new number to the right of whats being displayed
        QString newVal = displayVal + buttonVal;

        // make sure it's a double
        double dblNewVal = newVal.toDouble();

        // display
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed() {
    // reset from previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    // get our display value
    QString displayVal = ui->Display->text();

    // cast to double
    calcVal = displayVal.toDouble();

    // get reference to number pressed
    QPushButton *button = (QPushButton *)sender();

    // get text content of button
    QString buttonVal = button->text();

    // check if '/', '*', '+', or '-' was pressed
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

    // clear display area
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed() {
    // initialize solution to 0.0 in case none of the math buttons were pressed
    double solution = 0.0;

    // get our display value
    QString displayVal = ui->Display->text();

    // cast to double
    double dblDisplayVal = displayVal.toDouble();

    // do arithmetic calculation with calcVal and dlbDisplayVal based on which math button was pressed
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

    // set text of Display widget to result of our calculation
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign() {
    // get our display value
    QString displayVal = ui->Display->text();

    // check if it is a number and check sign
    QRegExp reg("[-]?[0-9.]*");

    // if it is a number change the sign
    if (reg.exactMatch(displayVal)) {
        // change sign
        double dblDisplayVal = -1 * displayVal.toDouble();

        // update display widget to our new display value
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::ClearButtonPressed() {
    // reset our calc value to 0.0
    calcVal = 0.0;

    // display our calc value
    ui->Display->setText(QString::number(calcVal));
}
