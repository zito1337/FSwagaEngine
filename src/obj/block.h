#ifndef BLOCK_H
#define BLOCK_H
#include "cglm/cglm.h"

float block_vertices[];
vec3 block_pos;

void spawn_block(vec3 spawn_pos);
void remove_block();

#endif