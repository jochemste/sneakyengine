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

bool SubscriberAdmin::remove_subscriber(const hash::hash_t &subscriber_id) {
  for (auto &[id, subscr_vec] : m_admin_map) {
    for (auto it = subscr_vec.begin(); it != subscr_vec.end(); it++) {
      if ((*it)->get_id() == subscriber_id) {
        // Found instance. Deleting instance and returning success
        subscr_vec.erase(it);

        // Check if subject should be deleted
        if (m_admin_map.at(id).empty())
          m_admin_map.erase(id);

        return true;
      }
    }
  }

  // Failed to find instance to delete
  return false;
}

std::vector<ISubscr_ptr>
SubscriberAdmin::get_subscribers(const std::string &subject) {
  if (!contains_subject(subject)) {
    return {};
  }

  return m_admin_map.at(hash::get_hash(subject));
}

ISubscr_ptr SubscriberAdmin::get_subscriber(const hash::hash_t &subscriber_id) {
  for (auto &[id, subscr_vec] : m_admin_map) {
    for (auto it = subscr_vec.begin(); it != subscr_vec.end(); it++) {
      if ((*it)->get_id() == subscriber_id) {
        // Found instance

        return (*it);
      }
    }
  }

  return nullptr;
}

bool SubscriberAdmin::contains_subject(const std::string &subject) {
  return m_admin_map.contains(hash::get_hash(subject));
}
} // namespace subscr_admin
