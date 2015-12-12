#include "update_particle.h"
void swap_ptr(double*** a, double*** b)
{
  double** tmp = *a;
  *a = *b;
  *b = tmp;
}

  
int update_particle_boris(Particles* P, Parameter* para)
{
  /* try out restrict keyword to increase performance */
  // use boris method to update particle
  int i,j,k;
  int d = P->dim;  
  /* test field */
  for (j = 0; j < P->particle_num; ++j)
  {
    P->bfield[d*j+2] = 1.0;
    P->bfield_1[d*j+2] = 1.0;        
  }
  /* test field */
  swap_ptr(&(P->pos),&(P->pos_1));
  swap_ptr(&(P->vel),&(P->vel_1));  

  double u_minus [3] = {0.0, 0.0, 0.0};
  double u_plus [3] = {0.0, 0.0, 0.0};
  double u_prime [3] = {0.0, 0.0, 0.0};
  double t_t [3] = {0.0, 0.0, 0.0};

  for (i = 0; i < P->species_num; ++i)
    for (j = 0; j < P->particle_num; ++j)
    {
      for (k = 0; k < d; ++k)
        u_minus[k] = P->vel_1[i][d*j+k]+P->species[i].charge*para->dt*P->efield[d*j+k]/(2.0*P->species[i].mass);
      
      for (k = 0; k < d; ++k)
      {
        double gamma = sqrt(1+inner_product(d,&(P->vel_1[i][d*j]),&(P->vel_1[i][d*j]))/(C*C));
        double blen = vector_len(d,&(P->bfield[d*j]));
        double x = P->species[i].charge*para->dt*blen/(2.0*gamma*P->species[i].mass);
        t_t[k] = P->bfield[d*j+k]/blen * tan(x);
      }
      outer_product(u_minus,t_t,u_prime);
      for (k = 0; k < d; ++k)
        u_prime[k] += u_minus[k];
      

      double coef = 2.0/(1+inner_product(d,t_t,t_t));
      for (k = 0; k < d; ++k)
        t_t[k] = t_t[k]*coef;

      outer_product(u_prime,t_t,u_plus);
      for (k = 0; k < d; ++k)
        u_plus[k] += u_minus[k];      
      for (k = 0; k < d; ++k)      
        P->vel[i][d*j+k] = u_plus[k] + P->species[i].charge*para->dt*P->efield[d*j+k]/(2.0*P->species[i].mass);
      double gamma = sqrt(1+inner_product(d,&(P->vel[i][d*j]),&(P->vel[i][d*j]))/(C*C));      
      for (k = 0; k < d; ++k)                  
        P->pos[i][d*j+k] = P->pos_1[i][d*j+k] + P->vel[i][d*j+k]*para->dt/gamma;
    }
  return 0;
}

