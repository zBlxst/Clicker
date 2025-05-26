#pragma once

#include <vector>
#include <memory>

class Button;
class WindowManager;

class Layer {
protected:
    WindowManager& m_window_manager;
    std::vector<std::shared_ptr<Button>> m_all_buttons;
    
public:
    Layer(WindowManager& window_manager);
    virtual void display();
    void recv_click(unsigned int x, unsigned int y);

};