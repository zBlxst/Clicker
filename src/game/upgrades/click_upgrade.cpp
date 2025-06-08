#include "upgrades/click_upgrade.hpp"

#include <format>

ClickUpgrade::ClickUpgrade(int index, unsigned int index_in_gm, GameManager& game_manager) :
    m_index(index),
    Upgrade(index_in_gm, game_manager) {}

std::vector<std::string> ClickUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Click")
    };
    return res;
}
