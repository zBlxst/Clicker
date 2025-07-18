#include "stat_tracker.hpp"

StatTracker::StatTracker(std::string file_name) :
    m_clicks(0),
    m_last_second_gain(0),
    m_click_gain(0),
    m_total_gain(0),
    m_total_faction_coin_gain(0),
    m_file_name(file_name),
    m_mana_produced(0),
    m_n_achievements(0) {}

StatTracker::StatTracker() :
    StatTracker(DEFAULT_SAVE_FILE) {}