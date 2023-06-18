#include "mainwindow.h"
#include "lagrange.h"
#include "nevill.h"
#include "Interval.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mainLayout = new QVBoxLayout();
    QLabel *name = new QLabel("Oblicz Interpolacje");
    name->setAlignment(Qt::AlignCenter);
    arithmeticLayout = new QHBoxLayout();

    floatingPoint = new QRadioButton("Arytmetyka zmiennopozycyjna - metoda Lagrange'a");
    intervalArithmetic = new QRadioButton("Arytmetyka przedziałowa - metoda Lagrange'a");
    intervalArithmetic2 = new QRadioButton("Arytmetyka przedziałowa (dane przedziałowe) - metoda Lagrange'a");
    floatingPointNevill = new QRadioButton("Arytmetyka zmiennopozycyjna - metoda Neville'a");
    intervalArithmeticNevill = new QRadioButton("Arytmetyka przedziałowa - metoda Neville'a");
    intervalArithmetic2Nevill = new QRadioButton("Arytmetyka przedziałowa (dane przedziałowe) - metoda Neville'a");

    arithmeticGroup = new QButtonGroup();
    arithmeticGroup->addButton(floatingPoint);
    arithmeticGroup->addButton(intervalArithmetic);
    arithmeticGroup->addButton(intervalArithmetic2);
    arithmeticGroup->addButton(floatingPointNevill);
    arithmeticGroup->addButton(intervalArithmeticNevill);
    arithmeticGroup->addButton(intervalArithmetic2Nevill);

    arithmeticLayout = new QHBoxLayout();
    arithmeticLayout->addWidget(floatingPoint);
    arithmeticLayout->addWidget(intervalArithmetic);
    arithmeticLayout->addWidget(intervalArithmetic2);

    QHBoxLayout* arithmeticLayoutNevill = new QHBoxLayout();
    arithmeticLayoutNevill->addWidget(floatingPointNevill);
    arithmeticLayoutNevill->addWidget(intervalArithmeticNevill);
    arithmeticLayoutNevill->addWidget(intervalArithmetic2Nevill);

    mainLayout->addLayout(arithmeticLayout);
    mainLayout->addLayout(arithmeticLayoutNevill);


    numNodesLabel = new QLabel("Wpisz liczbę węzłów");
    numNodesEdit = new QLineEdit();
    arithmeticLayout->addWidget(numNodesLabel);
    arithmeticLayout->addWidget(numNodesEdit);

    // ZMIENNOPOZYCYJNA
    inputLayout = new QHBoxLayout();
    QVBoxLayout *nodesLayout = new QVBoxLayout();
    nodesLabel = new QLabel("Wpisz węzły interpolacji");
    nodesTextEdit = new QTextEdit();  // Initializing nodesTextEdit before using it
    nodesLayout->addWidget(nodesLabel);
    nodesLayout->addWidget(nodesTextEdit);

    QVBoxLayout *valuesLayout = new QVBoxLayout();
    valuesLabel = new QLabel("Wpisz wartości funkcji w węzłach");
    valuesTextEdit = new QTextEdit();
    valuesLayout->addWidget(valuesLabel);
    valuesLayout->addWidget(valuesTextEdit);

    QVBoxLayout *interpolationPointLayout = new QVBoxLayout();
    interpolationPointLabel = new QLabel("Wpisz wartość wezła, dla którego chcesz obliczyć wartość funkcji");
    interpolationPointTextEdit = new QTextEdit();
    interpolationPointLayout->addWidget(interpolationPointLabel);
    interpolationPointLayout->addWidget(interpolationPointTextEdit);

    inputLayout->addLayout(nodesLayout);
    inputLayout->addLayout(valuesLayout);
    inputLayout->addLayout(interpolationPointLayout);

    resultLayout = new QHBoxLayout();

    QVBoxLayout *left = new QVBoxLayout();
    QLabel *outputValueLabel = new QLabel("Wartość funkcji dla podanego wezła");
    outputValueTextEdit = new QTextEdit();
    outputValueTextEdit->setReadOnly(true);
    left->addWidget(outputValueLabel);
    left->addWidget(outputValueTextEdit);

    QVBoxLayout *right = new QVBoxLayout;
    QLabel *polynomialCoefficientsLabel = new QLabel("Współczynniki wielomianu");
    polynomialCoefficients = new QTextEdit();
    polynomialCoefficients->setReadOnly(true);
    right->addWidget(polynomialCoefficientsLabel);
    right->addWidget(polynomialCoefficients);

    resultLayout->addLayout(left);
    resultLayout->addLayout(right);

    computeButton = new QPushButton("OBLICZ");
    mainLayout->addWidget(name);
    //mainLayout->addLayout(arithmeticLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(resultLayout);
    mainLayout->addWidget(computeButton);

    centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(arithmeticGroup, &QButtonGroup::buttonToggled,
            [=](QAbstractButton *button, bool checked) {
                if (checked) {
                    for (auto &otherButton : arithmeticGroup->buttons()) {
                        if (otherButton != button) {
                            otherButton->setChecked(false);
                        }
                    }
                }
            });

    // Initially show all the widgets
    nodesLabel->show();
    nodesTextEdit->show();
    valuesLabel->show();
    valuesTextEdit->show();
    interpolationPointLabel->show();
    interpolationPointTextEdit->show();
    outputValueLabel->show();
    outputValueTextEdit->show();
    numNodesLabel->show();
    numNodesEdit->show();
    computeButton->show();
    polynomialCoefficientsLabel->show();
    polynomialCoefficients->show();

    connect(arithmeticGroup, &QButtonGroup::buttonToggled,
            [=](QAbstractButton *button, bool checked) {
                if (checked) {
                    for (auto &otherButton : arithmeticGroup->buttons()) {
                        if (otherButton != button) {
                            otherButton->setChecked(false);
                        }
                    }
                }
            });

    // Connect the "OBLICZ" button to a function that performs the calculations and updates the results text box.
    connect(computeButton, &QPushButton::clicked, this, &MainWindow::performCalculations);
}

