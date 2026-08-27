#pragma once

#include "window.hpp"
#include "controller.hpp"

class Engine {
public:

  Engine();

  // getters / setters
  Window& getWindow() { return window_; }

  // functions
  void start();
  void stop();

private:
  // holds global engine variables
  Window window_ {};
  Controller controller_ {};

  void init();
  void onUpdate();
  void onRender();
};
