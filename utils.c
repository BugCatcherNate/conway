#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

const char *loadFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return NULL; // Return NULL to indicate an error
    }

    // Find the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char *file_content = (char *)malloc(file_size + 1);

    if (file_content == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL; // Return NULL to indicate an error
    }

    // Read the file content
    size_t bytes_read = fread(file_content, 1, file_size, file);
    file_content[bytes_read] = '\0'; // Null-terminate the string

    fclose(file);
    return file_content; // Return the file content as a string
}

// Matrix Math
void mat4_identity(float matrix[16])
{
    for (int i = 0; i < 16; i++)
    {
        matrix[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}

void mat4_translate_in_place(float matrix[16], float x, float y, float z)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
}
