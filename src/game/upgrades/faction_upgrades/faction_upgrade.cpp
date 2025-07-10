#include "upgrades/faction_upgrades/faction_upgrade.hpp"

#include "game_manager.hpp"

FactionUpgrade::FactionUpgrade(Faction::FACTION faction, int index_in_faction, int index_in_gm, GameManager& game_manager) :
    Upgrade(index_in_gm, game_manager),
    m_faction(faction),
    m_index_in_faction(index_in_faction) {}

bool FactionUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_faction() == m_faction;
}

void FactionUpgrade::buy_callback() {
    switch (m_index_in_faction)
    {
    case 0:
        callback0();
        break;
    case 1:
        callback1();
        break;
    case 2:
        callback2();
        break;
    case 3:
        callback3();
        break;
    case 4:
        callback4();
        break;
    case 5:
        callback5();
        break;
    case 6:
        callback6();
        break;
    case 7:
        callback7();
        break;
    case 8:
        callback8();
        break;
    }
}