#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <thread>


class GameManager;

class Spell {

protected:
    GameManager& m_game_manager;

    double m_cost;
    int m_index;
    bool m_running;

    int m_max_time;
    int m_remaining_time;

    std::shared_ptr<std::function<void(GameManager&)>> m_start_spell;
    std::shared_ptr<std::function<void(GameManager&)>> m_end_spell;
    void thread_function();
    std::shared_ptr<std::thread> m_thread;
    
public:
    Spell(double cost, int index, int max_time, std::shared_ptr<std::function<void(GameManager&)>> start_spell, std::shared_ptr<std::function<void(GameManager&)>> end_spell, GameManager& game_manager);
    static std::vector<std::shared_ptr<Spell>> get_one_of_each(GameManager& game_manager);
    
    void cast();
    void set_mana(double value);
    double get_cost();



    virtual double get_buff() = 0;

    int get_max_time();
    int get_remaining_time();

    virtual void callback();
    virtual bool is_available() = 0;
    bool is_running();
    std::vector<std::string> get_base_text_to_display();
};