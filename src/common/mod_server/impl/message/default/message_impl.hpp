#include "server.hpp"

#include "types.hpp"

#include <string>

namespace common {
namespace mod_server {

class MessageImpl : public IMessage {
public:
  MessageImpl();
  MessageImpl(const std::string &subject);
  MessageImpl(const std::string &subject, const std::string &message_str);

  ~MessageImpl() {}

  virtual const std::string get_subject() override;
  virtual int get_subject_id() override;
  virtual void get_message(std::string &message_str) override;
  virtual void get_message(int &message_int) override;
  virtual utils::types::type get_type() override;

  virtual void set_subject(const std::string &subject) override;
  virtual void set_subject_id(const int &id) override;
  virtual void set_message(std::string &message_str) override;
  virtual void set_message(int &message_int) override;

private:
  std::string m_subject;
  std::string m_message_str;
  int m_message_int         = 0;
  utils::types::type m_type = utils::types::e_STRING;
};

} // namespace mod_server
} // namespace common
