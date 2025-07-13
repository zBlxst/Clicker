#pragma once

#include <memory>
#include <vector>

#include "ui/layer.hpp"
#include "ui/layers/royal_exchange_layer/royal_exchange_button.hpp"

class RoyalExchangeLayer : public Layer {
private:
    static constexpr int X = 100;
    static constexpr int Y = 100;
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 800;

    std::vector<std::shared_ptr<RoyalExchangeButton>> m_all_royal_exchange_buttons;
public:
    RoyalExchangeLayer(WindowManager& window_manager);
};