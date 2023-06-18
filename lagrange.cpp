#include<iostream>
#include<iomanip>
#include <cmath>
#include"Interval.h"

using namespace std;
using namespace interval_arithmetic;

long double lagrange_wartosc_wielomianu(long double* wspolczynniki, int stopien, long double x) {
    long double wynik = 0;
    long double potega_x = 1;


    for (int i = stopien-1; i >= 0; i--) {
        wynik += wspolczynniki[i] * potega_x;
        potega_x *= x;
    }

    return wynik;
}

long double * lagrange_wspolczynniki_wielomianu(long double* X, long double* tabFx, int laczna_liczba_wezlow, long double* wspolczyn) {
    int n = laczna_liczba_wezlow;

    for (int i = 0; i < n; i++) {
        wspolczyn[i] = 0;
    }

    for (int i = 0; i < n; i++) { // dla kazdego bloku
        long double bloczek[1000];
        for (int z = 0; z < n; z++) {
            bloczek[z] = 0;
        }

        long double mnoznik = tabFx[i];
        bloczek[0] = 1.000;
        for (int j = 0; j < n; j++) { // dla kazdego wspolczynnika
            if (i != j) {
                for (int k = n - 1; k >= 0; k--) {
                    bloczek[k + 1] += bloczek[k] * (-X[j]);
                }
                mnoznik /= (1.000 * X[i] - X[j]);
            }
        }

        for (int j = 0; j < n; j++) {
            wspolczyn[j] += bloczek[j] * mnoznik;
        }
    }

    return wspolczyn;
}


interval_arithmetic::Interval<long double> lagrange_wartosc_wielomianu_interv(interval_arithmetic::Interval<long double>* wspolczynniki, int stopien, interval_arithmetic::Interval<long double> x) {
    interval_arithmetic::Interval<long double> wynik;
    wynik.a=0;
    wynik.b=0;
    Interval<long double> potega_x;
    potega_x.a=1.0;
    potega_x.b=1.0;

    for (int i = stopien-1; i >= 0; i--) {
        wynik = wynik + (wspolczynniki[i] * potega_x);
        potega_x = potega_x * x;
    }

    return wynik;
}

interval_arithmetic::Interval<long double> * lagrange_wspolczynniki_wielomianu_interv(interval_arithmetic::Interval<long double>* X, interval_arithmetic::Interval<long double>* tabFx, int laczna_liczba_wezlow, interval_arithmetic::Interval<long double>* wspolczyn) {
    int n = laczna_liczba_wezlow;

    for (int i = 0; i < n; i++) {
        wspolczyn[i].a =0.0;
        wspolczyn[i].b =0.0;
    }

    for (int i = 0; i < n; i++) { // dla kazdego bloku
        interval_arithmetic::Interval<long double> bloczek[1000];
        for (int z = 0; z < n; z++) {
            bloczek[z].a = 0.0;
            bloczek[z].b = 0.0;
        }

        interval_arithmetic::Interval<long double> mnoznik = tabFx[i];
        bloczek[0].a = 1.000;
        bloczek[0].b = 1.000;
        for (int j = 0; j < n; j++) { // dla kazdego wspolczynnika
            if (i != j) {
                for (int k = n - 1; k >= 0; k--) {
                    bloczek[k + 1] = bloczek[k + 1] + (bloczek[k] * (X[j]*(-1)));
                }
                mnoznik = mnoznik / (X[i] - X[j]);
            }
        }

        for (int j = 0; j < n; j++) {
            wspolczyn[j] =wspolczyn[j] +( bloczek[j] * mnoznik);
        }
    }

    return wspolczyn;
}


/*
int main() {
    int n;
    long double wart;
    cin >> n;
    cin >> wart;
    long double x[1000], y[1000], wyniki[1000],wspolczyn[1000];
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        cin >> x[i];
        cin >> y[i];
    }

    lagrange_wspolczynniki_wielomianu(x, y, n, wspolczyn);

    cout << "----\n";
    for (int i = 0; i < n; i++) {
        cout << wspolczyn[i] << "x^" << n - i - 1 << " ";
    }
    cout << "\n----\n";

    long double suma = lagrange_wartosc_wielomianu(wspolczyn,n,wart);

    cout << " = " << suma;
    return 0;
}*/