void MainWindow::performCalculations() {
    polynomialCoefficients->setText("");
    QString arithmeticType;
    if (floatingPoint->isChecked()) {
        arithmeticType = "Arytmetyka zmiennopozycyjna - metoda Lagrange'a";
    } else if (intervalArithmetic->isChecked()) {
        arithmeticType = "Arytmetyka przedziałowa - metoda Lagrange'a";
    } else if (intervalArithmetic2->isChecked()) {
        arithmeticType = "Arytmetyka przedziałowa (dane przedziałowe) - metoda Lagrange'a";
    } else if (floatingPointNevill->isChecked()) {
        arithmeticType = "Arytmetyka zmiennopozycyjna - metoda Neville'a";
    } else if (intervalArithmeticNevill->isChecked()) {
        arithmeticType = "Arytmetyka przedziałowa - metoda Neville'a";
    } else if (intervalArithmetic2Nevill->isChecked()) {
        arithmeticType = "Arytmetyka przedziałowa (dane przedziałowe) - metoda Neville'a";
    }

    bool conversionOk;
    int size = numNodesEdit->text().toInt(&conversionOk);
    if (!conversionOk) {
        outputValueTextEdit->setText("Wprowadzono nieprawidłowe dane");
        return;
    }

    QString interpolationPointString = interpolationPointTextEdit->toPlainText();

    QString nodesText = nodesTextEdit->toPlainText();
    QStringList nodesStringList = nodesText.split('\n');
    QString valuesText = valuesTextEdit->toPlainText();
    QStringList valuesStringList = valuesText.split('\n');

    if (nodesStringList.size() != size || valuesStringList.size() != size) {
        outputValueTextEdit->setText("Wprowadzono nieprawidłowe dane");
        return;
    }

    long double interpolationPoint;
    interval_arithmetic::Interval<long double> intervalInterpolationPoint;

    QVector<long double> nodes(size);
    QVector<interval_arithmetic::Interval<long double>> intervalNodes(size);
    QVector<long double> values(size);
    QVector<interval_arithmetic::Interval<long double>> intervalValues(size);

    if (arithmeticType == "Arytmetyka zmiennopozycyjna - metoda Lagrange'a" || arithmeticType == "Arytmetyka zmiennopozycyjna - metoda Neville'a") {
        interpolationPoint = interpolationPointString.toDouble();
        for (int i = 0; i < size; ++i) {
            nodes[i] = nodesStringList[i].toDouble();
            values[i] = valuesStringList[i].toDouble();
        }
    } else if (arithmeticType == "Arytmetyka przedziałowa - metoda Lagrange'a" || arithmeticType == "Arytmetyka przedziałowa - metoda Neville'a") {
        intervalInterpolationPoint = interval_arithmetic::IntRead<long double>(interpolationPointString.toStdString());
        for (int i = 0; i < size; ++i) {
            intervalNodes[i] = interval_arithmetic::IntRead<long double>(nodesStringList[i].toStdString());
            intervalValues[i] = interval_arithmetic::IntRead<long double>(valuesStringList[i].toStdString());
        }
    } else if (arithmeticType == "Arytmetyka przedziałowa (dane przedziałowe) - metoda Lagrange'a" || arithmeticType == "Arytmetyka przedziałowa (dane przedziałowe) - metoda Neville'a") {
        QStringList bounds = interpolationPointString.split(',');
        if (bounds.size() != 2) {
            outputValueTextEdit->setText("Wprowadzono nieprawidłowe dane");
                return;
        }

        intervalInterpolationPoint.a = interval_arithmetic::LeftRead<long double>(bounds[0].toStdString());
        intervalInterpolationPoint.b = interval_arithmetic::RightRead<long double>(bounds[1].toStdString());

        for (int i = 0; i < size; ++i) {
            QStringList intervalBounds = nodesStringList[i].split(',');
            if (intervalBounds.size() != 2) {
                outputValueTextEdit->setText("Wprowadzono nieprawidłowe dane");
                return;
            }
            QStringList intervalValuesBounds = valuesStringList[i].split(',');
            if (intervalValuesBounds.size() != 2) {
                outputValueTextEdit->setText("Wprowadzono nieprawidłowe dane");
                return;
            }
            intervalNodes[i].a = interval_arithmetic::LeftRead<long double>(intervalBounds[0].toStdString());
            intervalNodes[i].b = interval_arithmetic::RightRead<long double>(intervalBounds[1].toStdString());
            intervalValues[i].a = interval_arithmetic::LeftRead<long double>(intervalValuesBounds[0].toStdString());
            intervalValues[i].b = interval_arithmetic::RightRead<long double>(intervalValuesBounds[1].toStdString());
        }
    }

    QString interpolationResult;
    QString coefficiens;

    if (arithmeticType == "Arytmetyka zmiennopozycyjna - metoda Lagrange'a") {
        long double* emptyTab= new long double[size];
        long double* lagrangeCoefficients = lagrange_wspolczynniki_wielomianu(nodes.data(), values.data(), size, emptyTab);
        long double result = lagrange_wartosc_wielomianu(lagrangeCoefficients, size, interpolationPoint);
        interpolationResult = QString::fromStdString(std::to_string(result));
        for (int i = size-1; i >= 0; --i) {
            coefficiens += "f[" + QString::number(size-1-i) + "]=" + QString::fromStdString(std::to_string(lagrangeCoefficients[i])) + "\n";
        }
        delete[] lagrangeCoefficients;
    } else if (arithmeticType == "Arytmetyka przedziałowa - metoda Lagrange'a" || arithmeticType == "Arytmetyka przedziałowa (dane przedziałowe) - metoda Lagrange'a") {
        interval_arithmetic::Interval<long double>* emptyTab= new interval_arithmetic::Interval<long double>[size];
        interval_arithmetic::Interval<long double>* lagrangeCoefficients = lagrange_wspolczynniki_wielomianu_interv(intervalNodes.data(), intervalValues.data(), size, emptyTab);
        interval_arithmetic::Interval<long double> intervalResult = lagrange_wartosc_wielomianu_interv(lagrangeCoefficients, size, intervalInterpolationPoint);
        string left, right;
        intervalResult.IEndsToStrings(left, right);
        long double doubleWidth = IntWidth(intervalResult);
        QString width = QString::number(doubleWidth,'E',16);
        interpolationResult = "[" + QString::fromStdString(left) + ", " + QString::fromStdString(right) + "] szerokosc:" + width;
        for (int i = size-1; i >= 0; --i) {
            lagrangeCoefficients[i].IEndsToStrings(left, right);
            doubleWidth = IntWidth(lagrangeCoefficients[i]);
            coefficiens += "f[" + QString::number(size-1-i) + "]=" + "[" + QString::fromStdString(left) + ", " + QString::fromStdString(right) + "] szerokosc:" + width+"\n";
        }
        delete[] lagrangeCoefficients;
    } else if (arithmeticType == "Arytmetyka zmiennopozycyjna - metoda Neville'a") {
        long double result = neville_wartosc_wielomianu(nodes.data(), values.data(), size, interpolationPoint);
        interpolationResult = QString::fromStdString(std::to_string(result));
    } else if (arithmeticType == "Arytmetyka przedziałowa - metoda Neville'a" || arithmeticType == "Arytmetyka przedziałowa (dane przedziałowe) - metoda Neville'a") {
        interval_arithmetic::Interval<long double> intervalResult = neville_wartosc_wielomianu_interv(intervalNodes.data(), intervalValues.data(), size, intervalInterpolationPoint);
        string left, right;
        intervalResult.IEndsToStrings(left, right);
        long double doubleWidth = IntWidth(intervalResult);
        QString width = QString::number(doubleWidth,'E',16);
        interpolationResult = "[" + QString::fromStdString(left) + ", " + QString::fromStdString(right) + "] szerokosc:" + width;
    }

    outputValueTextEdit->setText(interpolationResult);
    polynomialCoefficients->setText(coefficiens);
}

