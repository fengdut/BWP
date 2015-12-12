#include "vector.h"
inline double inner_product(int len, double* a, double* b)
{
  int i;
  double sum = 0.0;
  for (i=0;i<len;i++)
    sum += a[i]*b[i];
  return sum;
}

inline void outer_product(double* a, double* b, double* c)
{
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - b[2]*a[0];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

inline double vector_len(int len, double* a)
{
  double sum = 0.0;
  int i;
  for (i = 0; i < len; ++i)
    sum += a[i]*a[i];
  return sqrt(sum);
}

