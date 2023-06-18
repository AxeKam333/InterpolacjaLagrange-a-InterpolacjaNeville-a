#ifndef NEVILL_H
#define NEVILL_H
#include"Interval.h"

long double neville_wartosc_wielomianu(long double* x, long double* y, int n, long double x0);
interval_arithmetic::Interval<long double> neville_wartosc_wielomianu_interv(interval_arithmetic::Interval<long double>* x, interval_arithmetic::Interval<long double>* y, int n, interval_arithmetic::Interval<long double> x0);

#endif // NEVILL_H
