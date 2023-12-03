#include <main.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
      return 1;

  // GL 3.0 + GLSL 130
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
  if (window == nullptr)
      return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  init_imgui(window);

  static float height = 0.0;
  imgui_add_f_slider("Height", &height, 0.0, 1.0);
  static float width = 0.0;
  imgui_add_f_slider("Width", &width, 0.0, 10.0);
  static float depth = 0.0;
  imgui_add_f_slider("Depth", &depth, -1.0, 1.0);

  static int a1 = 0;
  imgui_add_i_slider("1", &a1, 0, 10);
  static int a2 = 0;
  imgui_add_i_slider("2", &a2, 0, 1000);
  static int a3 = 0;
  imgui_add_i_slider("3", &a3, -10, 10);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard
    // flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse
    //   input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch
    //   keyboard input data to your main application, or
    //   clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and
    // hide them from your application based on those two flags.
    glfwPollEvents();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45, 0.55, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    render_imgui();

    glfwSwapBuffers(window);
  }

  imgui_cleanup();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
