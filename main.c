#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void create_world(int *array, int x_size, int y_size);
void update(int *array, int x_size, int y_size);
bool rand_bool();
int get_value(int *array, int x, int y, int y_size);
void draw(int *array, int x_size, int y_size);

int main()
{
    int x_size = 20;
    int y_size = 20;
    int array[x_size * y_size];
    create_world(array, x_size, y_size);

    for (;;)
    {

        draw(array, x_size, y_size);
        sleep(1);
        update(array, x_size, y_size);
    }
    free(array);
}

void update(int *array, int x_size, int y_size)
{
    int i;

    for (i = 0; i < x_size * y_size; ++i)
    {

        if (array[i] == 0)
        {
            array[i] = 1;
        }
        else
        {
            array[i] = 0;
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

void draw(int *array, int x_size, int y_size)
{
    int i;
    for (i = 0; i < x_size * y_size; ++i)
    {

        if (i % x_size == 0)
        {

            printf("\n");
        }

        printf("%d ", array[i]);
    }
    printf("\n");
}

int get_value(int *array, int x, int y, int y_size)
{

    return array[x * y_size + y];
}
