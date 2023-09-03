#ifndef UTILS_H
#define UTILS_H

const char *loadFile(const char *filename);
void mat4_translate_in_place(float matrix[16], float x, float y, float z);
void mat4_identity(float matrix[16]);

#endif