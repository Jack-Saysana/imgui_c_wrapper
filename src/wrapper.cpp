#include <wrapper.h>

extern "C" {

int init_imgui(GLFWwindow *window) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  f_sliders = (F_SLIDER *) malloc(sizeof(F_SLIDER) * STARTING_BUFF_LEN);
  if (f_sliders == NULL) {
    fprintf(stderr, "imgui_wrapper: Unable to allocate slider buffer\n");
    return -1;
  }
  f_sliders_len = 0;
  f_sliders_size = STARTING_BUFF_LEN;

  i_sliders = (I_SLIDER *) malloc(sizeof(I_SLIDER) * STARTING_BUFF_LEN);
  if (i_sliders == NULL) {
    fprintf(stderr, "imgui_wrapper: Unable to allocate slider buffer\n");
    return -1;
  }
  i_sliders_len = 0;
  i_sliders_size = STARTING_BUFF_LEN;

  return 0;
}

void render_imgui() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Input");
  for (size_t i = 0; i < f_sliders_len; i++) {
    ImGui::SliderFloat(f_sliders[i].label, f_sliders[i].val, f_sliders[i].lower, f_sliders[i].upper);
  }
  for (size_t i = 0; i < i_sliders_len; i++) {
    ImGui::SliderInt(i_sliders[i].label, i_sliders[i].val, i_sliders[i].lower, i_sliders[i].upper);
  }
  ImGui::End();

  // Rendering
  ImGui::Render();

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_cleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

int imgui_add_f_slider(const char *label, float *val, float lower, float upper) {
  if (f_sliders == NULL) {
    return -1;
  }

  f_sliders[f_sliders_len].label = label;
  f_sliders[f_sliders_len].val = val;
  f_sliders[f_sliders_len].lower = lower;
  f_sliders[f_sliders_len].upper = upper;
  f_sliders_len++;
  if (f_sliders_len == f_sliders_size) {
    f_sliders_size *= 2;
    f_sliders = (F_SLIDER *) realloc(f_sliders, sizeof(F_SLIDER) * f_sliders_size);
    if (f_sliders == NULL) {
      f_sliders_size /= 2;
      f_sliders_len--;
      return -1;
    }
  }

  return 0;
}

int imgui_add_i_slider(const char *label, int *val, int lower, int upper) {
  if (i_sliders == NULL) {
    return -1;
  }

  i_sliders[i_sliders_len].label = label;
  i_sliders[i_sliders_len].val = val;
  i_sliders[i_sliders_len].lower = lower;
  i_sliders[i_sliders_len].upper = upper;
  i_sliders_len++;
  if (i_sliders_len == i_sliders_size) {
    i_sliders_size *= 2;
    i_sliders = (I_SLIDER *) realloc(i_sliders, sizeof(I_SLIDER) * i_sliders_size);
    if (i_sliders == NULL) {
      i_sliders_size /= 2;
      i_sliders_len--;
      return -1;
    }
  }

  return 0;
}

}
