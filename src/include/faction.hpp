#pragma once

#include <string>
#include <vector>

class Faction {
public:
    static constexpr int N_BASE_FACTIONS_PER_MORALITY = 3;
    enum MORALITY {
        GOOD,
        BAD,
        NEUTRAL,
        N_MORALITIES,
        NO_MORALITY,
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
        NO_FACTION
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

    static constexpr FACTION BASE_FACTION_PER_MORALITY[N_MORALITIES][N_BASE_FACTIONS_PER_MORALITY] = {
        { FAIRY, ELVEN, ANGEL },
        { GOBLIN, UNDEAD, DEMON },
        { TITAN, DRUID, FACELESS },
    };
    static constexpr std::string FACTIONS_NAMES[FACTION::N_FACTIONS] = { 
        "Fairy", "Elven", "Angel",
        "Goblin", "Undead", "Demon",
        "Titan", "Druid", "Faceless",
    };

    static std::vector<FACTION_COINS> get_faction_coins_per_faction(Faction::FACTION faction);
};