#pragma once

#include <string>

class Faction {
public:
    enum MORALITY {
        GOOD,
        BAD,
        NEUTRAL,
        N_MORALITIES,
        NONE,
    };
    static constexpr std::string MORALITIES_NAMES[MORALITY::N_MORALITIES] = { "Good", "Bad", "Neutral"};

    enum FACTION {
        FAIRY,
        ELVEN,
        ANGEL,
        GOBLIN,
        UNDEAD,
        DEMON,
        TITAN,
        DRUID,
        FACELESS,
        N_FACTIONS,
    };

    enum FACTION_COINS {
        FAIRY_COIN,
        ELVEN_COIN,
        ANGEL_COIN,
        GOBLIN_COIN,
        UNDEAD_COIN,
        DEMON_COIN,
        N_FACTIONS_COINS,
    };

    static constexpr FACTION FACTION_PER_MORALITY[N_MORALITIES][3] = {
        { FAIRY, ELVEN, ANGEL },
        { GOBLIN, UNDEAD, DEMON },
        { TITAN, DRUID, FACELESS },
    };
    static constexpr std::string FACTIONS_NAMES[FACTION::N_FACTIONS] = { 
        "Fairy", "Elven", "Angel",
        "Goblin", "Undead", "Demon",
        "Titan", "Druid", "Faceless",
    };
};