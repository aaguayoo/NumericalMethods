/**
 * @file sir.c
 *
 * @brief This numerical code solves SIR Model set of ordinary differential
 * equations using the Euler method
 *
 * If we have the following ODE:
 *
 * dS/dt = - b * S * I
 *
 * dI/dt = + b * S * I - g * I
 *
 * dR/dt = + g * I
 * 
 * the Euler method consists on approximate the value of f following this
 * formula
 *
 * f(t_0 + Dt) = f(t_0) + df(t)/dt |_(t_0) Dt 
 *             = f(t_0) +    F(f(t_0),t_0) Dt
 *             = f_0    +       F(f_0,t_0) Dt
 *
 * if t_0 and f(t_0) are known values.
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

#define f(n,i) f[(n)*(Nt+1) + (i)] 

int main(int argc, char *argv[])
{
   /**
    * The numerical resolution N
    */
   int Nt;
   Nt = 500;

   int Node;
   Node = 3;

   /**
    * We have to define a numerical domain
    *    Tmax = 3.141592.../2.0
    *    Tmin = 0
    *
    * and the time step Dt
    */
   double Tmin, Tmax;
   double Dt;
   Tmin = 0.0;
   Tmax = 20.0;

   Dt = (Tmax - Tmin)/Nt;

   /**
    * Initial/boundary point t_0, f_0 = f(t_0)
    */
   double *f_0;
   double t_0;
   f_0 = (double *)malloc((Node+1)*sizeof(double));
   t_0 = Tmin;

   // Assume that S + I + R = 1

   f_0[0] = 0.9999; // S_0
   f_0[1] = 1 - f_0[0]; // I_0
   f_0[2] = 0.0; // R_0

   /**
    * Compute the numerical domain vector T
    */
   double *T;
   T = (double *)malloc((Nt+1)*sizeof(double));

   for(int i = 0; i <= Nt; i++)
   {
      /**
       * The i-th position of vector T, i.e., T_i
       */
      T[i] = Tmin + i*Dt;
   }

   /**
    * Define the solution vector f
    */
   double *f;
   f = (double *)malloc((Node)*(Nt+1)*sizeof(double));

   /**
    * Implement the Euler method
    */
   f(0,0) = f_0[0];
   f(1,0) = f_0[1];
   f(2,0) = f_0[2];

   for(int i = 1; i <= Nt; i++)
   {
      f(0,i) = f_0[0] + F_S(f_0,t_0)*Dt;
      f(1,i) = f_0[1] + F_I(f_0,t_0)*Dt;
      f(2,i) = f_0[2] + F_R(f_0,t_0)*Dt;

      t_0 = T[i];

      f_0[0] = f(0,i);
      f_0[1] = f(1,i);
      f_0[2] = f(2,i);
   }

   /**
    * Print solution
    */
   for(int i = 0; i <= Nt; i++)
   {
      printf("%f %f %f %f\n",T[i],f(0,i),f(1,i),f(2,i));
   }

   return 0;
}
