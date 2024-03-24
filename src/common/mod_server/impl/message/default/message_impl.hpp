#include "server.hpp"

#include "types.hpp"

#include <functional>
#include <string>

namespace common {
namespace mod_server {

/// Default implementation of IMessage
class MessageImpl : public IMessage {
public:
  MessageImpl();
  MessageImpl(const std::string &subject);
  MessageImpl(const std::string &subject, const std::string &message_str);

  ~MessageImpl();

  virtual const std::string get_subject() override;
  virtual unsigned long int get_subject_id() override;
  virtual int get_message_id() override;
  virtual bool get_message(std::string &message_str) override;
  virtual bool get_message(int &message_int) override;
  virtual utils::types::type get_type() override;

  virtual void set_subject(const std::string &subject) override;
  virtual void set_message(const std::string &message_str) override;
  virtual void set_message(const int &message_int) override;

private:
  void set_subject_id(const unsigned long int &id);

  std::string m_subject;
  std::string m_message_str;
  int m_message_int;
  unsigned long int m_subject_id;
  utils::types::type m_type = utils::types::e_STRING;
  bool m_subject_set;
  bool m_message_set;
  std::hash<std::string> m_subject_hasher;

  static int m_message_id;
};

} // namespace mod_server
} // namespace common
