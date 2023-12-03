#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

#CXX = g++
#CXX = clang++

EXE = imgui_wrapper
BIN_DIR = ./bin
IMGUI_DIR = ./imgui
SRC_DIR = ./src
SOURCES = $(SRC_DIR)/wrapper.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
APP_SOURCES = $(SRC_DIR)/main.cpp
APP_SOURCES += $(SOURCES)
APP_OBJS = $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(basename $(notdir $(APP_SOURCES)))))
LIB_OBJS = $(addprefix $(BIN_DIR)/lib_, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++11 -I./include
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
# LINUX_GL_LIBS = -lGLESv2

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib -L/opt/homebrew/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES FOR TEST APP
##---------------------------------------------------------------------

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(APP_OBJS)
	$(CXX) -o $(BIN_DIR)/$@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(BIN_DIR)/*

.PHONY: run
run:
	@./bin/$(EXE)

##---------------------------------------------------------------------
## BUILD RULES FOR LIBRARY
##---------------------------------------------------------------------

$(BIN_DIR)/lib_%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -fpic -o $@ $<

$(BIN_DIR)/lib_%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -fpic -o $@ $<

$(BIN_DIR)/lib_%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -fpic -o $@ $<

.PHONY: lib
lib: $(LIB_OBJS)
#	ar -rcs lib$(EXE).a $(LIB_OBJS)
	$(CXX) -shared -o lib$(EXE).so $(LIB_OBJS)
