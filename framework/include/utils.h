#ifndef D7066A8E_1A13_41A3_8EBB_6C6BE6395517
#define D7066A8E_1A13_41A3_8EBB_6C6BE6395517

#include <glad/gl.h>
#include <stdint.h>
#include <stdio.h>

typedef struct bmp_image {
    uint32_t width;
    uint32_t height;
    unsigned char* pixels;
} bmp_image_t;

int read_bmp(const char* path, bmp_image_t* bmp);

char* read_file(const char* path);
const char* get_gl_error_name(GLenum code);

#define CATCH_GL_ERRORS_AND(block)                                     \
    do {                                                               \
        GLenum err = glGetError();                                     \
                                                                       \
        if (err) {                                                     \
            while (err != GL_NO_ERROR) {                               \
                fprintf(stderr, "Caught %s ", get_gl_error_name(err)); \
                fprintf(stderr, " at %s:%d\n", __FILE__, __LINE__);    \
                err = glGetError();                                    \
            }                                                          \
            do {                                                       \
                block;                                                 \
            } while (0);                                               \
        }                                                              \
    } while (0)

#define CATCH_GL_ERRORS CATCH_GL_ERRORS_AND({})

#endif /* D7066A8E_1A13_41A3_8EBB_6C6BE6395517 */
