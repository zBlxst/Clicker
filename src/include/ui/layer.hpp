#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class Button;
class WindowManager;

class Layer {
protected:
    WindowManager& m_window_manager;
    std::vector<std::shared_ptr<Button>> m_all_buttons;

    int m_x;
    int m_y;
    int m_width;
    int m_height;
    
public:
    sf::RenderTexture m_render_texture;
    sf::Sprite get_sprite();
    Layer(int x, int y, int width, int height, WindowManager& window_manager);
    virtual void display();
    void recv_click(int x, int y);

};