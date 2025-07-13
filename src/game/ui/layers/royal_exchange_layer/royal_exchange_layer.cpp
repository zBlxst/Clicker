#include "ui/layers/royal_exchange_layer/royal_exchange_layer.hpp"
#include "ui/layers/royal_exchange_layer/royal_exchange_button.hpp"

#include "achievement.hpp"

#include "faction.hpp"

#include "game_manager.hpp"
#include "window_manager.hpp"

RoyalExchangeLayer::RoyalExchangeLayer(WindowManager& window_manager) :
    Layer(X, Y, WIDTH, HEIGHT, window_manager),
    m_all_royal_exchange_buttons() {
        for (int i = 0; i < Faction::FACTION_COINS::N_FACTIONS_COINS; i++) {
            std::shared_ptr<RoyalExchangeButton> achievement_button = std::make_shared<RoyalExchangeButton>((Faction::FACTION_COINS)i, window_manager);
            m_all_royal_exchange_buttons.push_back(achievement_button);
            m_all_buttons.push_back(achievement_button);
            achievement_button->update_ui_index(i);
        }
    }