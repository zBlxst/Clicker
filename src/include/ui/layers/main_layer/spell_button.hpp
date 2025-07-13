#pragma once

#include "ui/buttons/button.hpp"
#include "spells/spell.hpp"

class SpellButton : public Button {
    
private:
    static constexpr int BASE_POS_X = 700;
    static constexpr int BASE_POS_Y = 130;
    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 100;
    static constexpr int V_SPACING = 10;
    
    int m_ui_index;
    
    bool should_catch_click();
    
public:
    const std::shared_ptr<Spell> m_spell;
    
    SpellButton(std::shared_ptr<Spell> spell, WindowManager& window_manager);
    void callback();
    void display();
    void update_ui_index(int index);

};