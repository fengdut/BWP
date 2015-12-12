#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
extern inline double inner_product(int len,double* a, double* b);
extern inline void outer_product(double* a, double *b, double* c);
extern inline double vector_len(int len, double* a);
#endif
