#include "faction.hpp"



std::vector<Faction::FACTION_COINS> Faction::get_faction_coins_per_faction(Faction::FACTION faction) {
    switch (faction) {
    case Faction::FAIRY:
        return { Faction::FACTION_COINS::FAIRY_COIN };
    case Faction::ELVEN:
        return { Faction::FACTION_COINS::ELVEN_COIN };
    case Faction::ANGEL:
        return { Faction::FACTION_COINS::ANGEL_COIN };
    case Faction::GOBLIN:
        return { Faction::FACTION_COINS::GOBLIN_COIN };
    case Faction::UNDEAD:
        return { Faction::FACTION_COINS::UNDEAD_COIN };
    case Faction::DEMON:
        return { Faction::FACTION_COINS::DEMON_COIN };
    case Faction::TITAN:
        return { Faction::FACTION_COINS::ANGEL_COIN, Faction::FACTION_COINS::GOBLIN_COIN };
    case Faction::DRUID:
        return { Faction::FACTION_COINS::ELVEN_COIN, Faction::FACTION_COINS::DEMON_COIN };
    case Faction::FACELESS:
        return { Faction::FACTION_COINS::FAIRY_COIN, Faction::FACTION_COINS::UNDEAD_COIN };
    default:
        return { };
    }
    
}
