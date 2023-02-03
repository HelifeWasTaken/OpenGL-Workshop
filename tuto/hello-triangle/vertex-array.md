# Creating a vertex array

You should now have a pair of shaders that are compiled and linked together to
form a shader program!

The next step will be to actually feed data to our program! The graphics
pipeline starts with the _Vertex Shader_, so we have to provide it _per-vertex
data_. We do so by creating what is called a _Vertex Array_ (makes sense,
right?).

Our triangle is made up of three vertices, so we will need three entries in our
vertex array. In the following table, each line represents a vertex in our
vertex array:

| X position | Y position |
| :--------: | :--------: |
|   `-0.5`   |   `-0.5`   |
|   `0.0`    |   `0.5`    |
|   `0.5`    |   `-0.5`   |

A vertex can have any sort of data associated with it, not just its position!
For instance, we can associate a colour to each vertex:

| X position | Y position |  Red  | Green | Blue  |
| :--------: | :--------: | :---: | :---: | :---: |
|   `-0.5`   |   `-0.5`   | `1.0` | `0.0` | `0.0` |
|   `0.0`    |   `0.5`    | `0.0` | `1.0` | `0.0` |
|   `0.5`    |   `-0.5`   | `0.0` | `0.0` | `1.0` |

## Buffers

In OpenGL, as with many other graphics API, a vertex array doesn't directly hold
the data associated with each vertex. Instead, a one-dimensional generic data
structure called a "buffer" is used to store arbitrary data that can then be
used to construct a vertex array.

Keeping the example above, we could have a buffer storing 2D vertex positions:

|  X1   |  Y1   |   X2   |  Y2   |  X3   |   Y3   |
| :---: | :---: | :----: | :---: | :---: | :----: |
| `0.0` | `0.5` | `-0.5` | `0.5` | `0.5` | `-0.5` |

Because buffers are one-dimensional data structures, vertex coordinates have to
be stored in an interleaved layout (`X1, Y1, X2, Y2, ...XN, YN`).

OpenGL provides a couple functions to manipulate buffers:

- [`glGenBuffers`]: to create buffers
- [`glDeleteBuffers`]: to destroy buffers
- [`glBufferData`]: to set the buffer contents
- [`glBindBuffer`]: to "bind" buffers (more on that in the next section)

### The OpenGL state machine

When programming with the OpenGL API, you will encounter many `glBind*`
functions. This is because OpenGL was designed around the concept of a "state
machine" where objects must be bound before being manipulated. In other words,
**you cannot use [`glBufferData`] before having bound your buffer with
[`glBindBuffer`]**:

```c
// first, bind the buffer...
glBindBuffer(GL_ARRAY_BUFFER, my_buffer);
// now that it is the current GL_ARRAY_BUFFER, you can set its data!
glBufferData(GL_ARRAY_BUFFER, /* ... */);
```

> **Pay attention to the arguments of [`glBufferData`]!** Look it up... None of
> them corresponds _directly_ to the buffer ID you want to manipulate.

### Buffers: checkpoint

Back to code! Create the following buffers for the vertex array we will be
creating in the next section:

|   X1   |   Y1   |  X2   |  Y2   |  X3   |   Y3   |
| :----: | :----: | :---: | :---: | :---: | :----: |
| `-0.5` | `-0.5` | `0.0` | `0.5` | `0.5` | `-0.5` |

|  R1   |  G1   |  B1   |  R2   |  G2   |  B2   |  R3   |  G3   |  B3   |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `1.0` | `0.0` | `0.0` | `0.0` | `1.0` | `0.0` | `0.0` | `0.0` | `1.0` |

The first one will contain vertex coordinates, and the second will contain
vertex colours. The data they contain should be an array of `float`s.

> Don't forget to delete the buffers at the end of your program!

## Constructing the vertex array

You should now have two buffers created, one containing 2D coordinates and the
other containing colours. The last step of the process is to actually build a
vertex array from that data! You can generate an empty vertex array with
[`glGenVertexArrays`].

Remember the shaders you wrote? In your vertex shader, input variables denoted
with the `in` keyword correspond to _vertex attributes_. Each attribute in a
shader has a unique location that can be specified with
`layout(location = ...)`. When created with [`glGenVertexArrays`], vertex arrays
don't have any attributes: you must enable each location with
[`glEnableVertexAttribArray`].

> Don't forget to bind the vertex array with [`glBindVertexArray`] before
> manipulating it!

Now that you have enabled each vertex attribute location, the last step is to
specify where the data is, and the answer is... in the buffers of course!

However, the buffers we created don't hold any information regarding the format
in which our data is stored: it's just an array of raw bytes. The vertex shader
expects more sophisticated data types, such as single-precision floating-point
vectors for example.

Thankfully, [`glVertexAttribPointer`] lets us specify all of that with a single
function call (minus the call to [`glBindBuffer`])! Its `index` parameter
corresponds to the attribute location you want to assign data to.

In the end, the code to build the vertex array should look like this:

```c
// create the coordinates buffer:
glGenBuffers(...);
glBindBuffer(...);
glBufferData(...);

// same for the buffer storing vertex colours:
/* ... */

// create the vertex array:
glGenVertexArrays(...);
glBindVertexArray(...);

// bind one of the buffer to the vertex attribute it corresponds to:
glEnableVertexAttribArray(...);
glBindBuffer(...);
glVertexAttribPointer(...);

// then do the same for the other attribute!
/* ... */
```

> [`glGenBuffers`] can be used to create several buffers at the same time!

And that's all you need to render a triangle! Well, almost... In the next
chapter, we will put together everything we've done so far to finally get
something rendered on the screen!

[`glgenbuffers`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
[`gldeletebuffers`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml
[`glbufferdata`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
[`glbindbuffer`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
[`glgenvertexarrays`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
[`glenablevertexattribarray`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
[`glbindvertexarray`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
[`glvertexattribpointer`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
