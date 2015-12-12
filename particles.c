#include "particles.h"
int particles_init(Particles* P, int s_num, int p_num, int d)
{
  int i,j;  
  int ret = 0;//return value
  P->species_num = s_num;
  P->particle_num = p_num;
  P->dim = d;
  
  P->pos = (double**) calloc (s_num,sizeof(double*));
  P->vel = (double**) calloc (s_num,sizeof(double*));
  P->pos_1 = (double**) calloc (s_num,sizeof(double*));
  P->vel_1 = (double**) calloc (s_num,sizeof(double*));

  P->efield = (double*) calloc (p_num*d,sizeof(double*));
  P->bfield = (double*) calloc (p_num*d,sizeof(double*));
  P->efield_1 = (double*) calloc (p_num*d,sizeof(double*));
  P->bfield_1 = (double*) calloc (p_num*d,sizeof(double*));
  
  /* initialize species */
  // TODO: read from configuration file
  P->species = (Species*) malloc(s_num*sizeof(Species));
  P->species[0].mass = 1.0;
  P->species[0].charge = 1.0;
  
  double** tmp [] = {P->pos,P->vel,P->pos_1,P->vel_1};
  int tmp_len = 4;

  for (j=0;j<tmp_len;j++)
  {
    for (i=0;i<s_num;i++)
    {
      tmp[j][i] = (double*) calloc (p_num*d,sizeof(double));
      if (tmp[j][i] == NULL)
      {
        ret = 1;
        goto end;
      }
    }
  }
  
 end:
  // error handling
  if (ret == 1)
  {
    printf ("%s\n","malloc error in Particles_init()");
    for (i=0;i<4;i++)
      for (j=0;j<s_num;j++)
        if(tmp[i][j] != NULL)
          free(tmp[i][j]);
  }
  return ret;
}

int particles_print(Particles* P)
{
  int i,j;
  /* printf ("%s\n","--------------------");       */
  /* int i,j; */
  /* for (i=0;i<P->species_num;i++) */
  /* { */
  /*   printf ("%s %d\n","species ",i); */
  /*   species_print(&(P->species[i])); */
  /*   printf ("%s\n","--------------------");     */
  /* } */
  
  //printf ("%s\n","Print out all particles");

  for (i=0;i<P->species_num;i++)
  {
    printf ("%s %d\n","species",i);
    if (P->dim == 3)
      for (j=0;j<P->particle_num;j++)
        printf ("%5d: p:%10e %10e %10e v:%10e %10e %10e \n",j,P->pos[i][3*j],P->pos[i][3*j+1],P->pos[i][3*j+2],P->vel[i][3*j],P->vel[i][3*j+1],P->vel[i][3*j+2]);
    if (P->dim == 2)
      for (j=0;j<P->particle_num;j++)
        printf ("%5d: p:%10e %10e v:%10e %10e \n",j,P->pos[i][2*j],P->pos[i][2*j+1],P->vel[i][2*j],P->vel[i][2*j+1]);
    printf ("%s\n","------------------------------------------------------------------------");    
  }
  
  return 0;
}

extern int species_print(Species* S)
{
  printf ("%s %e %s\n","mass:",S->mass,"kg");
  printf ("%s %e %s\n","charge:",S->charge,"C");
  return 0;
}
