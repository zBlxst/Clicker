#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/layers/main_layer/click_button.hpp"
#include "ui/layers/main_layer/upgrade_button.hpp"
#include "ui/layers/main_layer/building_button.hpp"
#include "ui/layers/main_layer/spell_button.hpp"

#include "building.hpp"
#include "building_upgrade.hpp"
#include "game_manager.hpp"

#include <iostream>
#include "utils.hpp"


MainLayer::MainLayer(WindowManager& window_manager) :
    Layer(0, 0, window_manager.m_width, window_manager.m_height, window_manager),
    m_all_upgrade_buttons() {
    
    // Initialisation of upgrades vectors
    for (int i = 0; i < Upgrade::TYPES::N_ITEMS; i++) {
        m_all_upgrade_buttons.push_back(std::vector<std::shared_ptr<UpgradeButton>>());
    }

    // Click button for background
    std::shared_ptr<ClickButton> click_button = std::make_shared<ClickButton>(window_manager);
    m_all_buttons.push_back(click_button);

    // Initialisation of buildings
    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        std::shared_ptr<BuildingButton> building_button = std::make_shared<BuildingButton>(i, window_manager);
        m_all_buttons.push_back(building_button);
    }

    // Initialisation of faction upgrades
    for (std::shared_ptr<Upgrade> m_up: m_window_manager.get_game_manager().get_all_upgrades()[Upgrade::TYPES::FACTION]) {
        std::shared_ptr<UpgradeButton> faction_upgrade_button = std::make_shared<UpgradeButton>(m_up, window_manager);
        m_all_buttons.push_back(faction_upgrade_button);
        m_all_upgrade_buttons[Upgrade::TYPES::FACTION].push_back(faction_upgrade_button);
    }

    // Initialisation of buildings upgrades
    for (std::shared_ptr<Upgrade> b_up: m_window_manager.get_game_manager().get_all_upgrades()[Upgrade::TYPES::BUILDING]) {
        std::shared_ptr<UpgradeButton> building_upgrade_button = std::make_shared<UpgradeButton>(b_up, window_manager);
        m_all_buttons.push_back(building_upgrade_button);
        m_all_upgrade_buttons[Upgrade::TYPES::BUILDING].push_back(building_upgrade_button);
    }

    // Initialisation of click upgrades
    for (std::shared_ptr<Upgrade> c_up: m_window_manager.get_game_manager().get_all_upgrades()[Upgrade::TYPES::MISC]) {
        std::shared_ptr<UpgradeButton> click_upgrade_button = std::make_shared<UpgradeButton>(c_up, window_manager);
        m_all_buttons.push_back(click_upgrade_button);
        m_all_upgrade_buttons[Upgrade::TYPES::MISC].push_back(click_upgrade_button);
    }

    // Initialisation of spells
    for (std::shared_ptr<Spell> spell: m_window_manager.get_game_manager().get_all_spells()) {
        std::shared_ptr<SpellButton> spell_button = std::make_shared<SpellButton>(spell, window_manager);
        m_all_buttons.push_back(spell_button);
        m_all_spell_buttons.push_back(spell_button);
    }

    
}

void MainLayer::display() {
    int available_building_upgrades = 0;
    int available_spell = 0;

    for (int i = 0; i < Upgrade::TYPES::N_ITEMS; i++) {
        for (std::shared_ptr<UpgradeButton> b_up_button: m_all_upgrade_buttons[i]) {
            if (b_up_button->m_upgrade->is_available()) {
                b_up_button->update_ui_index(available_building_upgrades++);
            }
        }
    }

    for (std::shared_ptr<SpellButton> s_button: m_all_spell_buttons) {
        if (s_button->m_spell->is_available()) {
            s_button->update_ui_index(available_spell++);
        }
    }

    std::string money_text = std::format("Money {}", double_to_string(m_window_manager.get_game_manager().get_money()));
        std::string gain_text = std::format("Gain {}/s", double_to_string(m_window_manager.get_game_manager().get_prod()));
        std::string total_clicks_text = std::format("Total clicks {}", m_window_manager.get_game_manager().get_stat_tracker().m_clicks);
        std::string click_gain_text = std::format("Click gain {}", double_to_string(m_window_manager.get_game_manager().get_click_gain()));
        std::string assistants_text = std::format("Assistants {}", m_window_manager.get_game_manager().get_assistants());
        std::string mana_text = std::format("Mana {} / {}", double_to_string(m_window_manager.get_game_manager().get_mana()), double_to_string(m_window_manager.get_game_manager().get_mana_max()));
        std::string morality_text = std::format("Morality : {} / Faction : {}", Faction::get_morality_name(m_window_manager.get_game_manager().get_morality()), Faction::get_faction_name(m_window_manager.get_game_manager().get_faction())); 
        std::string faction_coins_text = std::format("Faction coins : [{}, {}, {}, {}, {}, {}]", 
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::FAIRY_COIN)),
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::ELVEN_COIN)),
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::ANGEL_COIN)),
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::GOBLIN_COIN)),
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::UNDEAD_COIN)),
            double_to_string(m_window_manager.get_game_manager().get_faction_coin(Faction::FACTION_COINS::DEMON_COIN))
        );
    std::vector<std::string> to_print = {money_text, gain_text, total_clicks_text, click_gain_text, assistants_text, mana_text, morality_text, faction_coins_text};
    m_window_manager.draw_text(to_print, 0, 0, 15, WindowManager::WHITE);
    Layer::display();
}