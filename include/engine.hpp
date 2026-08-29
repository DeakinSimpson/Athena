#pragma once

class Engine {
public:

  Engine();

  // functions
  void start();
  void stop();

private:
  void init();
  void onUpdate();
  void onRender();
};
