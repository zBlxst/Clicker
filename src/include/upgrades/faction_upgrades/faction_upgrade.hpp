#pragma once

#include "upgrade.hpp"
#include "faction.hpp"

class GameManager;

class FactionUpgrade : public Upgrade {

protected:
    Faction::FACTION m_faction;
    int m_index_in_faction;

    virtual void callback0() = 0;
    virtual void callback1() = 0;
    virtual void callback2() = 0;
    virtual void callback3() = 0;
    virtual void callback4() = 0;
    virtual void callback5() = 0;
    virtual void callback6() = 0;
    virtual void callback7() = 0;
    virtual void callback8() = 0;
public:
    FactionUpgrade(Faction::FACTION faction, int index_in_faction, int index_in_gm, GameManager& game_manager);
    bool is_available();
    void buy_callback();
};

