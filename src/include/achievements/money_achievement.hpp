#pragma once

#include "achievements/achievement.hpp"

class MoneyAchievement : public Achievement {

public: 
    static constexpr int N_ACHIEVEMENT = 5;
    static constexpr double REQUIREMENT[N_ACHIEVEMENT] = {1e3, 1e6, 1e9, 1e12, 1e15};

private:
    double m_requirement;
public:
    MoneyAchievement(double requirement, GameManager& game_manager);
    void check_if_obtained();

};