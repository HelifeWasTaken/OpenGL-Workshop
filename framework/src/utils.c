#ifdef _MSC_VER
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "utils.h"
#include <errno.h>
#include <glad/gl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_bmp(const char* path, bmp_image_t* bmp)
{
    FILE* file = fopen(path, "r");

    if (!file) {
        char* msg = strerror(errno);
        fprintf(stderr, "Couldn't open file \"%s\": %s\n", path, msg);
        return 1;
    }

    uint32_t data_offset = 0;
    fseek(file, 0x0A, SEEK_SET);
    fread(&data_offset, 1, 4, file);

    uint32_t size[2];
    fseek(file, 0x12, SEEK_SET);
    fread(&size, 4, 2, file);

    unsigned char* data = calloc(size[0] * size[1] * 4, sizeof(char));
    fseek(file, data_offset, SEEK_SET);
    fread(data, 1, size[0] * size[1] * 4, file);

    fclose(file);

    bmp->width = size[0];
    bmp->height = size[1];
    bmp->pixels = data;
    return 0;
}

char* read_file(const char* path)
{
    long len = 0;
    char* data = NULL;
    FILE* file = fopen(path, "r");

    if (!file) {
        char* msg = strerror(errno);
        fprintf(stderr, "Couldn't open file \"%s\": %s\n", path, msg);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    data = calloc(len + 1, sizeof(char));
    if (data) {
        rewind(file);
        fread(data, sizeof(char), len, file);
    }
    fclose(file);
    return data;
}

const char* get_gl_error_name(GLenum code)
{
    switch (code) {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    default:
        return NULL;
    }
}
