#include <memory>
#include <string>

#include "types.hpp"

namespace common {
namespace mod_server {

/// Message interface to be used in IServer. Used to pass messages between
/// poster and subscriber.
class IMessage {
public:
  /// Gets the subject of the message as a string. Used by subscriber and
  /// server.
  virtual const std::string get_subject() = 0;
  /// Gets the subject id of the message. Subject id should be set by the
  /// server, to allow uniqueness. Used by subscriber, server and poster.
  virtual int get_subject_id() = 0;
  /// Gets the message id, which is unique. Used by subscriber, server and
  /// poster.
  virtual int get_message_id() = 0;
  /// Get the message content as a string. Returns false if failed.
  /// Used by subscriber.
  virtual bool get_message(std::string &message_str) = 0;
  /// Get the message content as an int. Returns false if failed.
  /// Used by subscriber.
  virtual bool get_message(int &message_int) = 0;
  /// Get the type of the message content. To be used by the subscriber.
  virtual utils::types::type get_type() = 0;

  /// Set the subject of the message. Should be set by the poster.
  virtual void set_subject(const std::string &subject) = 0;
  /// Set the subject id. Should be set by the server and should be unique
  /// within the context of the server.
  virtual void set_subject_id(const int &id) = 0;
  /// Set the message as a string. Should be used by the poster.
  virtual void set_message(const std::string &message_str) = 0;
  /// Set the message as a int. Should be used by the poster.
  virtual void set_message(const int &message_int) = 0;
};

/// Poster interface. To be used to send messages to subscribers through the
/// server.
class IPoster {
public:
  /// Get id of poster.
  virtual int get_id() = 0;

  /// Send a prepared message to the server.
  virtual bool send_message(std::shared_ptr<IMessage> message) = 0;
};

class ISubscriber {
public:
  virtual bool has_message()                                  = 0;
  virtual void set_message(std::shared_ptr<IMessage> message) = 0;
  virtual std::shared_ptr<IMessage> get_message()             = 0;
};

/// Subscription based server. Used to pass messages between poster and
/// subscriber for the purpose of communicating between modules/submodules.
class IServer {
public:
  virtual void post(const std::shared_ptr<IPoster> poster,
                    std::shared_ptr<IMessage> message) = 0;
  virtual void subscribe(std::shared_ptr<ISubscriber> observer,
                         const std::string &subject)   = 0;
};

/// Factory to create a message.
class MessageFactory {
public:
  /// Create a shared pointer to a message.
  std::shared_ptr<IMessage> create();
};
} // namespace mod_server
} // namespace common
