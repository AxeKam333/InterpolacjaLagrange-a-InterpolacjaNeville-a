#include<iostream>
#include<iomanip>
#include <cmath>
#include"Interval.h"

using namespace std;


long double neville_wartosc_wielomianu(long double* x, long double* y, int n, long double x0)
{
    long double** R = new long double*[n];
    for (int i = 0; i < n; i++)
    {
        R[i] = new long double[n];
        R[i][0] = y[i];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            R[i][j] = ((x0 - x[i - j]) * R[i][j - 1] - (x0 - x[i]) * R[i - 1][j - 1]) / (x[i] - x[i - j]);
        }
    }
    /*
        |       R[i][0]      |       R[i][1]       |       R[i][2]       |       R[i][3]       |
    --------------------------------------------------------------------------------------------
    R[0]|         1.0        |         0.0         |         0.0         |         0.0         |
    --------------------------------------------------------------------------------------------
    R[1]|         3.0        |         5.0         |         0.0         |         0.0         |
    --------------------------------------------------------------------------------------------
    R[2]|         2.0        |         2.5         |        3.333333     |         0.0         |
    --------------------------------------------------------------------------------------------
    R[3]|         1.0        |         3.0         |        2.666666     |         3.0         |
    --------------------------------------------------------------------------------------------
    */

    long double result = R[n - 1][n - 1];

    // Zwolnienie pamiêci
    for (int i = 0; i < n; i++)
    {
        delete[] R[i];
    }
    delete[] R;

    return result;
}

interval_arithmetic::Interval<long double> neville_wartosc_wielomianu_interv(interval_arithmetic::Interval<long double>* x, interval_arithmetic::Interval<long double>* y, int n, interval_arithmetic::Interval<long double> x0)
{
    interval_arithmetic::Interval<long double>** R = new interval_arithmetic::Interval<long double>*[n];
    for (int i = 0; i < n; i++)
    {
        R[i] = new interval_arithmetic::Interval<long double>[n];
        R[i][0] = y[i];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            R[i][j] = ((x0 - x[i - j]) * R[i][j - 1] - (x0 - x[i]) * R[i - 1][j - 1]) / (x[i] - x[i - j]);
        }
    }

    interval_arithmetic::Interval<long double> result = R[n - 1][n - 1];

    // Zwolnienie pamiêci
    for (int i = 0; i < n; i++)
    {
        delete[] R[i];
    }
    delete[] R;

    return result;
}
/*
int main()
{
    const int n = 4; // Liczba punktów danych

    long double x[n] = { 0.0, 1.0, 3.0, 4.0 }; // Przyk³adowe punkty x
    long double y[n] = { 1.0, 3.0, 2.0, 1.0 }; // Przyk³adowe wartoœci funkcji dla punktów x

    long double x0 = 2; // Przyk³adowy punkt, dla którego obliczamy wartoœæ przybli¿on¹

    long double result = nevilleInterpolation(x, y, n, x0);

    cout << "Wartosc przyblizona dla x = " << x0 << " wynosi: " << result << endl;

    return 0;
}*/
