# Clearing the screen

Right now, your window probably doesn't show anything exciting yet. Let's change
that!

Use [`glClear`] and [`glClearColor`] to clear the framebuffer of your window
using the colour of your choice! Do it in the `render` function callback to
clear the screen every time before anything gets drawn.

![A cleared window](./res/win_clear.png) _I went with some dark shade of grey._

## Links

- [OpenGL 4 Reference Pages][opengl-refpages] - the official documentation
- [docs.gl] - a nicer documentation, though unofficial

[opengl-refpages]: https://www.khronos.org/registry/OpenGL-Refpages/gl4/
[docs.gl]: http://docs.gl
[`glclear`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClear.xhtml
[`glclearcolor`]:
  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearColor.xhtml
