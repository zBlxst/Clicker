#include "ui/layer.hpp"
#include "ui/button.hpp"
#include "ui/buttons/do_nothing_button.hpp"

#include <ranges>


Layer::Layer(int x, int y, int width, int height, WindowManager& window_manager) : 
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_window_manager(window_manager),
    m_render_texture(sf::Vector2u(width, height)),
    m_all_buttons() {
        std::shared_ptr<DoNothingButton> do_nothing_button = std::make_shared<DoNothingButton>(0, 0, m_width, m_height, window_manager);
        m_all_buttons.push_back(do_nothing_button);
    }

void Layer::display() {
    for (std::shared_ptr<Button> b: m_all_buttons) {
        b->display();
    }
    m_render_texture.display();
}

void Layer::recv_click(int x, int y) {
    if (   x < m_x 
        || x > m_x + m_width
        || y < m_y
        || y > m_y + m_height
    ) {
        m_window_manager.pop_layer();
    }

    x -= m_x;
    y -= m_y;
    for (std::shared_ptr<Button> b: std::ranges::views::reverse(m_all_buttons)) {
        if (b->catched_click(x, y))
            break;
    }
}

sf::Sprite Layer::get_sprite() {
    sf::Sprite sprite(m_render_texture.getTexture());
    sprite.setScale(sf::Vector2f(1, 1));
    sprite.setPosition(sf::Vector2f(m_x, m_y));
    return sprite;
}
