#ifndef PARAMETER_H
#define PARAMETER_H
typedef struct
{
  double dt;//timestep.
  int stepnum;//simulation step number.
  int period;// dump data every period step.
  int dim;//dimension
  int* N;//an array of cell number
  double* size;//an array of cell number  
}Parameter;
#endif
