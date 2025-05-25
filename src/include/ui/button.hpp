#pragma once

#include <bits/stdc++.h>

// class WindowManager;
class GameManager;

#include "ui/window_manager.hpp"


class Button {
protected:
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_width;
    unsigned int m_height;

    WindowManager& m_window_manager;

    // std::function<void(WindowManager&)> m_callback;
    virtual void callback();

public:
    Button(unsigned int x, unsigned int y, unsigned int width, unsigned int height, 
        WindowManager& window_manager);
    bool catched_click(unsigned int x, unsigned int y);
    virtual void display();
};