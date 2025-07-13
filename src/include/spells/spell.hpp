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

    int m_max_time;
    int m_remaining_time;
public:
    Spell(double cost, int index, GameManager& game_manager, int max_time);
    static std::vector<std::shared_ptr<Spell>> get_one_of_each(GameManager& game_manager);
    
    void cast();
    void set_mana(double value);
    double get_cost();


    virtual double get_buff() = 0;

    int get_max_time();
    int get_remaining_time();

    virtual void callback() = 0;
    virtual bool is_available() = 0;
    bool is_running();
    std::vector<std::string> get_base_text_to_display();
};