#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <optional>

class Texture
{
public:
    static std::optional<Texture> create(SDL_Renderer*, float width = 10, float height = 10, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    static std::optional<Texture> create(SDL_Renderer*, std::filesystem::path, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    // Texture(Texture&&);

    void target(SDL_Renderer*) const;
    void draw(SDL_Renderer*) const;

    // size represents the size of the texture being drawn on the current rendering target
    SDL_FRect projection() const;
    void projection(std::optional<float> width = {}, std::optional<float> height = {}, std::optional<float> x = {}, std::optional<float> y = {});

    // crop represents how texture is cropped before being applied on the rendering target
    SDL_FRect crop() const;
    void crop(std::optional<float> width = {}, std::optional<float> height = {}, std::optional<float> x = {}, std::optional<float> y = {});
private:
    Texture(SDL_Texture*, SDL_FRect, SDL_FRect);
private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*p)> m_texture;
    SDL_FRect m_projection = { 0, 0, 10, 10 };
    SDL_FRect m_crop = m_projection;
};