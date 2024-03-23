#include "message_impl.hpp"

#include "logging.hpp"
#include "types.hpp"

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

int MessageImpl::get_subject_id() {
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
    Log(LogLevel::debug) << LOG_HEADER << "Setting message to: '" << message_str
                         << "'";
    message_str = m_message_str;
  } else {
    Log(LogLevel::warning) << LOG_HEADER << "Cannot set message to '"
                           << message_str << "', type is not set to str";
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
    Log(LogLevel::debug) << LOG_HEADER << "Setting message to: " << message_int;
    m_message_int = message_int;
  } else {
    Log(LogLevel::warning) << LOG_HEADER << "Cannot set message to "
                           << message_int << ", type is not set to int";
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

  if (m_subject_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Subject was already set, cannot set subject anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }
  m_subject = subject;

  m_subject_set = true;

  Log(LogLevel::debug) << LOG_END;
}

void MessageImpl::set_subject_id(const int &id) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
}

void MessageImpl::set_message(const std::string &message_str) {
  Log(LogLevel::debug) << LOG_START;

  if (m_message_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Message was already set, cannot set message anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }

  m_type        = utils::types::e_STRING;
  m_message_str = message_str;
  m_message_int = -1;

  m_message_set = true;

  Log(LogLevel::debug) << LOG_END;
}

void MessageImpl::set_message(const int &message_int) {
  Log(LogLevel::debug) << LOG_START;

  if (m_message_set) {
    Log(LogLevel::warning)
        << LOG_HEADER << "Message was already set, cannot set message anymore";
    Log(LogLevel::debug) << LOG_END;
    return;
  }

  m_type        = utils::types::e_INT;
  m_message_str = "";
  m_message_int = message_int;

  m_message_set = true;

  Log(LogLevel::debug) << LOG_END;
}

} // namespace mod_server
} // namespace common
