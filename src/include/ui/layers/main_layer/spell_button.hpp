#pragma once

#include "ui/button.hpp"
#include "spells/spell.hpp"

class SpellButton : public Button {
    
private:
    static constexpr unsigned int BASE_POS_X = 700;
    static constexpr unsigned int BASE_POS_Y = 130;
    static constexpr unsigned int WIDTH = 100;
    static constexpr unsigned int HEIGHT = 100;
    static constexpr unsigned int V_SPACING = 10;
    
    int m_ui_index;
    
    bool should_catch_click();
    
public:
    const std::shared_ptr<Spell> m_spell;
    
    SpellButton(std::shared_ptr<Spell> spell, WindowManager& window_manager);
    void callback();
    void display();
    void update_ui_index(int index);

};