#pragma once

#include "window.hpp"

class Engine {
public:

  Engine() = default;

  // getters / setters
  Window& getWindow() { return window_; }

  // functions
  void start();
  void stop();

  void onUpdate();

private:
  Window window_;
};
