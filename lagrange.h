#ifndef LAGRANGE_H
#define LAGRANGE_H
#include"Interval.h"

long double lagrange_wartosc_wielomianu(long double* wspolczynniki, int stopien, long double x);
long double * lagrange_wspolczynniki_wielomianu(long double* X, long double* tabFx, int laczna_liczba_wezlow, long double* wspolczyn);
interval_arithmetic::Interval<long double> lagrange_wartosc_wielomianu_interv(interval_arithmetic::Interval<long double>* wspolczynniki, int stopien, interval_arithmetic::Interval<long double> x);
interval_arithmetic::Interval<long double> * lagrange_wspolczynniki_wielomianu_interv(interval_arithmetic::Interval<long double>* X, interval_arithmetic::Interval<long double>* tabFx, int laczna_liczba_wezlow, interval_arithmetic::Interval<long double>* wspolczyn);

#endif // LAGRANGE_H
