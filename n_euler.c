/**
 * @file n_euler.c
 *
 * @brief This numerical code solves a set of ordinary differential equations (ODEs)
 * using the Euler method
 *
 * If we have the following ODE:
 *
 * df_1(x)/dx = F_0(f_1,...,f_n,x) ------- (e.g. cos(x),...)
 *  .
 *  .
 *  .
 * df_N(x)/dx = F_N(f_1,...,f_n,x) ------- (e.g. sin(x),...)
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

#define f(n,i) f[(n)*(Nx+1) + (i)] 

int main(int argc, char *argv[])
{
   /**
    * The numerical resolution N
    */
   int Nx;
   Nx = 500;

   /**
    * The number of ODEs
    */
   int Node;
   Node = 3;

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

   Dx = (Xmax - Xmin)/Nx;

   /**
    * Initial/boundary point x_0, f_0 = f(x_0)
    */
   double *f_0;
   double x_0;
   f_0 = (double *)malloc((Node+1)*sizeof(double));
   x_0 = Xmin;

   f_0[0] = 1.0;
   f_0[1] = 1.0;
   f_0[2] = 1.0;

   /**
    * Compute the numerical domain vector X
    */
   double *X;
   X = (double *)malloc((Nx+1)*sizeof(double));

   for(int i = 0; i <= Nx; i++)
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
   f = (double *)malloc((Node)*(Nx+1)*sizeof(double));

   /**
    * Implement the Euler method
    */
   f(0,0) = f_0[0];
   f(1,0) = f_0[1];
   f(2,0) = f_0[2];

   for(int i = 1; i <= Nx; i++)
   {
      f(0,i) = f_0[0] + F_0(f_0,x_0)*Dx;
      f(1,i) = f_0[1] + F_1(f_0,x_0)*Dx;
      f(2,i) = f_0[2] + F_2(f_0,x_0)*Dx;

      x_0 = X[i];

      f_0[0] = f(0,i);
      f_0[1] = f(1,i);
      f_0[2] = f(2,i);
   }

   /**
    * Print solution
    */
   for(int i = 0; i <= Nx; i++)
   {
      printf("%f %f %f %f\n",X[i],f(0,i),f(1,i),f(2,i));
   }

   return 0;
}
