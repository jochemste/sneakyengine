#ifndef HASH_HPP
#define HASH_HPP

#include <functional>
#include <string>

namespace hash {
typedef long unsigned hash_t;

inline hash_t get_hash(const std::string &str) {
  static std::hash<std::string> hasher;
  return hasher(str);
}
} // namespace hash
#endif // HASH_HPP
