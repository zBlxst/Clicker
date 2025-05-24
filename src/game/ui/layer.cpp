#include "ui/layer.hpp"
#include "ui/button.hpp"

Layer::Layer(WindowManager& window_manager) : 
    m_window_manager(window_manager),
    m_all_buttons() {
        std::shared_ptr<Button> b = std::make_shared<Button>(200, 200, 500, 500, window_manager);
        m_all_buttons.push_back(b);
}

void Layer::display() {
    for (std::shared_ptr<Button> b: m_all_buttons) {
        b->display();
    }
}

void Layer::recv_click(unsigned int x, unsigned int y) {
    for (std::shared_ptr<Button> b: m_all_buttons) {
        if (b->catched_click(x, y))
            break;
    }
}