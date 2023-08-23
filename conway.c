#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "conway.h"

// 2d matrix represented in a 1d array
void update(int *old_array, int *new_array, int x_size, int y_size)
{
    int i;

    for (i = 0; i < x_size * y_size; ++i)
    {
        int x;
        int y;
        get_coord(i, y_size, &x, &y);
        int n_state = get_neighbor_state(old_array, x, y, y_size);

        if (old_array[i] == 1)
        {
            if (n_state <= 1 || n_state >= 4)
            {
                new_array[i] = 0;
            }
            else if (n_state == 2 || n_state == 3)
            {

                new_array[i] = 1;
            }
            else
            {
                new_array[i] = 0;
            }
        }
        else
        {

            if (n_state == 3)
            {
                new_array[i] = 1;
            }
            else
            {
                new_array[i] = 0;
            }
        }
    }
}

void create_world(int *array, int x_size, int y_size)
{

    int i;

    for (i = 0; i < x_size * y_size; ++i)
    {
        bool b = rand_bool();
        if (b)
        {
            array[i] = 1;
        }
        else
        {
            array[i] = 0;
        }
    }
}

bool rand_bool()
{
    return rand() % 2 == 1;
}

int get_neighbor_state(int *array, int x, int y, int y_size)
{

    int total_n_alive = 0;
    int row = -1;
    int col = -1;
    for (int n = 0; n < 9; ++n)
    {

        if (row == 0 && col == 0)
        {
            total_n_alive += 0;
        }
        else
        {
            total_n_alive += get_value(array, x + row, y + col, y_size);
        }
        if (row == 1)
        {
            row = -1;
            col += 1;
        }
        else
        {
            row += 1;
        }
    }

    return total_n_alive;
}

void get_coord(int elem, int y_size, int *x, int *y)
{

    *x = elem % y_size;
    *y = elem / y_size;
}

int get_value(int *array, int x, int y, int y_size)
{
    if (x > y_size || x < 0)
    {
        return 0;
    }
    else if (y > y_size || y < 0)
    {
        return 0;
    }
    else
    {
        return array[y * y_size + x];
    }
}
