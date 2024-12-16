#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <optional>

class Texture
{
public:
    Texture(SDL_Renderer*&, float width = 10, float height = 10, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    Texture(SDL_Renderer*&, std::filesystem::path, std::optional<SDL_FRect> projection = {}, std::optional<SDL_FRect> crop = {});
    Texture(const Texture&) = delete;
    ~Texture();
    operator bool() const;

    void target() const;
    void draw() const;

    // size represents the size of the texture being drawn on the current rendering target
    SDL_FRect projection() const;
    void projection(std::optional<float> width = std::nullopt, std::optional<float> height = std::nullopt, std::optional<float> x = std::nullopt, std::optional<float> y = std::nullopt);

    // crop represents how texture is cropped before being applied on the rendering target
    SDL_FRect crop() const;
    void crop(std::optional<float> width = std::nullopt, std::optional<float> height = std::nullopt, std::optional<float> x = std::nullopt, std::optional<float> y = std::nullopt);
private:
    SDL_Renderer*& m_renderer;
    SDL_FRect m_projection = { 0, 0, 10, 10 };
    SDL_FRect m_crop = m_projection;
    SDL_Texture* m_texture;
};