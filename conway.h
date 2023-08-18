#ifndef CONWAY_H
#define CONWAY_H

#include <stdbool.h>

void create_world(int *array, int x_size, int y_size);
void update(int *old_array, int *new_array, int x_size, int y_size);
void get_coord(int elem, int y_size, int *x, int *y);
bool rand_bool();
int get_value(int *array, int x, int y, int y_size);
int get_neighbor_state(int *array, int x, int y, int y_size);

#endif