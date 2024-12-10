#include "debuggui.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>

DebugGui::DebugGui(const char* name)
: m_name(name)
{ m_ints.reserve(5); }

bool DebugGui::init(SDL_Window* window, SDL_Renderer* renderer) 
{
    m_window = window;
    m_renderer = renderer;

    // IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);

    return true;
}

void DebugGui::events(SDL_Event* event) 
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

void DebugGui::draw() 
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin(m_name);
    for ( auto a : m_ints ) 
        ImGui::SliderInt(a.label, a.point, a.min, a.max);
    for ( auto a : m_floats )
        ImGui::SliderFloat(a.label, a.point, a.min, a.max);
    ImGui::End();
}

void DebugGui::render() 
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}

DebugGui::~DebugGui() 
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void DebugGui::addInt(const char* label, int* v, int v_min, int v_max) 
{
    m_ints.push_back({ label, v, v_min, v_max });
}

void DebugGui::addFloat(const char* label, float* v, float v_min, float v_max) 
{
    m_floats.push_back({ label, v, v_min, v_max });
}