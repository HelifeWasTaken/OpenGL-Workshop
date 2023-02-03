#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <stdio.h>
#include <stdlib.h>

#include "framework.h"
#include "utils.h"

init_cb_t* user_init_callback = NULL;
render_cb_t* user_render_callback = NULL;
update_cb_t* user_update_callback = NULL;
cleanup_cb_t* user_cleanup_callback = NULL;

/**
 * @brief Set the callback function to be called on app initialisation.
 *
 * No OpenGL API call may be performed outside of the callback function!
 */
void workshop_on_init(init_cb_t* fn)
{
    user_init_callback = fn;
}

/**
 * @brief Set the callback function to be called on app update.
 *
 * No OpenGL API call may be performed outside of the callback function!
 */
void workshop_on_update(update_cb_t* fn)
{
    user_update_callback = fn;
}

/**
 * @brief Set the callback function to be called on app render.
 *
 * No OpenGL API call may be performed outside of the callback function!
 */
void workshop_on_render(render_cb_t* fn)
{
    user_render_callback = fn;
}

/**
 * @brief Set the callback function to be called on app cleanup.
 *
 * No OpenGL API call may be performed outside of the callback function!
 */
void workshop_on_cleanup(cleanup_cb_t* fn)
{
    user_cleanup_callback = fn;
}

static void on_glfw_error(int error, const char* description)
{
    fprintf(stderr, "GLFW error: %s\n", description);
}

static void on_window_resize(GLFWwindow* win, int w, int h)
{
    glViewport(0, 0, w, h);
}

/**
 * @brief Run the application.
 *
 * A new window with the given dimensions and title is created along with an
 * OpenGL context. No OpenGL function calls may be performed before this
 * function is called!
 *
 * @param title
 * @param width
 * @param height
 * @return int Zero on success, any non-zero value on error.
 */
int workshop_start(const char* title, int width, int height)
{
    // Setup the error callback to be notified of any GLFW error
    glfwSetErrorCallback(on_glfw_error);

    // Initialize GLFW
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    // Set the OpenGL context version and profile: 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    GLFWwindow* win = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!win) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make the GL context current
    glfwMakeContextCurrent(win);

    // Load OpenGL function pointers
    gladLoadGL(glfwGetProcAddress);

    // Enable vertical synchronization
    glfwSwapInterval(1);

    // Set the GL viewport to match the window's framebuffer size
    glViewport(0, 0, width, height);

    glfwSetWindowSizeCallback(win, on_window_resize);

    CATCH_GL_ERRORS_AND({
        glfwDestroyWindow(win);
        glfwTerminate();
        return EXIT_FAILURE;
    });

    // Call user's initialization routine
    if (user_init_callback) {
        int err = user_init_callback();

        if (err) {
            glfwDestroyWindow(win);
            glfwTerminate();
            return err;
        }
    }

    // Values used for timing calculations
    double last_start_time = glfwGetTime();
    double delta_time = 0.0;

    // Game loop!
    while (!glfwWindowShouldClose(win)) {
        double start_time = glfwGetTime();
        delta_time = start_time - last_start_time;
        last_start_time = start_time;

        // Process events
        double sleep_for = 1.0 / 200.0 - delta_time;
        glfwWaitEventsTimeout(sleep_for > 0 ? sleep_for : 0);

        // Call user's update routine
        if (user_update_callback) {
            user_update_callback(delta_time);
        }

        // Call user's rendering routine
        if (user_render_callback) {
            user_render_callback();
        }

        // Present our rendered image to the screen
        glfwSwapBuffers(win);
    }

    // Call user's cleanup routine
    if (user_cleanup_callback) {
        user_cleanup_callback();
    }

    // Destroy the window, terminate GLFW and exit successfully
    glfwDestroyWindow(win);
    glfwTerminate();

    return EXIT_SUCCESS;
}
