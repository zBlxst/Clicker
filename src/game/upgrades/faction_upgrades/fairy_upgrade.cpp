#include "upgrades/faction_upgrades/fairy_upgrade.hpp"

#include "game_manager.hpp"
#include "building.hpp"

#include <cmath>

FairyUpgrade::FairyUpgrade(int index_in_faction, int index_in_gm, GameManager& game_manager) :
    FactionUpgrade(Faction::FACTION::FAIRY, index_in_faction, index_in_gm, game_manager) {}

double FairyUpgrade::get_cost() {
    return FairyUpgrade::BASE_COSTS[m_index_in_faction];
}

double FairyUpgrade::get_buff() {
    return 0;
}

std::vector<std::string> FairyUpgrade::get_base_text_to_display() {
    return {};
}

void FairyUpgrade::callback0() {
    m_game_manager.get_all_buildings()[0]->m_buff.m_additive_buff += 98;
    m_game_manager.get_all_buildings()[0]->m_cost_multiplier_buff -= 0.02;
}

void FairyUpgrade::callback1() {
    m_game_manager.get_all_buildings()[0]->m_buff.m_multiplicative_buff *= 100;    
}

void FairyUpgrade::callback2() {
    m_game_manager.m_mana_max_buff.m_additive_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                int n_good = 0;
                for (std::shared_ptr<Building> building : game_manager.get_all_buildings()) {
                    if (building->m_morality == Faction::MORALITY::GOOD) {
                        n_good += building->get_level();
                    }
                } 
                return 1.3*pow(n_good, 0.7);
            }
        )
    );
}

void FairyUpgrade::callback3() {
    m_game_manager.get_all_buildings()[1]->m_buff.m_additive_buff += 234;
    m_game_manager.get_all_buildings()[1]->m_cost_multiplier_buff -= 0.02;
}

void FairyUpgrade::callback4() {
    m_game_manager.m_click_buff.m_additive_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                double prod = 0;
                for (int i = 0; i < 3; i++) {
                    prod += game_manager.get_all_buildings()[i]->get_gain();
                } 
                return game_manager.m_production_buff.get_buffed_value(0.2*prod);
            }
        )
    );
}

void FairyUpgrade::callback5() {
    m_game_manager.m_mana_regen_buff.m_additive_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                return 2.75*pow(game_manager.get_all_buildings()[1]->get_level(), 0.275);
            }
        )
    );
}

void FairyUpgrade::callback6() {
    m_game_manager.get_all_buildings()[1]->m_buff.m_additive_buff += 580;
    m_game_manager.get_all_buildings()[1]->m_cost_multiplier_buff -= 0.02;
}

void FairyUpgrade::callback7() {
    m_game_manager.m_production_buff.m_multiplicative_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                double count = 0;
                for (int i = 0; i < 3; i++) {
                    count += game_manager.get_all_buildings()[i]->get_level();
                } 
                return 0.75*pow(count, 0.75) / 100;
            }
        )
    );
}

void FairyUpgrade::callback8() {
    m_game_manager.m_assistants_buff.m_additive_buff_callbacks.push_back(
        std::make_shared<std::function<double(GameManager&)>>(
            [](GameManager& game_manager) {
                double count = 0;
                for (int i = 0; i < 3; i++) {
                    count += game_manager.get_all_buildings()[i]->get_level();
                } 
                return 1.2*pow(count, 0.6);
            }
        )
    );
}