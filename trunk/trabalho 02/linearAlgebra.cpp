#include "linearAlgebra.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;

float** mallocMatrix(int a,int b)
{
    //alocando 'a' linhas
    float **matrix = (float**) malloc(a * sizeof(float*));

    for(int i=0; i < a; ++i)
    {
        matrix[i] = (float*) malloc(b * sizeof(float));
    }

    return matrix;
}

void freeMatrix(float **matrix)
{

}

void printMatrix(float **matrix, int a, int b)
{
    for (int i=0; i < a; ++i)
    {
        for (int j=0; j < b; ++j)
            cout << "|" << matrix[i][j] << "|";
        cout << endl;
    }
}

float* solve(float **linSys, int a, int b)
{
    for (int i=0; i < a-1; ++i)
    {
        for (int j=i+1; j < a; ++j)
        {
            //testa para ver se o elemento já nao é 0
            if ( fabs(linSys[j][i]) >= EPSOLON)
            {
                float mult = - linSys[i][i] / linSys[j][i];

                for (int k=i; k < b; ++k)
                {
                    linSys[j][k] = (linSys[j][k] * mult) + linSys[i][k];
                }
            }
        }
    }

    //printMatrix(linSys,a,b);

    float *solution = (float*) malloc(a*sizeof(float));

    for (int i=a-1; i >= 0; --i)
    {
        float tempSolution = 0;

        for (int k=a-1; k > i; --k)
        {
            tempSolution += solution[k] * linSys[i][k];
        }

        solution[i] = (linSys[i][b-1] - tempSolution) / linSys[i][i];
    }

    return solution;
}

//assumes that c is correct and contain 8 coefficients
Point spatialTransform(float *c, Point p)
{
    Point p1;
    p1.x = c[0]*p.x + c[1]*p.y + c[2]*p.x*p.y + c[3];
    p1.y = c[4]*p.x + c[5]*p.y + c[6]*p.x*p.y + c[7];

    //cout << p1.x << " " << p1.y << " " << endl;
    return p1;
}

