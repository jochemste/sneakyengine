#ifndef SERVER_IMPL_HPP
#define SERVER_IMPL_HPP

#include "server.hpp"

#include "hash.hpp"

#include <memory>
#include <string>
#include <vector>

namespace common {
namespace mod_server {
class ServerImpl : public IServer {
public:
  ServerImpl();
  ~ServerImpl();

  virtual void post(const std::shared_ptr<IPoster> poster,
                    std::shared_ptr<IMessage> message) override;
  virtual void subscribe(std::shared_ptr<ISubscriber> subscriber,
                         const std::string &subject) override;
  virtual void unsubscribe(hash::hash_t subscriber_id) override;
  virtual bool has_subscribers(const std::string &subject) override;

private:
  std::vector<std::shared_ptr<ISubscriber>> m_subscribers;
};
} // namespace mod_server
} // namespace common

#endif // SERVER_IMPL_HPP
