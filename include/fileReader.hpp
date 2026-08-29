#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace FileReader {
  inline std::string readFile(const std::string& filepath) {
    std::ifstream fileStream(filepath);
    
    // check if the filestream opened correctly
    if (!fileStream.is_open()) {
      std::cerr << "Failed to open file at: " << filepath << std::endl;
      return "";
    }
    
    // send file to string buffer and return string
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
    return "Hello World!";
  }
}
