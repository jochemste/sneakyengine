#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <memory>

class IDisplay {
public:
  virtual void start() = 0;
  virtual void stop()  = 0;
};

/// @brief Factory-ish function to get display implementation
std::unique_ptr<IDisplay> DIS_get_display_instance();

#endif // DISPLAY_HPP
