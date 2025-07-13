#include "faction.hpp"

#include <iostream>

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

std::string Faction::get_morality_name(MORALITY morality) {
    switch (morality)
    {
    case GOOD:
        return "Good";
    case BAD:
        return "Bad";
    case NEUTRAL:
        return "Neutral";
    case NO_MORALITY:
        return "None";
    }
    return "";
}

std::string Faction::get_faction_name(FACTION faction) {
    switch (faction)
    {
    case FAIRY:
        return "Fairy";
    case ELVEN:
        return "Elven";
    case ANGEL:
        return "Angel";
    case GOBLIN:
        return "Goblin";
    case UNDEAD:
        return "Undead";
    case DEMON:
        return "Demon";
    case TITAN:
        return "Titan";
    case DRUID:
        return "Druid";
    case FACELESS:
        return "Faceless";
    case NO_FACTION:
        return "None";
    }
    return "";
}
