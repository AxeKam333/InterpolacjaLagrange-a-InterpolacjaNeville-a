#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void performCalculations();

private:
    QVBoxLayout *mainLayout;
    QLabel *name;
    QHBoxLayout *arithmeticLayout;
    QRadioButton *floatingPoint;
    QRadioButton *intervalArithmetic;
    QRadioButton *intervalArithmetic2;
    QRadioButton *floatingPointNevill;
    QRadioButton *intervalArithmeticNevill;
        QRadioButton *intervalArithmetic2Nevill;
    QButtonGroup *arithmeticGroup;
    QLabel *numNodesLabel;
    QLineEdit *numNodesEdit;
    QHBoxLayout *inputLayout;
    QVBoxLayout *nodesLayout;
    QLabel *nodesLabel;
    QTextEdit *nodesTextEdit;
    QVBoxLayout *valuesLayout;
    QLabel *valuesLabel;
    QTextEdit *valuesTextEdit;
    QVBoxLayout *interpolationPointLayout;
    QLabel *interpolationPointLabel;
    QTextEdit *interpolationPointTextEdit;
    QHBoxLayout *resultLayout;
    QVBoxLayout *left;
    QLabel *outputValueLabel;
    QTextEdit *outputValueTextEdit;
    QVBoxLayout *right;
    QLabel *interpolationMethodLabel;
    QTextEdit *polynomialCoefficients;
    QPushButton *computeButton;
    QWidget *centralWidget;

    double interpolationResult;  // Deklaracja zmiennej interpolationResult
    QString interpolationMethod;  // Deklaracja zmiennej interpolationMethod
};

#endif // MAINWINDOW_H
