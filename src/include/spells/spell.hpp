#pragma once

#include <string>
#include <vector>
#include <memory>

class GameManager;

class Spell {

protected:
    GameManager& m_game_manager;

    double m_cost;
    int m_index;
    bool m_running;

public:
    Spell(double cost, int index, GameManager& game_manager);
    static std::vector<std::shared_ptr<Spell>> get_one_of_each(GameManager& game_manager);
    
    void cast();
    void set_mana(double value);
    double get_cost();

    


    virtual void callback() = 0;
    bool is_available() {return true;};
    bool is_running();
    std::vector<std::string> get_base_text_to_display();
};