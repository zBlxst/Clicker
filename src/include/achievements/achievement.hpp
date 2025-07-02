#pragma once

class GameManager;

class Achievement {

protected:
    bool m_obtained;
    GameManager& m_game_manager;

public:
    Achievement(GameManager& game_manager);
    void obtain();
    bool is_obtained();
    virtual void check_if_obtained() = 0;
};