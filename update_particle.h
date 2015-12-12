#ifndef UPDATE_PARTICLE_H
#define UPDATE_PARTICLE_H
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "particles.h"
#include "parameter.h"
extern int update_particle_boris(Particles* P, Parameter* para);
extern int update_particle(Particles* P, Parameter* para);
#endif
