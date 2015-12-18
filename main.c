#include <stdio.h>
#include <stdlib.h>
#include "update_grid.h"
#include "update_particle.h"
#include "particles.h"
#include "parameter.h"
#include"input.h"
int init(Parameter*,Particles*);

int main (int argc, char *argv[])
{
  // boundary
  // collision
  // interpolation
  // update grid
  // calculate force
  // update particle and species
	read_input();
  Parameter para;
  Particles P;
  init(&para,&P);
  P.pos_1[0][0] = 1.0;
  P.pos_1[0][1] = -0.001;  
  P.vel_1[0][1] = -1.0;
  P.pos[0][0] = 1.0;
  P.vel[0][1] = -1.0;

  P.pos_1[0][3] = 1.0;
  P.pos_1[0][4] = -0.001;  
  P.vel_1[0][4] = -1.0;
  P.pos[0][3] = 1.0;
  P.vel[0][4] = -1.0;  
  
  printf ("%s\n","simplePIC");
  update_grid();
  int i;
  for (i = 0; i < 10000; ++i)
  {
  //particles_print(&P);  
  update_particle_boris(&P,&para);  
  } 

  return 0;
}

int init (Parameter* para, Particles* P)
{
  para->dt = 0.001;
  para->stepnum = 10;
  para->period = 1;
  para->dim = 3;
  /* add read file here */
  /* initialize Particles */
  if (particles_init(P,1,2,para->dim) != 0)
    exit(1);
  return 0;
}
