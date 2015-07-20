#ifndef VEC2
#define VEC2

#include<math.h>

#define DIMENSION 2

void sum(double *c, double *a, double *b)
{
	int i;
	for(i = 0; i < DIMENSION; i++)
		c[i] = a[i] + b[i];
}

void subtract(double *c, double *a, double *b)
{
	int i;
	for(i = 0; i < DIMENSION; i++)
		c[i] = a[i] - b[i];
}

double scalar(double *a, double *b)
{
	int i;
	double sum = 0.0f;
	for(i = 0; i < DIMENSION; i++)
		sum += a[i] * b[i];
	return sum;
}

void multiply(double *a, double b)
{
	int i;
	for(i = 0; i < DIMENSION; i++)
		a[i] *= b;
}

void divide(double *a, double b)
{
	int i;
	for(i = 0; i < DIMENSION; i++)
		a[i] /= b;
}

double module(double *a)
{
	int i;
	double tmp = 0.0f;
	for(i = 0; i < DIMENSION; i++)
		tmp += a[i] * a[i];
	return sqrt(tmp);
}

#endif
