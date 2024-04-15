#include "subscr_admin.hpp"

#include "hash.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace subscr_admin {

using ISubscr_ptr = std::shared_ptr<csrv::ISubscriber>;

bool SubscriberAdmin::add_subscriber(const std::string &subject,
                                     ISubscr_ptr subscriber) {
  if (contains_subject(subject)) {
    m_admin_map[hash::get_hash(subject)].push_back(subscriber);
  } else {
    m_admin_map[hash::get_hash(subject)] = {subscriber};
  }

  return true;
}
bool SubscriberAdmin::remove_subscriber(unsigned long int subscriber_id) {}

std::vector<ISubscr_ptr>
SubscriberAdmin::get_subscribers(const std::string &subject) {}

ISubscr_ptr SubscriberAdmin::get_subscriber(const int &subscr_id) {}

bool SubscriberAdmin::contains_subject(const std::string &subject) {
  return m_admin_map.contains(hash::get_hash(subject));
}
} // namespace subscr_admin
