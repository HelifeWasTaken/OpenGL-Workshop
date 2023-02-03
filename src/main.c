#include "framework.h"
#include <glad/gl.h>

/* Create shaders, buffers, vertex arrays, and other resources here */
static int init()
{
    // Return 0 on success
    return 0;
}

/* Render everything! */
static void render()
{
}

/* Destroy everything! */
static void cleanup()
{
}

/* Start everything! You shouldn't have to modify the main function. */
int main()
{
    workshop_on_init(init);
    workshop_on_render(render);
    workshop_on_cleanup(cleanup);

    return workshop_start("less gooo", 640, 480);
}
