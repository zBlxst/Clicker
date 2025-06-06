#include "stat_tracker.hpp"

StatTracker::StatTracker(std::string file_name) :
    m_clicks(0),
    m_last_second_gain(0),
    m_file_name(file_name) {}

StatTracker::StatTracker() :
    StatTracker(DEFAULT_SAVE_FILE) {}