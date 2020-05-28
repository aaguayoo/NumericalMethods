/**
 * @file function.c
 *
 * @brief 
 *
 * @author Alejandro Aguayo-Ortiz
 *
 * @date 28-05-2020 - 18:24:29
 *
 * E-mail: aaguayoo92@ciencias.unam.mx
 *
 * Created on: 28-05-2020 - 17:24:57
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>
#include<math.h>
#include"header.h"

/**
 * This is the Right Hand Side (RHS) of the ODE
 */

double F(double f, double x)
{
   return cos(x);
}

double F_0(double *f, double x)
{
   return sin(x);
}

double F_1(double *f, double x)
{
   return x;
}

double F_2(double *f, double x)
{
   return cos(x);
}

double F_S(double *f, double x)
{
   // F_S = -b * S * I
   return - b * f[0] * f[1];
}

double F_I(double *f, double x)
{
   // F_I = + b * S * I - g * I
   return b * f[0] * f[1] - g * f[1];
}

double F_R(double *f, double x)
{
   // F_R = + g * I
   return g * f[1];
}
