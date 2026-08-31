#pragma once

class Engine {
public:

  Engine();

  // functions
  void start();
  void stop();

private:
  float lastFrameTime_ { 0.0f };

  void init();
  void onUpdate();
  void onRender();
};
