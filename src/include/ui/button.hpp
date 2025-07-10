#pragma once


// class WindowManager;
class GameManager;

#include "ui/window_manager.hpp"


class Button {
protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    
    WindowManager& m_window_manager;
    
    // std::function<void(WindowManager&)> m_callback;
    virtual void callback();
    virtual bool should_catch_click();
    
    public:
    Button(int x, int y, int width, int height, 
        WindowManager& window_manager);
    bool catched_click(int x, int y);
    virtual void display();
    virtual sf::Color get_background_color();
};