/**
 * @file euler.c
 *
 * @brief This numerical code solves a ordinary differential equation (ODE)
 * using the Euler method
 *
 * If we have the following ODE:
 *
 * df(x)/dx = F(f,x) ------- (e.g. cos(x),...)
 * 
 * the Euler method consists on approximate the value of f following this
 * formula
 *
 * f(x_0 + Dx) = f(x_0) + df(x)/dx |_(x_0) Dx 
 *             = f(x_0) +    F(f(x_0),x_0) Dx
 *             = f_0    +       F(f_0,x_0) Dx
 *
 * if x_0 and f(x_0) are known values.
 *
 * @author Alejandro Aguayo-Ortiz
 *
 * @date 28-05-2020 - 17:17:44
 *
 * E-mail: aaguayoo92@ciencias.unam.mx
 *
 * Created on: 28-05-2020 - 17:16:34
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>
#include<math.h>
#include"header.h"

int main(int argc, char *argv[])
{
   /**
    * The numerical resolution N
    */
   int N;
   N = 500;

   /**
    * We have to define a numerical domain
    *    Xmax = 3.141592.../2.0
    *    Xmin = 0
    *
    * and the size step Dx
    */
   double Xmin, Xmax;
   double Dx;
   Xmin = 0.0;
   Xmax = M_PI_2;

   Dx = (Xmax - Xmin)/N;

   /**
    * Initial/boundary point x_0, f_0 = f(x_0)
    */
   double x_0, f_0;
   x_0 = Xmin;
   f_0 = 0.0;

   /**
    * Compute the numerical domain vector X
    */
   double *X;
   X = (double *)malloc((N+1)*sizeof(double));

   for(int i = 0; i <= N; i++)
   {
      /**
       * The i-th position of vector X, i.e., X_i
       */
      X[i] = Xmin + i*Dx;
   }

   /**
    * Define the solution vector f
    */
   double *f;
   f = (double *)malloc((N+1)*sizeof(double));

   /**
    * Implement the Euler method
    */
   f[0] = f_0;

   for(int i = 1; i <= N; i++)
   {
      f[i] = f_0 + F(f_0,x_0)*Dx;

      x_0 = X[i];
      f_0 = f[i];
   }

   /**
    * Print solution
    */
   for(int i = 0; i <= N; i++)
   {
      printf("%f %f\n",X[i],f[i]);
   }

   return 0;
}
