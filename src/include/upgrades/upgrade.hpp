#pragma once

#include <string>
#include <vector>

class GameManager;

class Upgrade {

public:
    enum TYPES {
        BUILDING,
        CLICK,
        N_ITEMS
    };

protected:
    GameManager& m_game_manager;

    bool m_bought;

public:
    Upgrade(unsigned int index_in_gm, GameManager& game_manager);

    const unsigned int m_index_in_gm;

    virtual double get_cost() = 0;
    virtual double get_buff() = 0;
    void buy();
    virtual bool is_available() = 0;
    virtual void buy_callback() = 0;

    bool is_bought();
    virtual std::vector<std::string> get_base_text_to_display() = 0;
};