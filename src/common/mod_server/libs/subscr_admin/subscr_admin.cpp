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

bool SubscriberAdmin::remove_subscriber(hash::hash_t subscriber_id) {
  for (auto &[id, subscr_vec] : m_admin_map) {
    for (auto it = subscr_vec.begin(); it != subscr_vec.end(); it++) {
      if ((*it)->get_id() == subscriber_id) {
        // Found instance. Deleting and returning success
        subscr_vec.erase(it);
        return true;
      }
    }
  }

  // Failed to find instance to delete
  return false;
}

std::vector<ISubscr_ptr>
SubscriberAdmin::get_subscribers(const std::string &subject) {}

ISubscr_ptr SubscriberAdmin::get_subscriber(const int &subscr_id) {}

bool SubscriberAdmin::contains_subject(const std::string &subject) {
  return m_admin_map.contains(hash::get_hash(subject));
}
} // namespace subscr_admin
