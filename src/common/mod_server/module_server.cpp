#include "server.hpp"

#include "message_impl.hpp"

namespace common {
namespace mod_server {
std::shared_ptr<IMessage> MessageFactory::create() {
  return std::make_unique<MessageImpl>();
}
} // namespace mod_server
} // namespace common
