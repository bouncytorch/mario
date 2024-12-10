#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <imgui.h>
#include <vector>

class DebugGui {
public:
    DebugGui(const char* name);
    bool init(SDL_Window* window, SDL_Renderer* renderer);
    void events(SDL_Event* event);
    void draw();
    void render();
    ~DebugGui();

    void addInt(const char* label, int* v, int v_min, int v_max);
    void addFloat(const char* label, float* v, float v_min, float v_max);
private:
    const char* m_name;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    struct intsl { const char* label; int* point; int min; int max; };
    std::vector<intsl> m_ints;

    struct floatsl { const char* label; float* point; float min; float max; };
    std::vector<floatsl> m_floats;
};