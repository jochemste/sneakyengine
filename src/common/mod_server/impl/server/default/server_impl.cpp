#include "server_impl.hpp"

namespace common {
namespace mod_server {
ServerImpl::ServerImpl() {}
ServerImpl::~ServerImpl() {}

void ServerImpl::post(const std::shared_ptr<IPoster> poster,
                      std::shared_ptr<IMessage> message) {}

void ServerImpl::subscribe(std::shared_ptr<ISubscriber> subscriber,
                           const std::string &subject) {}
void ServerImpl::unsubscribe(hash::hash_t subscriber_id) {}
bool ServerImpl::has_subscribers(const std::string &subject) {}
} // namespace mod_server
} // namespace common
