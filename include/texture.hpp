#pragma once

class Texture {
  unsigned int ID_ {};

public:
  Texture() = default;

  void init(const char* filepath);

  unsigned int get() { return ID_; }
  
};
