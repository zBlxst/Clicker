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
};