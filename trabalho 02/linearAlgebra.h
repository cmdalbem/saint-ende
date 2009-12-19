#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__

#include "definitions.h"

Point spatialTransform(float *c, Point p);

float** mallocMatrix(int a,int b);
void freeMatrix(float **matrix);

void printMatrix(float **matrix, int a, int b);

float* solve(float **linSys, int a,int b);
#endif /* __LINEAR_ALGEBRA_H__ */

