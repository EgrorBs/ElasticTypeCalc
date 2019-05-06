#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <sstream>
#include <string>

namespace std {
  
  template <typename T> std::string to_string(const T& in) {
    std::ostringstream stream;
    stream << in;
    return stream.str();
  }
  
}

#endif //PCH_H
