#include "message_impl.hpp"

#include "logging.hpp"
#include "types.hpp"

#include <functional>
#include <string>

namespace common {
namespace mod_server {

int MessageImpl::m_message_id = 0;

MessageImpl::MessageImpl()
    : m_subject_id(0), m_subject_set(false), m_message_set(false) {
  Log(LogLevel::debug) << LOG_START;
  m_message_id++;
  Log(LogLevel::debug) << LOG_END << " - Created message with id "
                       << m_message_id;
}

MessageImpl::MessageImpl(const std::string &subject) : MessageImpl() {
  Log(LogLevel::debug) << LOG_START;
  set_subject(subject);
  Log(LogLevel::debug) << LOG_END;
}

MessageImpl::MessageImpl(const std::string &subject,
                         const std::string &message_str)
    : MessageImpl(subject) {
  Log(LogLevel::debug) << LOG_START;

  set_message(message_str);

  Log(LogLevel::debug) << LOG_END;
}

MessageImpl::~MessageImpl() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
}

const std::string MessageImpl::get_subject() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;

  return m_subject;
}

hash::hash_t MessageImpl::get_subject_id() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;

  return m_subject_id;
}
int MessageImpl::get_message_id() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;

  return m_message_id;
}

bool MessageImpl::get_message(std::string &message_str) {
  Log(LogLevel::debug) << LOG_START;

  if (m_type == utils::types::e_STRING) {
    Log(LogLevel::debug) << LOG_HEADER << "Getting message: '" << message_str
                         << "'";
    message_str = m_message_str;
  } else {
    Log(LogLevel::warning) << LOG_HEADER
                           << "Cannot get message, type is not set to str";
    message_str = "";
    Log(LogLevel::debug) << LOG_END;
    return false;
  }

  Log(LogLevel::debug) << LOG_END;

  return true;
}

bool MessageImpl::get_message(int &message_int) {
  Log(LogLevel::debug) << LOG_START;

  if (m_type == utils::types::e_INT) {
    Log(LogLevel::debug) << LOG_HEADER << "Getting message: " << message_int;
    message_int = m_message_int;
  } else {
    Log(LogLevel::warning) << LOG_HEADER
                           << "Cannot set message, type is not set to int";
    message_int = -1;
    Log(LogLevel::debug) << LOG_END;
    return false;
  }

  Log(LogLevel::debug) << LOG_END;

  return true;
}

utils::types::type MessageImpl::get_type() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;

  return m_type;
}

void MessageImpl::set_subject(const std::string &subject) {
  Log(LogLevel::debug) << LOG_START;

  // Ensure subjects are not set already
  if (m_subject_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Subject was already set, cannot set subject anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }

  Log(LogLevel::debug) << LOG_HEADER << "Subject set to str '" << subject
                       << "'";
  m_subject = subject;

  // set subject id to hash of subject
  long unsigned int hashed = m_subject_hasher(m_subject);
  set_subject_id(hashed);

  // Set to true, to make sure subject is only set once.
  m_subject_set = true;

  Log(LogLevel::debug) << LOG_END;
}

void MessageImpl::set_message(const std::string &message_str) {
  Log(LogLevel::debug) << LOG_START;

  // Ensure messages are not set already
  if (m_message_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Message was already set, cannot set message anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }

  Log(LogLevel::debug) << LOG_HEADER << "Message set to str '" << message_str
                       << "'";
  m_type        = utils::types::e_STRING;
  m_message_str = message_str;
  m_message_int = -1;

  // Set to true, to make sure message can only be set once.
  m_message_set = true;

  Log(LogLevel::debug) << LOG_END;
}

void MessageImpl::set_message(const int &message_int) {
  Log(LogLevel::debug) << LOG_START;

  // Ensure messages are not set already.
  if (m_message_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Message was already set, cannot set message anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }

  Log(LogLevel::debug) << LOG_HEADER << "Message set to int " << message_int;
  m_type        = utils::types::e_INT;
  m_message_str = "";
  m_message_int = message_int;

  // Set to true, to make sure message can only be set once.
  m_message_set = true;

  Log(LogLevel::debug) << LOG_END;
}

// PRIVATE
void MessageImpl::set_subject_id(const hash::hash_t &id) {
  Log(LogLevel::debug) << LOG_START << " - Setting subject id to " << id;

  m_subject_id = id;

  Log(LogLevel::debug) << LOG_END;
}

} // namespace mod_server
} // namespace common
