#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <optional>

class Texture
{
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
public:
    Texture(SDL_Renderer*, float width = 10, float height = 10, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    Texture(SDL_Renderer*, std::filesystem::path, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    Texture(const Texture&) = delete;
    ~Texture();
    operator bool() const;

    void target() const;
    void draw() const;
public:
    SDL_FRect projection = { 0, 0, 10, 10 };
    SDL_FRect crop = projection;
};