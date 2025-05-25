#include "ui/layer.hpp"
#include "ui/button.hpp"

Layer::Layer(WindowManager& window_manager) : 
    m_window_manager(window_manager),
    m_all_buttons() {}

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