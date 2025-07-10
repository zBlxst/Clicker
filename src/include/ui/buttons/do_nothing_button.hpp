#pragma once

#include "ui/button.hpp"

class WindowManager;

class DoNothingButton : public Button {
private:

public:
    DoNothingButton(int x, int y, int width, int height, WindowManager& window_manager);
    void callback();
    void display();
};