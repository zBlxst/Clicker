#include "ui/layer.hpp"
#include "ui/button.hpp"
#include "ui/buttons/close_layer_button.hpp"

#include <ranges>


Layer::Layer(WindowManager& window_manager) : 
    m_window_manager(window_manager),
    m_all_buttons() {
        std::shared_ptr<CloseLayerButton> close_layer_button = std::make_shared<CloseLayerButton>(window_manager);
        m_all_buttons.push_back(close_layer_button);
    }

void Layer::display() {
    for (std::shared_ptr<Button> b: m_all_buttons) {
        b->display();
    }
}

void Layer::recv_click(int x, int y) {
    for (std::shared_ptr<Button> b: std::ranges::views::reverse(m_all_buttons)) {
        if (b->catched_click(x, y))
            break;
    }
}