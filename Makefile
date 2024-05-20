sdlPath = "./SDL/include"

# IMGUI_DIR = imgui

# SOURCES = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp

# SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_sdlrenderer2.cpp

#imgui
# CFLags = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

# sdl
CFLags += -I SDL/include -L SDL/lib
libs += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all:
	g++ main.cpp ${SOURCES} ${CFLags} -o main ${libs}