#pragma once

#include "ui/button.hpp"

class WindowManager;

class DoNothingButton : public Button {
private:

public:
    DoNothingButton(unsigned int x, unsigned int y, unsigned int width, unsigned int height, WindowManager& window_manager);
    void callback();
    void display();
};