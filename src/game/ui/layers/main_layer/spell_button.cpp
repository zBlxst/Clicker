#include "ui/layers/main_layer/spell_button.hpp"

#include <format>
#include <math.h>

#include "game_manager.hpp"
#include "spells/spell.hpp"
#include "utils.hpp"

SpellButton::SpellButton(   std::shared_ptr<Spell> spell, 
                                WindowManager& window_manager) :
    Button( 0, 0, 
            WIDTH, HEIGHT, window_manager),
    m_spell(spell),
    m_ui_index(0) {}


void SpellButton::callback() {
    if (m_spell->is_available()) {
        m_spell->cast();
    }
}

void SpellButton::display() {
    if (m_spell->is_available()) {
        Button::display();
        std::vector<std::string> to_write = m_spell->get_base_text_to_display();
        to_write.push_back(std::format("Cost : {}", double_to_string(m_spell->get_cost()))); 
        to_write.push_back(std::format("Buff : {}", double_to_string((m_spell->get_buff()*100)/100)));
        if (m_spell->is_running()) {
            to_write.push_back(std::format("Time : {}s", m_spell->get_remaining_time()));
        }
        
        m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
    }
}

void SpellButton::update_ui_index(int index) {
    m_ui_index = index;
    m_x = BASE_POS_X;
    m_y = BASE_POS_Y + m_ui_index*(HEIGHT+V_SPACING);
}

bool SpellButton::should_catch_click() {
    return m_spell->is_available() && !m_spell->is_running();
}
