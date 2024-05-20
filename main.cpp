#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
// #include "imgui.h"
// #include <backends/imgui_impl_sdl2.h>
// #include "backends/imgui_impl_sdlrenderer2.h"+

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int screenX = 90;
int screenY = 90;

// SDL variables
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

bool loadMedia();
void close();
void eventLoop();
// void imguiInit();
// void imguiLoop();

// Initialize SDL and create a window
bool init() {
    // bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cout << "Error SDL2 Initialization : " << SDL_GetError();
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (window == NULL || renderer == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } 

    gScreenSurface = SDL_GetWindowSurface(window);

    return true;
}

// Main loop
void mainLoop() {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    static int lastY = 0;
    static bool jump = false;

    if (screenY > (1080 - SCREEN_HEIGHT)) {
        screenY = lastY;
        jump = true;
    }

    if (keys[SDL_SCANCODE_D]) {
        screenX += 1;
    }
    if (keys[SDL_SCANCODE_A]) {
        screenX -= 1;
    }
    if (keys[SDL_SCANCODE_W]) {
        screenY -= 1;
    }
    if (keys[SDL_SCANCODE_S]) {
        screenY += 1;
    }

    lastY = screenY;
}


int main(int argc, char *args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 0;
    }
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    // if (!loadMedia()) {
    //     printf("Failed to load media!\n");
    //     return 0;
    // }
    
    SDL_Surface* healthbar_sur = IMG_Load("healthbar.png");
    SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(renderer, healthbar_sur);
    SDL_Rect rect = {100, 100, 200, 22};

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        // SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&e)) {
            // ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        mainLoop();
        // imguiLoop();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, healthbar_tex, NULL, &rect);

        SDL_RenderPresent(renderer);
        // SDL_SetWindowPosition(gWindow, screenX, screenY);
    }

    // Cleanup
    close();
    // ImGui_ImplSDLRenderer2_Shutdown();
    // ImGui_ImplSDL2_Shutdown();
    // ImGui::DestroyContext();

    // SDL_DestroyTexture(lettuce_tex);
    SDL_DestroyTexture(healthbar_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

// Load media
bool loadMedia() {
    gHelloWorld = IMG_Load("download.jpg");

    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "download.jpg", SDL_GetError());
        return false;
    }

    return true;
}

// Free resources and close SDL
void close() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

// Handle events
void eventLoop(SDL_Event &e) {
    // Currently not used, but can be used for event handling
}


// void imguiInit() {
//         // Setup Dear ImGui context
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO &io = ImGui::GetIO();
//     (void)io;

//     // Setup Dear ImGui style
//     ImGui::StyleColorsDark();

//     // Setup Platform/Renderer backends
//     ImGui_ImplSDL2_InitForSDLRenderer(gWindow, renderer);
//     ImGui_ImplSDLRenderer2_Init(renderer);
// }
// bool show_demo_window = true;
// ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
// void imguiLoop() {
//         // Start the Dear ImGui frame
//     ImGui_ImplSDLRenderer2_NewFrame();
//     ImGui_ImplSDL2_NewFrame();
//     ImGui::NewFrame();

//     ImGui::ShowDemoWindow(&show_demo_window);

//     // Rendering
//     ImGui::Render();
    
//     SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
//     SDL_RenderClear(renderer);
//     ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
// }

