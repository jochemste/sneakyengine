#ifndef SUBSCR_ADMIN
#define SUBSCR_ADMIN

#include "server.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace csrv = common::mod_server;

namespace subscr_admin {

using ISubscr_ptr = std::shared_ptr<csrv::ISubscriber>;

class SubscriberAdmin {
public:
  bool add_subscriber(const std::string &subject, ISubscr_ptr subscriber);
  bool remove_subscriber(unsigned long int subscriber_id);

  std::vector<ISubscr_ptr> get_subscribers(const std::string &subject);

  ISubscr_ptr get_subscriber(const int &subscr_id);

  bool contains_subject(const std::string &subject);

private:
  std::unordered_map<unsigned long int, std::vector<ISubscr_ptr>> m_admin_map;
};

} // namespace subscr_admin
#endif // SUBSCR_ADMIN
