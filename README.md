# imgui_c_wrapper
An extremely stripped down C wrapper for [imgui](https://github.com/ocornut/imgui)

## Features
Currently only provides a means for adding sliders in C programs which use GLFW and OpenGL

## Compilation
To compile the shared library, run the following command from within the projects root directory
`make lib`
This will create a `libimgui_wrapper.so` file in the projects directory. Link against this library in your application. The matching headers for this library can be found in `include/imgui_wrapper.h`

## Usage
- Upon GLFW window creation, initialize imgui via the `init_imgui()` function
- Add any sliders via the `imgui_add_[f,i]_slider()` functions
- In the main rendering loop of your program, call `render_imgui()`
- At the end of the application, call `imgui_cleanup()`

### Example
```
// During window initialization
glfwInit();
...
GLFWwindow *window = glfwCreateWindow(...);
...
init_imgui(window);

...
// Add sliders
imgui_add_f_slider("height", &height, 0.0, 1.0);
...
// During the main rendering loop
while (!glfwWindowShouldClose(window)) {
  ...
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // Render scene
  ...
  render_imgui();
  ...

  glfwSwapBuffers(window);
  glfwPollEvents();
}

...
imgui_cleanup();
glfwTerminate();
```
