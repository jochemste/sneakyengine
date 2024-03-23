#include "message_impl.hpp"

#include <string>

namespace common {
namespace mod_server {

MessageImpl::MessageImpl() {}
MessageImpl::MessageImpl(const std::string &subject) {}

MessageImpl::MessageImpl(const std::string &subject,
                         const std::string &message_str) {}

const std::string MessageImpl::get_subject() {}
int MessageImpl::get_subject_id() {}
void MessageImpl::get_message(std::string &message_str) {}
void MessageImpl::get_message(int &message_int) {}
utils::types::type MessageImpl::get_type() {}

void MessageImpl::set_subject(const std::string &subject) {}
void MessageImpl::set_subject_id(const int &id) {}
void MessageImpl::set_message(std::string &message_str) {}
void MessageImpl::set_message(int &message_int) {}

} // namespace mod_server
} // namespace common
