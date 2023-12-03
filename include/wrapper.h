#include <stdlib.h>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <imgui_wrapper_str.h>

#define STARTING_BUFF_LEN (10)

F_SLIDER *f_sliders = NULL;
size_t f_sliders_len = 0;
size_t f_sliders_size = 0;

I_SLIDER *i_sliders = NULL;
size_t i_sliders_len = 0;
size_t i_sliders_size = 0;

static ImGuiIO io;
