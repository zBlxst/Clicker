#include "upgrades/faction_upgrades/elven_upgrade.hpp"

#include "game_manager.hpp"
#include "building.hpp"
#include "utils.hpp"

#include <functional>
#include <cmath>

ElvenUpgrade::ElvenUpgrade(int index_in_faction, int index_in_gm, GameManager& game_manager) :
    FactionUpgrade(Faction::FACTION::ELVEN, index_in_faction, index_in_gm, game_manager) {}

double ElvenUpgrade::get_cost() {
    return ElvenUpgrade::BASE_COSTS[m_index_in_faction];
}

double ElvenUpgrade::get_buff() {
    return 0;
}

std::vector<std::string> ElvenUpgrade::get_base_text_to_display() {
    return {};
}

void ElvenUpgrade::callback0() {
    m_game_manager.m_faction_coins_buff.m_multiplicative_buff *= 1.5;
}

void ElvenUpgrade::callback1() {
    m_game_manager.m_click_buff.m_additive_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return 25000*game_manager.get_stat_tracker().m_n_achievements;
      })
    );
    m_game_manager.m_faction_coins_buff.m_additive_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return pow(1+0.1*game_manager.get_stat_tracker().m_n_achievements, 0.95);
      })
    );
}

void ElvenUpgrade::callback2() {
    m_game_manager.m_mana_regen_buff.m_additive_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return 2*pow(log(1+game_manager.get_stat_tracker().m_clicks), 1.25);
      })
    );
}

void ElvenUpgrade::callback3() {
    m_game_manager.m_click_buff.m_additive_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                int n_good = 0;
                for (std::shared_ptr<Building> building : game_manager.get_all_buildings()) {
                    if (building->m_morality == Faction::MORALITY::GOOD) {
                        n_good += building->get_level();
                    }
                } 
                return pow(n_good, 0.6);
            }
        )
    );
}

void ElvenUpgrade::callback4() {
    // Buff Royal Exchange
    TODO();
}

void ElvenUpgrade::callback5() {
    m_game_manager.m_production_buff.m_multiplicative_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return 2*pow(game_manager.get_stat_tracker().m_clicks, 0.4);
      })
    );
}

void ElvenUpgrade::callback6() {
    m_game_manager.m_click_buff.m_multiplicative_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return 2*pow(log(1+game_manager.get_stat_tracker().m_total_faction_coin_gain), 2) / 100;
      })
    );
}

void ElvenUpgrade::callback7() {
    // Elven Luck
    TODO();
}

void ElvenUpgrade::callback8() {
    m_game_manager.m_click_buff.m_additive_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
        return game_manager.get_building_prod();
      })
    );
}