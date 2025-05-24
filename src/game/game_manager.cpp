#include "game_manager.hpp"

GameManager::GameManager() : m_money(0) {}

double GameManager::get_money() {
    return m_money;
}

void GameManager::click() {
    m_money += 1;
}