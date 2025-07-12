#pragma once

#include <string>

class StatTracker {

private:
    static constexpr std::string DEFAULT_SAVE_FILE = "build/stat.save";
    std::string m_file_name;

public:
    int m_clicks;
    double m_last_second_gain;
    double m_click_gain;
    double m_total_gain;
    double m_total_faction_coin_gain;
    double m_mana_produced;
    int m_n_achievements;

    StatTracker(std::string file_name);
    StatTracker();
};