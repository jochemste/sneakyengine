#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <memory>
#include <string>

/// Interface to display
class IDisplay {
public:
  /// @brief Start the display
  virtual void start() = 0;

  /// @brief Stop the display
  virtual void stop() = 0;

  /// @brief Refresh the diplay
  virtual void refresh() = 0;
};

/// @brief Factory-ish function to get display implementation
std::unique_ptr<IDisplay> DIS_get_display_instance();

/// @brief General display exception class
class DisplayException : public std::exception {
public:
  DisplayException(const char *message);
  DisplayException(const std::string &message);
  const char *what();

private:
  const char *m_message;
};

#endif // DISPLAY_HPP
