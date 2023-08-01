#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int *create_world(int x_size, int y_size);
void update(int **array, int x_size, int y_size);
int get_value(int *array, int x, int y, int y_size);
void draw(int *array, int x_size, int y_size);

int main()
{
    int x_size = 20;
    int y_size = 20;
    int *array = create_world(x_size, y_size);

    for (;;)
    {


        draw(array, x_size, y_size);
        sleep(1);
        update(&array, x_size, y_size);
    }
    free(array);
}

void update(int **array, int x_size, int y_size)
{
    int i;

    int *new_array = (int *)malloc(x_size * y_size * sizeof(int));
    for (i = 0; i < x_size * y_size; ++i)
    {

        int * temp = &array[i]; 
        printf("%d", temp);
        if (temp == 0)
        {
            new_array[i] = 1;
        }
        else
        {
            new_array[i] = 0;
        }
    }

    free(*array);

    *array = (int *)malloc(x_size * y_size * sizeof(int));
 
    for (i = 0; i < x_size * y_size; ++i) {

        (*array)[i] = new_array[i];
    }

    free(new_array);

}

int *create_world(int x_size, int y_size)
{

    int i, j;
    x_size = 100;
    y_size = 5;

    int *array = (int *)malloc(x_size * y_size * sizeof(int));

    for (i = 0; i < x_size * y_size; ++i)
    {
        if (rand_bool())
        {
            array[i] = 1;
        }
        else
        {
            array[i] = 0;
        }
    }

    return array;
}

int rand_bool()
{

    if (rand() % 7 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

        printf("%d ", get_value(array, i / y_size, i % x_size, y_size));
    }
    printf("\n");
}

int get_value(int *array, int x, int y, int y_size)
{

    return array[x * y_size + y];
}
