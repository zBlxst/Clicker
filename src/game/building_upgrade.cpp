#include <building_upgrade.hpp>

BuildingUpgrade::BuildingUpgrade(unsigned int building_index, unsigned int upgrade_index, GameManager &game_manager) :
    m_game_manager(game_manager),
    m_building_index(building_index),
    m_upgrade_index(upgrade_index) {}