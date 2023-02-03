# Your own shader program

Finally, the time has come! The time for what you ask? Well, to write your very
own pair of GLSL shaders of course!

You might be wondering what I'm talking about, so let's reiterate, shall we?

## What is a shader?

Shaders are pieces of software that run on your GPU. They are used to perform
specialised calculations based on a set of inputs in parallel. They are written
in a language specific to the graphics API you're using. The _OpenGL Shading
Language_, abbreviated as _GLSL_, is the one we're going to use today.

> Don't worry! GLSL is actually very close to C! It just comes with fancy
> features that make it easier to write shaders: types such as `vec2`, `vec3`,
> `vec4` to represent vectors and built-in mathematical functions like
> `distance`, `normalize` and `cross`.

Depending on their role in the graphics pipeline, shaders can take several
names:

### Vertex shaders

The first step when rendering anything, is to give a position to each vertex.
This is exactly what the _vertex shader_ is for! It is executed once for each
vertex, to calculate its coordinates on screen. Typically, this is where you
would apply transformations and 3D projections.

```glsl
#version 330 core

layout(location = 0) in vec2 a_Position;

void main() {
    gl_Position = vec4(a_Position, 0.0, 1.0);
}
```

Here are a couple things to note about this example shader:

- It written in GLSL 3.30 and uses the `core` API profile (the profile we're
  using).
- It has a single input: `a_Position`, a 2D vector. The `layout(location = 0)`
  part just means "this is input #0".
- It constructs a 4D vector from `a_Position` and stores it into `gl_Position`.
  The `z` component is set to `0.0` and `w` (the fourth component) is set to
  `1.0`.

The main output of our vertex shader is the `gl_Position` variable, holding the
coordinates of a single point of the geometry we're drawing on screen!

> You might wonder why `gl_Position` is a `vec4` instead of a `vec2` or a
> `vec3`. This has to do with something called [homogeneous coordinates]. Don't
> worry too much about it for now, just keep in mind that `w` should be set to
> `1.0`!

[homogeneous coordinates]: https://en.wikipedia.org/wiki/Homogeneous_coordinates

The inputs of a vertex shader can be anything you want! For example, you could
keep it simple and just feed it plain 2D coordinates like in the example above.
But you could also feed it 3D coordinates and matrices, and let it do the math
to figure out the final 2D position! Don't worry, your GPU _loves_ doing math.

#### Exercise: compiling a vertex shader

To create a shader, you can use [`glCreateShader`]. Once created, you can load
the GLSL source code with [`glShaderSource`] and compile it with
[`glCompileShader`]. To make it easier for you to write your shaders in separate
files (typically `*.vs` for vertex shaders and `*.fs` for fragment shaders),
I've written a helper function to read a file in a heap-allocated string:

```c
char* source = read_file("./res/my_shader.vs");

GLuint shader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(shader, 1, &source, NULL);
glCompileShader(shader);

// don't forget to free the shader source string!
free(source);
```

Just don't forget to `#include "utils.h"` at the top of your C source file.

Try creating and compiling a vertex shader (for instance, the above example)
using those functions.

> You can use [`glGetShaderiv`] and [`glGetShaderInfoLog`] to see if your shader
> successfully compiled! Try inserting a syntax error and see if you can get a
> meaningful error message from it.

### Fragment (or pixel) shaders

After the vertex shader computed the positions of each triangle (GPUs can only
draw triangles), the next step is to actually fill them with colourful pixels!
Now, to decide what colour each pixel takes, another kind of shader is executed:
the _fragment shader_ (also known as _pixel shader_).

> Yes, it is executed for each individual pixel on screen. That means cycles are
> precious at this stage! Luckily, this is what modern GPUs are optimised for.

Unlike the vertex shader, you cannot _directly_ feed per-pixel input to your
fragment shader. However, you can pass variables from your vertex shader to your
fragment shader! Different values between two vertices will be linearly
interpolated.

```glsl
#version 330 core

// coming from an output of the vertex shader!
in vec3 v_Color;

// the final colour of the pixel!
out vec4 o_Color;

void main() {
    o_Color = vec4(v_Color, 1.0);
}
```

#### Exercise: compiling a fragment shader

Fragment shaders are compiled the exact same way as vertex shaders (don't forget
to specify `GL_FRAGMENT_SHADER` when creating it though).

> Because of how similar it is to compile vertex and fragment shaders, maybe you
> could write a helper function to do it for you...

## A complete shader program

You now have a vertex shader and a fragment shader compiled! It's now time to
link them together, just like you would link two object files together to get a
full program.

The function to do that is conveniently called [`glLinkProgram`]. Use it to link
a shader program for the two shaders you have compiled.

> Just like compilation, linkage can fail! You can use [`glGetProgramiv`] and
> [`glGetProgramInfoLog`] to get information about any error that occurred when
> linking your shaders.

Did it successfully link? In your vertex shader, add an input similar to
`a_Position` called `a_Color`, and pass its value to the fragment shader using
an `out` variable (they must share the same name in the two shaders).

[`glcreateshader`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
[`glshadersource`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
[`glcompileshader`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCompileShader.xhtml
[`glgetshaderiv`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetShader.xhtml
[`glgetshaderinfolog`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml
[`gllinkprogram`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
[`glgetprogramiv`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
[`glgetprograminfolog`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
